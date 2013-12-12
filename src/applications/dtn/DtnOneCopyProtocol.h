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

#ifndef DTNONECOPYPROTOCOL_H_
#define DTNONECOPYPROTOCOL_H_

#include "IDTNProtocol.h"
#include "BeaconsApp.h"
#include "DTNDataMsg_m.h"
#include "DTNcommon.h"
#include <functional>

#define ACK_TIME_OUT 21

class DtnOneCopyProtocol: public IDTNProtocol, BeaconSubscriber {
public:
    DtnOneCopyProtocol();
    virtual ~DtnOneCopyProtocol();
    /*
     * fragment a message and buffer it.
     */
    virtual void sendMessage(uint64 destId, uint64 msgId, bool broadcast, uint32  length);
    virtual void onNewNeighbor(Neighbor *neighbor);
    virtual void onRemoveNeighbor(Neighbor *neighbor);
    virtual void onNeighborChanged(Neighbor *neighbor);
    uint getBitrate() const;
    uint getBufferByteSize() const;
protected:
    int numInitStages() const
    {
        return std::max(cSimpleModule::numInitStages(), 5);
    }

    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    BeaconsApp *beaconsApp;
    /*
     * List containing Neighbors, only better neighbors than me must be added
     * Subclasses must initialize this variable in order to store Neighbor properly
     */
    std::set<Neighbor*,std::function<bool(Neighbor*const & , Neighbor*const & )> > *sortedNeighbors;
    std::map<uint64,Neighbor*> neighbors;
private:
    int localPort, destPort;
    UDPSocket socket;
    int wifiInterface;
    uint64 myId;
    uint32 msgId;

    struct timeSeq
    {
        simtime_t time;
        uint32 seq;
    public:
        virtual bool operator ()(const timeSeq & lhs, const timeSeq & rhs) const
        {
            if(lhs.time == rhs.time){
                return lhs.seq < rhs.seq;
            }else{
                return lhs.time < rhs.time;
            }
        }

        virtual bool operator <(const timeSeq & rhs) const{
            if(this->time == rhs.time){
                return this->seq<rhs.seq;
            }
            else{
                return this->time<rhs.time;
            }
        }
    };

    /*
     * stored messages sorted by their timestamp
     */
    std::map<timeSeq, DTNFragment> buffer;

    /*
     * Map used to cancel ACK timeouts when an ACK is received.
     * ACK timeout self messages carry an array of fragments pending of confirmation as contextInfo
     * so it is easy to reenqueue fragments
     */
    std::map<uint32, cMessage*> msgIdAckMap;

    /*
     * Number of message pending of confirmation from a neighbor
     */
    std::map<uint64, uint8> neighWindow;

    cMessage *transmission;

    /*
     * Parameters
     */
    /*
     * Time to wait for an ACK before reenqueue the message and remove the neighbor from list.
     */
    simtime_t ackTimeOut;
    /*
     * Max transmission window size
     */
    uint windowSize;
    /*
     * Bitrate in bits per second
     * It is used to calculate the time between two consecutive dataMessages
     */
    uint bitrate;
    /*
     * Max number of hops per fragment. 0 for unlimited.
     */
    uint maxHops;
    /*
     * Nodes beyond this limits are ignored from neighbor list
     */
    double maxRange;
    double maxSqrRange;
    /*
     * Whether use ACK messages or not
     */
    bool useAck;
    /*
     * Whether use broadcast or not
     */
    bool useBroadcast;
    /*
     * amount of redundancy added to messages
     */
    double redundancy;
    simsignal_t fragmentGenerated;
    simsignal_t dataTx;
    simsignal_t directDataTx;
    simsignal_t dataRx;
    simsignal_t ackTx;
    simsignal_t ackRx;
    simsignal_t ackTO;
    /*
     * Process a DTNData msg. Enqueue its contents and check if a transmission can occur now.
     */
    void processDTNData(DTNDataMsg *msg);
    /*
     * Process an ACK message. Cancel the ack-timeout self message and remove data from the buffer
     */
    void processACK(DTNDataAck *msg);
    /*
     * Process an ACK timeout cancel ack selfmessage and reenqueue packets
     */
    void processACKTimeOut(cMessage *msg);
    /*
     * Equeue a frangmet into the buffer
     */
    void enQueueFragment(DTNFragment fragment);
    /*
     * dequeue fragments and generate a DtnDataMsg
     */
    DTNDataMsg *generateDtnData(const Neighbor *neigh, int nodeType);
    /*
     * Generate a DTNDataAck to confirm a message
     */
    DTNDataAck *generateDtnAck(const DTNDataMsg *msg);
    /*
     * schedule an ACK timeout for a given DtnDataMsg
     * The scheduled message will contain
     */
    void scheduleAckTimeOut(DTNDataMsg *msg);
    /*
     * check if neighborlist contains at least one element
     */
    bool hasNeighbors();
    /*
     * check if there are packets in the buffer
     */
    bool hasPackets();
    /*
     * return the best available neighbor inside the communication range.
     * return NULL if no neighbor is inside the communication range.
     */
    Neighbor *getBestNeighbor();
    /*
     * start a transmission process. Only a transmission can be scheduled.
     */
    void startTransmission(){
        startTransmission(0);
    }
    void startTransmission(double delay);
    /*
     * do a transmission, schedule a new one if possible.
     */
    void doTransmission();
    /*
     * Update neighbors' locations using the received location and speed.
     * neighbors out of range will be removed from list.
     */
    void updateNeighborList();
    /*
     * this function compare a neighbor against me.
     * Subclasses must implement it.
     */
    virtual bool isBetterThanMe(Neighbor *neighbor) = 0;
};

#endif /* DTNONECOPYPROTOCOL_H_ */
