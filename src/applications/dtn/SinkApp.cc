/*
 * SinkApp.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: sertinell
 */

#include "SinkApp.h"

Define_Module(SinkApp);

SinkApp::SinkApp() {
    // TODO Auto-generated constructor stub

}

SinkApp::~SinkApp() {
    // TODO Auto-generated destructor stub
}

void SinkApp::initialize(int stage)
{
    if(stage==4){
        beaconsApp = ModuleAccess<BeaconsApp>("beaconsApp").get();
        ASSERT(beaconsApp->getType() == Sink);
        localPort = DTN_PORT;
        destPort = DTN_PORT;
        //Obtain the broadcast interface
        IInterfaceTable *ift = InterfaceTableAccess().get();
        InterfaceEntry *ie = ift->getInterfaceByName(par("wirelessIf").stringValue());
        if (ie == NULL) {
            throw cRuntimeError(this, "Invalid output interface name" );
        }
        wifiInterface = ie->getInterfaceId();
        useAck = par("useAck").boolValue();
        useBroadcast= par("useBroadcast").boolValue();
        myId = beaconsApp->getMyId();

        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);
        socket.setBroadcast(true);

        beaconsApp->subscribeNews(this);
        backBoneModule = dynamic_cast<BackBoneApp*> (getParentModule()->getParentModule()->getSubmodule(par("backboneModule").stdstringValue().c_str()));
        dataRx = registerSignal("dtnDataRx");
        ackTx = registerSignal("dtnAckTx");
    }
}

void SinkApp::onNewNeighbor(Neighbor *neighbor)
{
    if(neighbor->getNodeType() != Sink){
        beaconsApp->sendBeaconNow();
    }
}

void SinkApp::onRemoveNeighbor(Neighbor *neighbor)
{
}

void SinkApp::onNeighborChanged(Neighbor *neigh){
}

void SinkApp::handleMessage(cMessage *msg)
{
    ASSERT(!msg->isSelfMessage());
    if (dynamic_cast<DTNDataMsg *>(msg) != NULL) {
        DTNDataMsg *data = check_and_cast<DTNDataMsg *>(msg);
        processDtnData(data);
    }else{
        delete msg;
    }
}

/*
 * decapsulate packets and send them to DTNBackbone module through the ethernet interface
 */
void SinkApp::processDtnData(DTNDataMsg *data)
{
    sendDirect(data, backBoneModule, "dataIn");
    emit(dataRx, data);
    if(useAck){
        UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(data->removeControlInfo());
        // determine its source address/port
        IPvXAddress dstAddr = useBroadcast?IPv4Address::ALLONES_ADDRESS:ctrl->getSrcAddr();
        int srcPort = ctrl->getSrcPort();
        delete ctrl;

        DTNDataAck *ack = generateDtnAck(data);
        emit(ackTx, ack);
        socket.sendTo(ack, dstAddr, srcPort, wifiInterface);
    }
}

DTNDataAck *SinkApp::generateDtnAck(const DTNDataMsg *msg)
{
    DTNDataAck *ack = new DTNDataAck("DTN_ACK", DTN_ACK);
    ack->setDstId(msg->getSrcId());
    ack->setMsgId(msg->getMsgId());
    ack->setSrcId(myId);
    ack->setByteLength(sizeof(myId)*2+ sizeof(msg->getMsgId()));
    return ack;
}
