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

#include "DTNMsdp.h"

Define_Module(DTNMsdp)

DTNMsdp::DTNMsdp() {
    // TODO Auto-generated constructor stub

}

DTNMsdp::~DTNMsdp() {
    // TODO Auto-generated destructor stub
}

void DTNMsdp::initialize(int stage)
{
    DtnOneCopyProtocol::initialize(stage);
    if(stage != 4){
        return;
    }
    msdpBeacons = dynamic_cast<MSDPBeaconsApp*>(beaconsApp);
    ASSERT(msdpBeacons != NULL);
    sortedNeighbors = new std::set<Neighbor *, std::function<bool(Neighbor* const&, Neighbor* const&)> > (msdpComparator());
    penalty = par("transmissionPenalty");
}

bool DTNMsdp::isBetterThanMe(Neighbor *neighbor)
{
    MsdpNeighbor *msdpNeigh = dynamic_cast<MsdpNeighbor*>(neighbor);
    ASSERT(msdpNeigh != NULL);
    if(msdpNeigh->getNodeType() == Sink){
        return true;
    }
    double myDtnIndex = msdpBeacons->getMyDTNIndex();
    return msdpNeigh->getDtnIndex()*penalty > myDtnIndex;
}
