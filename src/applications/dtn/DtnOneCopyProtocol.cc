//
// T	his program is free software: you can redistribute it and/or modify
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

#include "DtnOneCopyProtocol.h"

DtnOneCopyProtocol::DtnOneCopyProtocol()
{
}

DtnOneCopyProtocol::~DtnOneCopyProtocol()
{
    cancelAndDelete(transmission);
    for(std::map<uint32, cMessage*>::iterator i = msgIdAckMap.begin(); i!= msgIdAckMap.end(); i++){
        cMessage * msg= i->second;
        cancelAndDelete(msg);
    }
}

void DtnOneCopyProtocol::sendMessage(uint64 destId, uint64 msgId, bool broadcast, uint32 length)
{
    Enter_Method("sendMessage()");
    uint n = ceil(double(length) / (fragmentSize-sizeof(DTNFragment)));
    uint N = ceil(n*(1+redundancy));
    for(uint32 i=0; i<N ; i++){
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
        emit(fragmentGenerated, fragment.size);
    }
    EV << "Sending a new message. Size:" << length << " MsgId:" << msgId << endl;
    startTransmission();
}

void DtnOneCopyProtocol::onNewNeighbor(Neighbor *neighbor)
{
    Enter_Method("onNewNeighbor()");
    EV << "New Neighbor received: Id:"<< neighbor->getId() <<" MyId:"<< myId << endl;
    ASSERT(sortedNeighbors!=NULL);
    ASSERT(sortedNeighbors->size() == neighbors.size());
    if(isBetterThanMe(neighbor)){
        sortedNeighbors->insert(neighbor);
        neighbors.insert(std::pair<uint64, Neighbor*>{neighbor->getId(), neighbor});
        neighWindow.insert(std::pair<uint64, uint>{neighbor->getId(),windowSize});
        ASSERT(sortedNeighbors->size() == neighbors.size());
        startTransmission();
        if(neighbor->getNodeType()==NodeType::Sink){
            oppStarted = simTime();
        }
    }
    else{
        /*
         * do nothing
         */
    }
}

void DtnOneCopyProtocol::onRemoveNeighbor(Neighbor *neighbor)
{
    Enter_Method("onRemoveNeighbor()");
    ASSERT(sortedNeighbors!=NULL);
    EV << "Remove Neighbor received: Id:"<< neighbor->getId() <<" MyId:"<< myId << endl;
    uint64 id = neighbor->getId();
    if(neighbors.find(id) != neighbors.end()){
        Neighbor *oldPointer = neighbors.at(id);
        if(neighbor->getNodeType() == NodeType::Sink){
            emit(oppExpired, simTime()-oppStarted);
        }
        int ret = sortedNeighbors->erase(oldPointer);
        ASSERT(ret==1);
        ret = neighbors.erase(id);
        ASSERT(ret==1);
        neighWindow.erase(id);
    }
}

void DtnOneCopyProtocol::onNeighborChanged(Neighbor *neighbor)
{
    Enter_Method("onNeighborChanged()");
    ASSERT(sortedNeighbors != NULL);
    EV << "Neighbor changed received: Id:"<< neighbor->getId() <<" MyId:"<< myId << endl;
    if( isBetterThanMe(neighbor) ){
        EV << "This neighbor is better than me: Id:"<< neighbor->getId() <<" MyId:"<< myId << endl;
        if(neighbors.find(neighbor->getId()) != neighbors.end() ){
            ASSERT(sortedNeighbors->size() == neighbors.size());
            /*
             * Update Neighbor
             * 1.get the old pointer
             * 2.remove from sortedNeighbors
             * 3.insert again
             * 4.insert in neighbors
             */
            Neighbor *oldPointer = neighbors.at(neighbor->getId());
            int ret = sortedNeighbors->erase(oldPointer);
            ASSERT(ret==1);
            ret = neighbors.erase(neighbor->getId());
            ASSERT(ret==1);
            ret = neighWindow.erase(neighbor->getId());
            ASSERT(ret==1);
            ASSERT(sortedNeighbors->size() == neighbors.size());
        }
        neighWindow.insert(std::pair<uint64, uint>{neighbor->getId(),windowSize});
        sortedNeighbors->insert(neighbor);
        neighbors.insert(std::pair<uint64,Neighbor *>{neighbor->getId(),neighbor});
        ASSERT(sortedNeighbors->size() == neighbors.size());
        startTransmission();
    }
    else{
        if(neighbors.find(neighbor->getId()) != neighbors.end() ){
            EV << "This neighbor is worse than me: Id:"<< neighbor->getId() <<" MyId:"<< myId << endl;
            onRemoveNeighbor(neighbor);
        }
    }
}

