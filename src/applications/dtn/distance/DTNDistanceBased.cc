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

#include "DTNDistanceBased.h"

Define_Module(DTNDistanceBased)

DTNDistanceBased::DTNDistanceBased() {
    // TODO Auto-generated constructor stub

}

DTNDistanceBased::~DTNDistanceBased() {
    // TODO Auto-generated destructor stub
}

void DTNDistanceBased::initialize(int stage)
{
    DtnOneCopyProtocol::initialize(stage);
    if(stage != 4){
        return;
    }
    distBeacons = dynamic_cast<DistanceBeaconsApp*>(beaconsApp);
    ASSERT(distBeacons != NULL);
    sortedNeighbors = new std::set<Neighbor *, std::function<bool(Neighbor* const&, Neighbor* const&)> > (distanceComparator());
}

bool DTNDistanceBased::isBetterThanMe(Neighbor *neighbor)
{
    DistanceNeighbor *distanNeigh = dynamic_cast<DistanceNeighbor*>(neighbor);
    ASSERT(distanNeigh != NULL);
    double myDist = distBeacons->getMySqrDistanceToPoa();
    return distanNeigh->getSqrDistanceToPoa() < myDist;
}



