/*
 * SinkApp.h
 *
 *  Created on: Oct 25, 2012
 *      Author: sertinell
 */

#ifndef SINKAPP_H_
#define SINKAPP_H_

#include <omnetpp.h>
#include "BeaconsApp.h"
#include "Ieee80211Consts.h"
#include "INETDefs.h"
#include "IPvXAddressResolver.h"
#include "IPv4InterfaceData.h"
#include "InterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "UDPControlInfo_m.h"
#include "UDPSocket.h"
#include "BeaconPkt_m.h"
#include "Neighbor.h"
#include "DTNcommon.h"
#include "DTNDataMsg_m.h"
#include "BackBoneApp.h"


class SinkApp: public cSimpleModule, BeaconSubscriber {
public:
    SinkApp();
    virtual ~SinkApp();
    virtual void onNewNeighbor(Neighbor *neighbor);
    virtual void onRemoveNeighbor(Neighbor *neighbor);
    virtual void onNeighborChanged(Neighbor *neighbor);
protected:
    int numInitStages() const {return std::max(cSimpleModule::numInitStages(), 5);}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
private:
    int localPort, destPort;
    UDPSocket socket;
    BeaconsApp *beaconsApp;
    BackBoneApp *backBoneModule;
    int wifiInterface;
    int backboneInterface;
    uint64 myId;
    bool useAck;
    bool useBroadcast;
    simsignal_t ackTx;
    simsignal_t dataRx;

    void processDtnData(DTNDataMsg *msg);
    DTNDataAck *generateDtnAck(const DTNDataMsg *msg);
};

#endif /* SINKAPP_H_ */