void DtnOneCopyProtocol::initialize(int stage)
{
    if(stage==4){
        sortedNeighbors = NULL;
        transmission = new cMessage("TRANSMISSION");
        neighbors.clear();
        beaconsApp = ModuleAccess<BeaconsApp>("beaconsApp").get();
        ASSERT(beaconsApp->getType() == Car);
        localPort = DTN_PORT;
        destPort = DTN_PORT;
        fragmentSize = par("fragmentSize");
        useBroadcast = par("useBroadcast").boolValue();
        redundancy = par("redundancy").doubleValue();
        //Obtain the broadcast interface
        IInterfaceTable *ift = InterfaceTableAccess().get();
        InterfaceEntry *ie = ift->getInterfaceByName(par("wirelessIf").stringValue());
        if (ie == NULL) {
            throw cRuntimeError(this, "Invalid output interface name" );
        }
        wifiInterface = ie->getInterfaceId();
        EV << "DtnOneCopyProtocol MTU" << ie->getMTU();
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);
        socket.setBroadcast(useBroadcast);
        beaconsApp->subscribeNews(this);
        myId = beaconsApp->getMyId();
        ackTimeOut = par("ackTimeOut");
        windowSize = par("windowSize");
        bitrate = par("bitrate");
        maxHops = par("maxHops");
        maxRange = par("maxRange");
        maxSqrRange = pow(maxRange,2);
        useAck = par("useAck").boolValue();
        oneFragPerMsg= par("oneFragPerMsg").boolValue();
        msgId=intrand(100);
        fragmentGenerated = registerSignal("dtnFragmentGenerated");
        dataTx = registerSignal("dtnDataTx");
        directDataTx = registerSignal("directDataTx");
        dataRx = registerSignal("dtnDataRx");
        ackTx = registerSignal("dtnAckTx");
        ackRx = registerSignal("dtnAckRx");
        ackTO = registerSignal("dtnAckTO");
        oppExpired = registerSignal("oppExpired");
        dropMsg = registerSignal("dropMsg");

    }
}

void DtnOneCopyProtocol::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        if(msg == transmission){
            doTransmission();
        }
        else if(msg->getKind() == ACK_TIME_OUT){
            processACKTimeOut(msg);
            delete msg;
        }
    }
    else if(dynamic_cast<DTNDataMsg*>(msg) != NULL){
        DTNDataMsg *data = check_and_cast<DTNDataMsg *>(msg);
        if(data->getDstId() == myId){
            processDTNData(data);
        }
        delete data;
    }
    else if(dynamic_cast<DTNDataAck*>(msg) != NULL){
        DTNDataAck *ack = check_and_cast<DTNDataAck *>(msg);
        if(ack->getDstId() == myId){
            if(useAck){
                processACK(ack);
            }
        }
        delete ack;
    }
}

void DtnOneCopyProtocol::processDTNData(DTNDataMsg *msg)
{
    uint n = msg->getFragmentsArraySize();
    emit(dataRx,msg);
    for(uint i=0; i<n; i++){
        enQueueFragment(msg->getFragments(i));
    }

    double waitTime = 0;

    if(useAck){
        DTNDataAck *ack = generateDtnAck(msg);
        emit(ackTx, ack);
        // determine its source address/port
        UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(msg->removeControlInfo());
        IPvXAddress dstAddr = useBroadcast?IPv4Address::ALLONES_ADDRESS:ctrl->getSrcAddr();
        UDPSocket::SendOptions options;
        options.outInterfaceId = wifiInterface;
        socket.sendTo(ack, dstAddr, destPort, &options);
        waitTime = ((double)ack->getByteLength())/(double)bitrate;
    }
    startTransmission(waitTime);
}

