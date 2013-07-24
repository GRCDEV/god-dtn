//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "EpidemicProtocol.h"
#include "BackBoneApp.h"

Define_Module(EpidemicProtocol);

EpidemicProtocol::EpidemicProtocol() {
    // TODO Auto-generated constructor stub

}

EpidemicProtocol::~EpidemicProtocol() {
    bb->unRegisterEpidemicProto(this);
}

void EpidemicProtocol::onNewNeighbor(Neighbor *neighbor)
{
    Enter_Method("OnNewNeighbor");
    EpiNeighbor *epi = dynamic_cast<EpiNeighbor*>(neighbor);
    ASSERT(epi != NULL);
    if(neighbor->getNodeType() == Car){
        sendOffer(neighbor->getIpAddr(), neighbor->getId());
    }
    else if (neighbor->getNodeType() == Sink){
        emptyBufferOnSink(neighbor->getIpAddr(),neighbor->getId());
    }
}

void EpidemicProtocol::onNeighborChanged(Neighbor *neighbor)
{
    Enter_Method("OnNeighborChanged");
    EpiNeighbor *epi = dynamic_cast<EpiNeighbor*>(neighbor);
    ASSERT(epi != NULL);
    if(neighbor->getNodeType() == Sink){
        emptyBufferOnSink(neighbor->getIpAddr(), neighbor->getId());
    }
    else if(lastAddedFragment > epi->getLastBufferUpdate() &&
            ( (lastSentMsg.find(neighbor->getId()) == lastSentMsg.end()) || lastAddedFragment > lastSentMsg[neighbor->getId()])){
        lastSentMsg[neighbor->getId()] = simTime();
        sendOffer(neighbor->getIpAddr(), neighbor->getId());
    }
}

void EpidemicProtocol::onRemoveNeighbor(Neighbor *neighbor)
{
    lastSentMsg.erase(neighbor->getId());
}

void EpidemicProtocol::initialize(int stage)
{
    IDTNProtocol::initialize(stage);
    if(stage==4){
            beaconsApp = ModuleAccess<BeaconsApp>("beaconsApp").get();
            bb = dynamic_cast<BackBoneApp*> (getParentModule()->getParentModule()->getSubmodule("DTNBackBone"));
            bb->registerEpidemicProto(this);
            ASSERT(beaconsApp->getType() == Car);
            myId = beaconsApp->getMyId();
            localPort = DTN_PORT;
            destPort = DTN_PORT;
            fragmentSize = par("fragmentSize");
            //Obtain the broadcast interface
            IInterfaceTable *ift = InterfaceTableAccess().get();
            InterfaceEntry *ie = ift->getInterfaceByName(par("wirelessIf").stringValue());
            if (ie == NULL) {
                throw cRuntimeError(this, "Invalid output interface name" );
            }
            wifiInterface = ie->getInterfaceId();

            socket.setOutputGate(gate("udpOut"));
            socket.bind(localPort);
            socket.setBroadcast(false);

            beaconsApp->subscribeNews(this);

            msgId= intrand(100);
            lastAddedFragment = simTime();
            maxHops = par("maxHops");
    }
}

void EpidemicProtocol::sendMessage(uint64 destId, uint64 msgId, bool broadcast, uint32 length)
{
    uint8 n = length / (fragmentSize-sizeof(DTNFragment));
    Enter_Method("sendMessage()");
    for(uint32 i=0; i<n ; i++){
        DTNFragment fragment;
        fragment.dstId = destId;
        fragment.srcId = myId;
        fragment.msgId = msgId;
        fragment.timeStamp = simTime();
        fragment.totalN = n;
        fragment.seqN = i;
        fragment.hops = maxHops;
        fragment.size = fragmentSize;
        enQueueFragment(fragment);
    }
}

void EpidemicProtocol::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        ASSERT("SelfMessage");
    }
    else if(dynamic_cast<EpidemicPktOffer*>(msg) != NULL){
        EpidemicPktOffer *pkt = check_and_cast<EpidemicPktOffer *>(msg);
        if(pkt->getDstId() == myId){
            processOffer(pkt);
        }
        else{
            delete pkt;
        }
    }else if(dynamic_cast<EpidemicPktAsk*>(msg) != NULL){
        EpidemicPktAsk *pkt = check_and_cast<EpidemicPktAsk *>(msg);
        if(pkt->getDstId() == myId){
            processAsk(pkt);
        }
        else{
            delete pkt;
        }
    }else if(dynamic_cast<DTNDataMsg*>(msg) != NULL){
        DTNDataMsg *data = check_and_cast<DTNDataMsg *>(msg);
        if(data->getDstId() == myId){
            processDTNData(data);
        }
        else{
            delete data;
        }
    }else {
        delete msg;
    }
}

