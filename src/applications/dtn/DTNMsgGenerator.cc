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

#include "DTNMsgGenerator.h"

Define_Module(DTNMsgGenerator);

DTNMsgGenerator::DTNMsgGenerator() {
    // TODO Auto-generated constructor stub

}

DTNMsgGenerator::~DTNMsgGenerator() {
    // TODO Auto-generated destructor stub

    cancelAndDelete(newMsg);

}


void DTNMsgGenerator::initialize(int stage)
{
    newMsg = new cMessage("NewMessage");
    numberOfMsg = par("numberOfMessages");
    msgCount = 0;
    msgId = intrand(1000);
    double delay = par("interMsgTime").doubleValue();
    if(numberOfMsg != 0 && delay != 0){
        scheduleAt(simTime()+delay+par("phaseTime").doubleValue(), newMsg);
    }
    msgGenerated = registerSignal("msgGenerated");
    dtnProtocol = ModuleAccess<IDTNProtocol>("dtnProtocol").get();
}




void DTNMsgGenerator::handleMessage(cMessage *msg)
{
    if( msg->isSelfMessage() && msg == newMsg){
        double msgSize = par("msgSize");
        dtnProtocol->sendMessage(0, msgId++, true, msgSize);
        emit(msgGenerated, msgSize);
        double delay = par("interMsgTime");
        msgCount++;
        if(msgCount != numberOfMsg){
            scheduleAt(simTime()+delay, newMsg);
        }
    }
    else{
        ASSERT("Message not found");
    }
}