void DtnOneCopyProtocol::processACK(DTNDataAck *msg)
{
    uint32 key=msg->getMsgId();
    uint64 srcId = msg->getSrcId();
    if(msgIdAckMap.find(key)!= msgIdAckMap.end()){
        if(neighWindow.find(srcId) != neighWindow.end()){
            uint window = neighWindow.at(srcId);
            neighWindow[srcId]= window +1;
        }
        std::vector<DTNFragment> *fragments = (std::vector<DTNFragment> *)(msgIdAckMap.at(key)->getContextPointer());
        if(neighbors.find(srcId) != neighbors.end() && neighbors.at(srcId)->getNodeType() == Car){
            emit(ackRx, msg);
        }
        ASSERT(fragments != NULL);
        cancelAndDelete(msgIdAckMap.at(key));
        msgIdAckMap.erase(key);
        delete fragments;
    }
}

void DtnOneCopyProtocol::processACKTimeOut(cMessage *msg)
{
    std::vector<DTNFragment> *fragments = (std::vector<DTNFragment> *)(msg->getContextPointer());
    ASSERT(fragments != NULL);
    uint n= fragments->size();
    for(uint i=0; i<n; i++){
        enQueueFragment(fragments->at(i));
    }
    std::map<uint32, cMessage*>::iterator i;
    for(i=msgIdAckMap.begin(); i!= msgIdAckMap.end(); i++){
        if(i->second == msg){
            break;
        }
    }
    emit(ackTO, n);
    msgIdAckMap.erase(i);
}

bool DtnOneCopyProtocol::hasNeighbors()
{
    return !sortedNeighbors->empty();
}

void DtnOneCopyProtocol::enQueueFragment(DTNFragment fragment)
{
    timeSeq myTimeSeq;
    myTimeSeq.time=fragment.timeStamp;
    myTimeSeq.seq = fragment.seqN;
    buffer.insert(std::pair<timeSeq, DTNFragment>{myTimeSeq, fragment});
}

DTNDataMsg *DtnOneCopyProtocol::generateDtnData(const Neighbor *neigh, int nodeType)
{
    DTNDataMsg *data = new DTNDataMsg("DTN_Data", DTN_DATA);
    data->setDstId(neigh->getId());
    data->setSrcId(myId);
    data->setMsgId(msgId++);
    uint n;
    if(oneFragPerMsg){
        n=1;
    }
    else{
        n= MAX_DTN_PACKET_SIZE/(fragmentSize);
    }
    uint j=0;
    std::vector<DTNFragment> toSend;
    for(std::map<timeSeq, DTNFragment>::iterator i = buffer.begin(); i!= buffer.end()  && j != n; i++){
        if(nodeType == Car){
            if(i->second.hops == 0 || i->second.hops > 1){
                if(i->second.hops != 0){
                    i->second.hops--;
                    ASSERT(i->second.hops < 1);
                }
                toSend.push_back(i->second);
                j++;
            }
        }
        else{
            toSend.push_back(i->second);
            j++;
        }
    }

    j=0;
    data->setFragmentsArraySize(toSend.size());
    for(std::vector<DTNFragment>::iterator i = toSend.begin(); i!= toSend.end(); i++, j++){
        data->setFragments(j, (*i));
        timeSeq myTimeSeq;
        myTimeSeq.time = i->timeStamp;
        myTimeSeq.seq = i->seqN;
        uint ret = buffer.erase(myTimeSeq);
        ASSERT(ret==1);
    }
    uint byteLength = sizeof(myId*2)+sizeof(msgId)+fragmentSize*toSend.size();
    data->setByteLength(byteLength);
    return data;
}

