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

#ifndef DTNMSGGENERATOR_H_
#define DTNMSGGENERATOR_H_

#include <csimplemodule.h>
#include <IDTNProtocol.h>
#include <omnetpp.h>
#include <ModuleAccess.h>

class DTNMsgGenerator: public cSimpleModule {
public:
    DTNMsgGenerator();
    virtual ~DTNMsgGenerator();
protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
private:
    cMessage *newMsg;
    int numberOfMsg;
    int msgCount;
    IDTNProtocol *dtnProtocol;
    simsignal_t msgGenerated;
    uint32 msgId;
};

#endif /* DTNMSGGENERATOR_H_ */
