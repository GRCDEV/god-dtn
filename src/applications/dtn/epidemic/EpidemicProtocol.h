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

#ifndef EPIDEMICAPP_H_
#define EPIDEMICAPP_H_

#include <csimplemodule.h>
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
#include "IDTNProtocol.h"
#include "EpiNeighbor.h"
#include "Epidemic_m.h"

#include <map>

#define PURGE_BUFFER 20
#define CONFIRMATION_TIME_OUT 21

class BackBoneApp;

class EpidemicProtocol: public IDTNProtocol, BeaconSubscriber {
public:
    EpidemicProtocol();
    virtual ~EpidemicProtocol();
    virtual void sendMessage(uint64 destId, uint64 msgId, bool broadcast, uint32  length);
    virtual void onNewNeighbor(Neighbor *neighbor);
    virtual void onRemoveNeighbor(Neighbor *neighbor);
    virtual void onNeighborChanged(Neighbor *neighbor);
    simtime_t getLastAddedFragment() const;
    void notifyMessageReceived(uint64 srcId, uint32 msgId, uint32 seqN);
protected:
    int numInitStages() const {return std::max(cSimpleModule::numInitStages(), 5);}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
private:
    simtime_t packetTimeout;
    int localPort, destPort;
    UDPSocket socket;
    BeaconsApp *beaconsApp;
    int wifiInterface;
    uint64 myId;
    uint32 msgId;
    uint8 maxHops;
    simtime_t lastAddedFragment;
    std::map<uint64, simtime_t> lastSentMsg;
    std::set<DTNUnique> delivered;
    std::set<DTNUnique> onBuffer;
    /*
     * store messages sorted by their timestamp
     */
    std::map<DTNUnique, DTNFragment> buffer;
    BackBoneApp *bb;
    /*
     * enqueue a fragment to the buffer
     */
    void enQueueFragment(DTNFragment fragment);
    void processOffer(EpidemicPktOffer *msg);
    void processAsk(EpidemicPktAsk *msg);
    void processDTNData(DTNDataMsg *msg);
    void sendOffer(IPvXAddress ip, uint64 nodeId);
    void emptyBufferOnSink(IPvXAddress ip, uint64 nodeId);
};

#endif /* EPIDEMICAPP_H_ */
