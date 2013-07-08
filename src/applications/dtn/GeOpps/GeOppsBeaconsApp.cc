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

#include "GeOppsBeaconsApp.h"
#include <vector>

Define_Module(GeOppsBeaconsApp);

GeOppsBeaconsApp::GeOppsBeaconsApp() {
    // TODO Auto-generated constructor stub

}

GeOppsBeaconsApp::~GeOppsBeaconsApp() {
    // TODO Auto-generated destructor stub
}

void GeOppsBeaconsApp::initialize(int stage)
{
    BeaconsApp::initialize(stage);
    if(stage != 3){
        return;
    }
    ASSERT(nav != NULL);
}

void GeOppsBeaconsApp::addExtraInfo(BeaconPkt *beacon)
{
    GeOppsData *dtnInfo = new GeOppsData();
    dtnInfo->setMetd(getMyMetd());
    dtnInfo->setByteLength(sizeof(double));
    beacon->encapsulate(dtnInfo);
}

void GeOppsBeaconsApp::readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh)
{
    GeOppsNeighbor *geOppsNeigh = dynamic_cast<GeOppsNeighbor*>(neighbor);
    ASSERT(geOppsNeigh != NULL);
    if(geOppsNeigh->getNodeType() == Sink){
        geOppsNeigh->setMetd(0);
    }
    else{
        GeOppsData *info = check_and_cast<GeOppsData *>(beacon->decapsulate());
        geOppsNeigh->setMetd(info->getMetd());
        delete info;
    }
}

double GeOppsBeaconsApp::getMyMetd()
{
    double time;
    double distance;
    double speed;
    Coord nearestPoint = nav->getNearestPointInRouteToPoa(time, distance, speed);
    if(speed == 0){
        speed = nav->getAverageSpeed();
    }
    return time + distance/speed;
}

Neighbor *GeOppsBeaconsApp::createNeighbor()
{
    return new GeOppsNeighbor();
}



