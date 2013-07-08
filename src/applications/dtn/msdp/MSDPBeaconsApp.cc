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

#include "MSDPBeaconsApp.h"
#include "MsdpNeighbor.h"
#include "MSDPDataMsg_m.h"

Define_Module(MSDPBeaconsApp);

MSDPBeaconsApp::MSDPBeaconsApp() {
    // TODO Auto-generated constructor stub

}

MSDPBeaconsApp::~MSDPBeaconsApp() {
    // TODO Auto-generated destructor stub
}

void MSDPBeaconsApp::initialize(int stage)
{
    BeaconsApp::initialize(stage);
    if(stage != 3){
        return;
    }
    ASSERT(nav != NULL);
    confidence = par("routeConfidence");
    beta = par("qBetaFactor");
    alpha = par("alpha");
    dtnProtocol =  ModuleAccess<DtnOneCopyProtocol>("dtnProtocol").get();
}

void MSDPBeaconsApp::addExtraInfo(BeaconPkt *beacon)
{
    MSDPInfo *dtnInfo = new MSDPInfo();
    dtnInfo->setDtnIndex(getMyDTNIndex());
    dtnInfo->setByteLength(sizeof(double));
    beacon->encapsulate(dtnInfo);
}

double MSDPBeaconsApp::getMyDTNIndex()
{
    double distance = nav->getCurrentPosition().distance(nav->getClosestPoa().omnetPosition);
    double dtnIndex = calcDtnIndex();
    return (2-alpha)*dtnIndex + alpha*1/distance;

}

void MSDPBeaconsApp::readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh)
{
    MsdpNeighbor *msdpNeigh = dynamic_cast<MsdpNeighbor*>(neighbor);
    ASSERT(msdpNeigh != NULL);
    if(msdpNeigh->getNodeType() == Sink){
        msdpNeigh->setDtnIndex(MAX_DTN_INDEX);
    }
    else{
        MSDPInfo *info = check_and_cast<MSDPInfo *>(beacon->decapsulate());
        msdpNeigh->setDtnIndex(info->getDtnIndex());
        delete info;
    }

}

double MSDPBeaconsApp::calcDtnIndex(){
    double dtnIndex;

    if(nav->getNumOp() == 0){
        return 0.0;
    }
    double timeTo = nav->getTimeToNextTxOpportunity();
    double tau = std::min(log10(timeTo+1)/log10(MAX_DTN_DELAY), 1.0);

    if(tau == 0){
        //Ensure that a SINK will always have a better DTN_INDEX
        return MAX_DTN_NODE_INDEX;
    }
    else{
        double duration = nav-> getDurationNextTxOpportunity();
        double dataBytes = duration * dtnProtocol->getBitrate()/8;

        double q = dtnProtocol->getBufferByteSize()/dataBytes;
        double Q;
        if(q == 0){
            Q = 1;
        }
        else if( q > 1 ){
            Q = 0;
        }
        else {
            Q = std::max(log(beta*(1-q))/log(beta), 0.0);
        }

        dtnIndex = (confidence*confidence)*Q/tau;

        if(dtnIndex > MAX_DTN_NODE_INDEX){
            dtnIndex = MAX_DTN_NODE_INDEX;
        }

        return dtnIndex;
    }
}

Neighbor *MSDPBeaconsApp::createNeighbor()
{
    return new MsdpNeighbor();
}