void EpidemicProtocol::enQueueFragment(DTNFragment fragment)
{
    DTNUnique uni;
    uni.msgId = fragment.msgId;
    uni.srcId = fragment.srcId;
    uni.seqN = fragment.seqN;
    onBuffer.insert(uni);
    buffer.insert(std::pair<DTNUnique, DTNFragment>({uni, fragment}));
    lastAddedFragment = simTime();
}

void EpidemicProtocol::processOffer(EpidemicPktOffer *msg)
{
    uint64 srcId = msg->getSrcId();
    uint n = msg->getOfferArraySize();
    EpidemicPktAsk *ask = new EpidemicPktAsk("ASK",PKT_REQUEST);
    ask->setDstId(srcId);
    ask->setSrcId(myId);
    int nAsk = 0;
    std::vector<DTNUnique> asked;

    int length = sizeof(srcId)*2+sizeof(EpidemicType);
    for(uint i=0; i<n; i++)
    {
        DTNUnique uni = msg->getOffer(i);
        if(onBuffer.find(uni) == onBuffer.end() && delivered.find(uni) == delivered.end()){
            asked.push_back(uni);
            length+=sizeof(DTNUnique);
            nAsk++;
        }
    }

    UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(msg->removeControlInfo());
    IPvXAddress dstAddr = ctrl->getSrcAddr();

    if( asked.size()> 0 ){
        ask->setAskArraySize(asked.size());
        ask->setByteLength(length);
        for(uint j=0; j< asked.size(); j++){
             ask->setAsk(j, asked.at(j));
        }
        socket.sendTo(ask, dstAddr, destPort, wifiInterface);
    }
    else{
        delete ask;
    }
    delete msg;
}

void EpidemicProtocol::processAsk(EpidemicPktAsk *msg)
{
    uint64 srcId = msg->getSrcId();
    uint n = msg->getAskArraySize();
    // determine its source address/port
    UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(msg->removeControlInfo());
    IPvXAddress dstAddr = ctrl->getSrcAddr();
    DTNDataMsg *data= new DTNDataMsg("EpidemicData");
    data->setDstId(srcId);
    data->setSrcId(myId);
    uint totalLength =sizeof(srcId)*2+sizeof(msgId);
    std::vector<DTNFragment> toSend;
    for(uint i=0;  i<n; i++){
        DTNUnique uni = msg->getAsk(i);
        if( buffer.find(uni) != buffer.end()){
            DTNFragment frag = buffer.find(uni)->second;
            toSend.push_back(frag);
            totalLength += fragmentSize;
        }
        /*
         * Send message and restart counters
         */
        if(( totalLength + fragmentSize > MAX_DTN_PACKET_SIZE))
        {
            data->setFragmentsArraySize(toSend.size());
            data->setByteLength(totalLength);
            for(uint j=0; j < toSend.size(); j++){
                data->setFragments(j, toSend.at(j));
            }
            toSend.clear();
            totalLength = 0;
            DTNDataMsg *data_t = data->dup();
            data->setMsgId(msgId++);
            socket.sendTo(data_t, dstAddr, destPort, wifiInterface);
        }
    }
    if(toSend.size()>0){
        data->setFragmentsArraySize(toSend.size());
        data->setByteLength(totalLength);
        data->setMsgId(msgId++);
        for(uint j=0; j < toSend.size(); j++){
            data->setFragments(j, toSend.at(j));
        }
        socket.sendTo(data, dstAddr, destPort, wifiInterface);
    }
    else{
        delete data;
    }
    delete msg;
}

void EpidemicProtocol::processDTNData(DTNDataMsg *msg)
{
    uint n = msg->getFragmentsArraySize();
    for(uint i=0; i<n; i++){
        DTNUnique uni;
        uni.msgId=msg->getFragments(i).msgId;
        uni.srcId=msg->getFragments(i).srcId;
        uni.seqN=msg->getFragments(i).seqN;
        if(onBuffer.find(uni) == onBuffer.end() && delivered.find(uni) == delivered.end() ){
            enQueueFragment(msg->getFragments(i));
        }
    }
    delete msg;
}

