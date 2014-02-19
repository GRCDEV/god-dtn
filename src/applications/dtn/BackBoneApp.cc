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

#include "BackBoneApp.h"

Define_Module(BackBoneApp);

BackBoneApp::BackBoneApp() {

}

BackBoneApp::~BackBoneApp() {

}

void BackBoneApp::initialize(int stage)
{
    localPort = DTN_PORT;
    msgRcv = registerSignal("msgReceived");
    frgRcv = registerSignal("fragmentReceived");
    msgDelay = registerSignal("msgReceivedDelay");
    frgDelay = registerSignal("fragmentReceivedDelay");
    msgPartial = registerSignal("msgPartial");
}



void BackBoneApp::handleMessage(cMessage *msg)
{
    ASSERT(!msg->isSelfMessage());
    if (dynamic_cast<DTNDataMsg *>(msg) != NULL){
        DTNDataMsg *data = check_and_cast<DTNDataMsg *>(msg);
        processDtnData(data);
    }else{
        ASSERT("Message not recognized");
    }
}



void BackBoneApp::registerEpidemicProto(EpidemicProtocol *proto)
{
    subscribrers.insert(proto);
}

void BackBoneApp::processDtnData(DTNDataMsg *msg)
{
    for(uint i = 0; i != msg->getFragmentsArraySize(); i++){
        DTNFragment fragment = msg->getFragments(i);
        DtnMsg dtnMsg;
        dtnMsg.msgId = fragment.msgId;
        dtnMsg.srcId = fragment.srcId;
        emit(frgRcv, fragment.size);
        double fragDelay = (simTime().dbl()-fragment.timeStamp.dbl());
        ASSERT(fragDelay > 0);
        emit(frgDelay, fragDelay);
        if(received.find(dtnMsg) == received.end()){
            if(receiving.find(dtnMsg) == receiving.end() ){
                //first fragment of a message have been received
                std::set<uint32> temp;
                temp.insert(fragment.seqN);
                receiving.insert(std::pair<DtnMsg,std::set<uint32> >{dtnMsg, temp});
            }
            else{
                ASSERT(receiving.at(dtnMsg).size() != 0 );
                std::pair<std::set<uint32>::iterator, bool> ret = receiving.at(dtnMsg).insert(fragment.seqN);

                if(ret.second == false){
                    //Fragment received twice
                }
            }
            if(receiving.at(dtnMsg).size() >= fragment.totalN){
                received.insert(dtnMsg);
                emit(msgRcv, (fragment.totalN*(fragment.size-sizeof(DTNFragment))));
                emit(msgDelay, fragDelay);
                informSubscribers(dtnMsg.srcId, dtnMsg.msgId, fragment.totalN);
                receiving.erase(dtnMsg);
            }
        }
    }
    delete msg;
}


void BackBoneApp::unRegisterEpidemicProto(EpidemicProtocol *proto)
{
    subscribrers.erase(proto);
}

void BackBoneApp::finish() {
    for(std::map<DtnMsg, std::set<uint32> >::iterator i = receiving.begin(); i!=receiving.end(); i++){
        emit(msgPartial, i->second.size());
    }
}

void BackBoneApp::informSubscribers(uint64 srcId, uint32 msgId, uint32 seqN)
{
    for(std::set<EpidemicProtocol *>::iterator proto=subscribrers.begin(); proto != subscribrers.end(); proto++){
        (*proto)->notifyMessageReceived(srcId, msgId, seqN);
    }
}





