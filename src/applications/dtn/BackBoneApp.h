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

#ifndef BACKBONEAPP_H_
#define BACKBONEAPP_H_

#include <csimplemodule.h>
#include "DTNcommon.h"
#include "UDPSocket.h"
#include "DTNDataMsg_m.h"
#include "EpidemicProtocol.h"

class BackBoneApp: public cSimpleModule {

public:
    BackBoneApp();
    virtual ~BackBoneApp();
    void registerEpidemicProto(EpidemicProtocol *proto);
    void unRegisterEpidemicProto(EpidemicProtocol *proto);
protected:
    int numInitStages() const {return std::max(cSimpleModule::numInitStages(), 1);}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
private:
    uint interface;
    uint localPort;
    UDPSocket socket;

    typedef struct _dtnMsg{
        uint32 msgId;
        uint64 srcId;

        bool operator< (const _dtnMsg& rhs) const
        {
            if(srcId< rhs.srcId ){
                return true;
            }
            else if( srcId == rhs.srcId){
                if(msgId<rhs.msgId){
                    return true;
                }
            }
            return false;
        }

    }DtnMsg;

    std::map<DtnMsg, std::set<uint32> > receiving;
    std::set<DtnMsg> received;
    std::set<EpidemicProtocol*> subscribrers;
    simsignal_t msgRcv;
    simsignal_t frgRcv;
    simsignal_t msgDelay;
    simsignal_t frgDelay;

    void processDtnData(DTNDataMsg *msg);
    void informSubscribers(uint64 srcId, uint32 msgId, uint32 seqN);
};

#endif /* BACKBONEAPP_H_ */
