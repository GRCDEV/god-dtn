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

#include "DTNGeOpps.h"

Define_Module(DTNGeOpps)

DTNGeOpps::DTNGeOpps() {
    // TODO Auto-generated constructor stub

}

DTNGeOpps::~DTNGeOpps() {
    // TODO Auto-generated destructor stub
}

void DTNGeOpps::initialize(int stage)
{
    DtnOneCopyProtocol::initialize(stage);
    if(stage != 4){
        return;
    }
    geOppsBeacons = dynamic_cast<GeOppsBeaconsApp*>(beaconsApp);
    ASSERT(geOppsBeacons != NULL);
    sortedNeighbors = new std::set<Neighbor *, std::function<bool(Neighbor* const&, Neighbor* const&)> > (geOppsComparator());
}




bool DTNGeOpps::isBetterThanMe(Neighbor *neighbor)
{
    GeOppsNeighbor *geOppsNeigh = dynamic_cast<GeOppsNeighbor*>(neighbor);
    ASSERT(geOppsNeigh != NULL);
    double myMetd = geOppsBeacons->getMyMetd();
    return geOppsNeigh->getMetd() < myMetd;
}



