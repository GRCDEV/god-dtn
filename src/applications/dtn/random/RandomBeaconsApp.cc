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

#include "RandomBeaconsApp.h"

Define_Module(RandomBeaconsApp);

RandomBeaconsApp::RandomBeaconsApp() {
    // TODO Auto-generated constructor stub

}

RandomBeaconsApp::~RandomBeaconsApp() {
    // TODO Auto-generated destructor stub
}

void RandomBeaconsApp::addExtraInfo(BeaconPkt *beacon)
{
    /*
     * No extra info is added to beacons!
     */
}

void RandomBeaconsApp::readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh)
{
    /*
     * No extra info is contained in beacons but distance is calculated and stored.
     */
    RandomNeighbor *rndNeigh = dynamic_cast<RandomNeighbor*>(neighbor);
    ASSERT(rndNeigh != NULL);
    if(rndNeigh->getNodeType() == Sink){
        rndNeigh->setP(1);
    }
    else{
        double p = 0;
        /*
         * If it is a new node, generate a new random value
         */
        if(newNeigh){
            p = uniform(0,1);
        }
        /*
         * else use the old value
         */
        else{
            RandomNeighbor *oldRndNeigh = dynamic_cast<RandomNeighbor*>(getNeighborInfo(rndNeigh->getId()));
            ASSERT(rndNeigh != NULL);
            p = oldRndNeigh->getP();
        }
        rndNeigh->setP(p);
    }
}

bool RandomBeaconsApp::hasChanged(Neighbor *neighbor)
{
    return false;
}

Neighbor *RandomBeaconsApp::createNeighbor()
{
    return new RandomNeighbor();
}



