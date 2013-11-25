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

#ifndef __PRUEBASENCILLA_BEACONS_H_
#define __PRUEBASENCILLA_BEACONS_H_

#include <omnetpp.h>
#include <map>
#include <string>
#include "NotificationBoard.h"
#include <cmath>
#include "Ieee80211Consts.h"
#include "INETDefs.h"
#include "IPvXAddressResolver.h"
#include "IPv4InterfaceData.h"
#include "InterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "UDPControlInfo_m.h"
#include "UDPSocket.h"
#include "MobilityBase.h"
#include "BeaconPkt_m.h"
#include "Neighbor.h"
#include "DTNcommon.h"
#include "NavigationSystem.h"

class BeaconSubscriber
{
    public:
        virtual ~BeaconSubscriber(){};

        virtual void onNewNeighbor(Neighbor *neighbor) = 0;
        virtual void onNeighborChanged(Neighbor *neighbor) = 0;
        virtual void onRemoveNeighbor(Neighbor *neighbor) = 0;
};


class BeaconsApp : public cSimpleModule
{
  public:
    ~BeaconsApp();
    void subscribeNews(BeaconSubscriber *subscriber);
    void unSubscribeNews(BeaconSubscriber *subscriber);
    void sendBeaconNow();
    enum NodeType getType() const;
    uint64 getMyId() const;
    Coord getMyLoc() const;
    Neighbor *getNeighborInfo(uint64 id);
  protected:
    int numInitStages() const {return std::max(cSimpleModule::numInitStages(), 4);}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    bool isNew(uint64 id);
    NavigationSystem *nav;
    std::map<uint64,Neighbor*> neighborsList;
  private:
    enum selfType{
        NEW_BEACON,
        REMOVE_NEIGH
    };
    MobilityBase *mobility;
    bool debug;
    double interBeaconTime;
    uint beaconID;
    UDPSocket socket;
    int localPort, destPort;
    IPv4Address myAddr;
    IPv4Address myServiceAddr;
    enum NodeType type;
    int outputInterface;
    uint64 myId;
    std::list<BeaconSubscriber*> subscriberList;
    std::map<uint64, cMessage *> msgMap;

    simsignal_t newNeighbor;
    simsignal_t rmNeighbor;

    void sendNewBeacon(void);
    void processBeacon(BeaconPkt *beacon);
    /*
     * Extra info is added through encapsulation, subclases must override this two methods
     */
    virtual void addExtraInfo(BeaconPkt *beacon){
        ;
    }
    virtual void readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh){
        ;
    }
    /*
     * Subclasses must override this method, by default only new neighbor are notified
     * always return false
     */
    virtual bool hasChanged(Neighbor *neighbor);
    /*
     * subclasses must override this method to generate a [TYPE]Neighbor object
     */
    virtual Neighbor *createNeighbor();
    /*
     * Inform to all subscribers of a NewNeighbor
     */
    void informNewNeighborSubscribers(Neighbor *neighbor);
    void informRemoveNeighborSubscribers(Neighbor *neighbor);
    void informOnChagedNeighborSubscribers(Neighbor *neighbor);
};



#endif