DTNDataAck *DtnOneCopyProtocol::generateDtnAck(const DTNDataMsg *msg)
{
    DTNDataAck *ack = new DTNDataAck("DTN_ACK", DTN_ACK);
    ack->setDstId(msg->getSrcId());
    ack->setMsgId(msg->getMsgId());
    ack->setSrcId(myId);
    ack->setByteLength(sizeof(myId)*2+ sizeof(msg->getMsgId()));
    return ack;
}

void DtnOneCopyProtocol::scheduleAckTimeOut(DTNDataMsg *msg)
{
    std::vector<DTNFragment> *fragments = new std::vector<DTNFragment>();
    uint n= msg->getFragmentsArraySize();
    for(uint i=0; i!=n; i++){
        fragments->push_back(msg->getFragments(i));
    }
    cMessage *ackTO = new cMessage("ACK_TO", ACK_TIME_OUT);
    ackTO->setContextPointer(fragments);
    msgIdAckMap.insert(std::pair<uint32, cMessage* >{msg->getMsgId(), ackTO});
    scheduleAt(simTime()+ackTimeOut, ackTO);
}

Neighbor *DtnOneCopyProtocol::getBestNeighbor()
{
    std::set<Neighbor *>::iterator i;
    for(i = sortedNeighbors->begin(); i != sortedNeighbors->end(); i++){
        Neighbor *node = *i;
        Coord oldLoc = node->getLocation();
        Coord newLoc;
        Coord speed;
        speed.x = cos(node->getAngle())*node->getSpeed();
        speed.y = sin(node->getAngle())*node->getSpeed();
        newLoc.x = oldLoc.x + speed.x * (simTime()-node->getLastUpdate()).dbl();
        newLoc.y = oldLoc.y + speed.y * (simTime()-node->getLastUpdate()).dbl();
        if( beaconsApp->getMyLoc().sqrdist(newLoc) < maxSqrRange){
            return node;
        }
    }
    return NULL;
}

void DtnOneCopyProtocol::startTransmission(double delay)
{
    /*
     * if a transmission is currently running. Do nothing
     */
    if(transmission->isScheduled()){
        return;
    }
    scheduleAt(simTime()+delay, transmission);
}

uint DtnOneCopyProtocol::getBitrate() const
{
    return bitrate;
}

uint DtnOneCopyProtocol::getBufferByteSize() const
{
    return buffer.size()*fragmentSize;
}

void DtnOneCopyProtocol::doTransmission()
{
    if(hasNeighbors() && hasPackets()){
        Neighbor *dst = getBestNeighbor();
        if( dst != NULL && neighWindow.at(dst->getId()) != 0){
            DTNDataMsg *data = generateDtnData(dst, dst->getNodeType());
            if(dst->getNodeType()==NodeType::Car){
                emit(dataTx, data);
            }
            else{
                emit(directDataTx,data);
            }

            IPvXAddress dstAddr = useBroadcast?IPv4Address::ALLONES_ADDRESS:dst->getIpAddr();
            UDPSocket::SendOptions options;
            options.outInterfaceId = wifiInterface;
            socket.sendTo(data, dstAddr, destPort, &options);

            if(useAck){
                uint window = neighWindow.at(dst->getId());
                neighWindow[dst->getId()] = --window;
                scheduleAckTimeOut(data);
            }

            uint ackBitSize = (!useAck)?0:(sizeof(myId)*2 + sizeof (msgId)*2)*8;
            double idleTime = (double)(data->getBitLength()+ackBitSize)/ (double)bitrate;
            scheduleAt(simTime()+idleTime, transmission);
        }
        else{
            cancelEvent(transmission);
        }
    }
    else{
        cancelEvent(transmission);
    }
}

bool DtnOneCopyProtocol::hasPackets()
{
    return !buffer.empty();
}

void DtnOneCopyProtocol::finish(){
    emit(dropMsg, buffer.size()+msgIdAckMap.size());
}


