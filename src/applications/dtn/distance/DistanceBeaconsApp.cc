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

#include "DistanceBeaconsApp.h"

Define_Module(DistanceBeaconsApp);

DistanceBeaconsApp::DistanceBeaconsApp() {
    // TODO Auto-generated constructor stub

}

DistanceBeaconsApp::~DistanceBeaconsApp() {
    // TODO Auto-generated destructor stub
}

void DistanceBeaconsApp::initialize(int stage)
{
    BeaconsApp::initialize(stage);
    if(stage != 3){
        return;
    }
    ASSERT(nav != NULL);
    poaList = nav->getPoaList();
    ASSERT(!poaList.empty());
}

void DistanceBeaconsApp::addExtraInfo(BeaconPkt *beacon)
{
    /*
     * No extra info is added to beacons!
     */
}

void DistanceBeaconsApp::readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh)
{
    /*
     * No extra info is contained in beacons but distance is calculated and stored.
     */
    DistanceNeighbor *distNeigh = dynamic_cast<DistanceNeighbor*>(neighbor);
    ASSERT(distNeigh != NULL);
    if(distNeigh->getNodeType() == Sink){
        distNeigh->setSqrDistanceToPoa(0);
    }
    else{
        std::vector<NavigationSystem::Ap>::iterator poa = poaList.begin();
        double minSqrDistance = distNeigh->getLocation().sqrdist(poa->omnetPosition);
        poa++;
        while(poa != poaList.end()){
            double sqrDistance = distNeigh->getLocation().sqrdist(poa->omnetPosition);
            if(sqrDistance < minSqrDistance){
                minSqrDistance = sqrDistance;
            }
            poa++;
        };
        distNeigh->setSqrDistanceToPoa(minSqrDistance);
    }
}

bool DistanceBeaconsApp::hasChanged(Neighbor *neighbor)
{
    DistanceNeighbor *old = dynamic_cast<DistanceNeighbor*>(neighborsList.at(neighbor->getId()));
    DistanceNeighbor *dist= dynamic_cast<DistanceNeighbor*>(neighbor);
    ASSERT(old != NULL);
    ASSERT(dist != NULL);
    return old->getLocation() != dist->getLocation();
}

double DistanceBeaconsApp::getMySqrDistanceToPoa()
{
    std::vector<NavigationSystem::Ap>::iterator poa = poaList.begin();
    Coord myLoc = nav->getCurrentPosition();
    double minSqrDistance = myLoc.sqrdist(poa->omnetPosition);
    poa++;
    while(poa != poaList.end()){
        double sqrDistance = myLoc.sqrdist(poa->omnetPosition);
        if(sqrDistance < minSqrDistance){
            minSqrDistance = sqrDistance;
        }
        poa++;
    };
    return minSqrDistance;
}

Neighbor *DistanceBeaconsApp::createNeighbor()
{
    return new DistanceNeighbor();
}