simtime_t EpidemicProtocol::getLastAddedFragment() const
{
    return lastAddedFragment;
}

void EpidemicProtocol::sendOffer(IPvXAddress ip, uint64 nodeId)
{
    Enter_Method("SendOffer");

    if(onBuffer.empty()){
        return;
    }
    EpidemicPktOffer *msg = new EpidemicPktOffer("Offer", PKT_OFFER);
    msg->setSrcId(myId);
    msg->setDstId(nodeId);
    uint totalLength = sizeof(myId)*2+sizeof(PKT_OFFER);
    std::vector<DTNUnique> toSend;
    for(std::set<DTNUnique>::iterator i = onBuffer.begin(); i!= onBuffer.end(); i++){
        DTNUnique uni = *i;
        toSend.push_back(uni);
        totalLength+=sizeof(DTNUnique);
        if(totalLength+sizeof(DTNUnique)> MAX_DTN_PACKET_SIZE){
            EpidemicPktOffer *newMsg = msg->dup();
            newMsg->setOfferArraySize(toSend.size());
            for(uint j= 0; j< toSend.size(); j++){
                newMsg->setOffer(j,toSend[j]);
            }
            newMsg->setByteLength(totalLength);
            totalLength = sizeof(myId)*2+sizeof(PKT_OFFER);
            toSend.clear();
            socket.sendTo(newMsg, ip, DTN_PORT, wifiInterface);
        }
    }
    if(toSend.size() != 0){
        msg->setOfferArraySize(toSend.size());
        for(uint j= 0; j< toSend.size(); j++){
            msg->setOffer(j,toSend.at(j));
        }
        msg->setByteLength(totalLength);
        socket.sendTo(msg, ip, DTN_PORT, wifiInterface);
    }
    else{
        delete msg;
    }
}

void EpidemicProtocol::notifyMessageReceived(uint64 srcId, uint32 msgId, uint32 seqN)
{
    std::list<DTNUnique> toRemove;
    for(std::set<DTNUnique>::iterator i=onBuffer.begin(); i!= onBuffer.end(); i++){
        if(i->msgId == msgId && i-> srcId == srcId){
            toRemove.push_back(*i);
        }
        else{
            i++;
        }
    }
    for(std::list<DTNUnique>::iterator i=toRemove.begin(); i != toRemove.end(); i++){
        delivered.insert(*i);
        buffer.erase(*i);
        onBuffer.erase(*i);
    }
}

void EpidemicProtocol::emptyBufferOnSink(IPvXAddress ip, uint64 nodeId)
{
    Enter_Method("emptyBufferOnSink");
    if(buffer.empty()){
        return;
    }
    uint64 srcId = nodeId;
    IPvXAddress dstAddr = ip;
    DTNDataMsg *data= new DTNDataMsg("EpidemicData");
    data->setDstId(srcId);
    data->setSrcId(myId);
    uint totalLength =sizeof(srcId)*2+sizeof(msgId);
    std::vector<DTNFragment> toSend;
    for(std::map<DTNUnique, DTNFragment>::iterator i= buffer.begin(); i!=buffer.end(); i++){
        DTNUnique uni = i->first;
        DTNFragment frag = i->second;
        toSend.push_back(frag);
        totalLength += fragmentSize;
        /*
         * Send message and restart counters
         */
        if(( totalLength + fragmentSize) > MAX_DTN_PACKET_SIZE)
        {
            data->setFragmentsArraySize(toSend.size());
            data->setByteLength(totalLength);
            for(uint j=0; j < toSend.size(); j++){
                data->setFragments(j, toSend.at(j));
            }
            toSend.clear();
            totalLength = 0;
            DTNDataMsg *data_t = data->dup();
            data->setMsgId(msgId++);
            socket.sendTo(data_t, dstAddr, destPort, wifiInterface);
        }
        delivered.insert(uni);
    }
    if(toSend.size()>0){
        data->setFragmentsArraySize(toSend.size());
        data->setByteLength(totalLength);
        data->setMsgId(msgId++);
        for(uint j=0; j < toSend.size(); j++){
            data->setFragments(j, toSend.at(j));
        }
        socket.sendTo(data, dstAddr, destPort, wifiInterface);
    }
    else{
        delete data;
    }
    onBuffer.clear();
    buffer.clear();
}


















