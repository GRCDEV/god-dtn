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

#ifndef DTNCOMMON_H_
#define DTNCOMMON_H_

#include <omnetpp.h>

#define MAX_DTN_PACKET_SIZE 2250

enum DtnPort{
    SINK_PORT,
    BEACON_PORT,
    DTN_PORT
};

enum DtnPacketType{
    DTN_DATA,
    DTN_ACK
};


struct DTNFragment{
    uint64 srcId;
    uint64 dstId;
    uint32 msgId;
    uint32  seqN;
    uint32  totalN;
    /*
     * Each hop traversed must decrement this value.
     * A fragment which hop value is 1 can be only sent to a sink.
     * A fragment which hop value is 0 can traverse infinite hops.
     */
    uint8  hops;
    uint32 size; //inBytes
    simtime_t timeStamp;
};

class DTNUnique{
public:
    uint64 srcId;
    uint32 msgId;
    uint32 seqN;

    bool operator< (const DTNUnique& rhs) const
    {
        if(srcId< rhs.srcId ){
            return true;
        }
        else if( srcId==rhs.srcId){
            if(msgId<rhs.msgId){
                return true;
            }else if(msgId==rhs.msgId){
                if(seqN<rhs.seqN){
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
        return false;
    }

    bool operator== (const DTNUnique& rhs) const{
        if(srcId == rhs.srcId && msgId == rhs.msgId && seqN == rhs.seqN )
            return true;
        else
            return false;
    }
};
#endif /* DTNCOMMON_H_ */
