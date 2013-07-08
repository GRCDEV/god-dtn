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

#include "DTNRandom.h"

Define_Module(DTNRandom)

DTNRandom::DTNRandom() {
    // TODO Auto-generated constructor stub

}

DTNRandom::~DTNRandom() {
    // TODO Auto-generated destructor stub
}

void DTNRandom::initialize(int stage)
{
    DtnOneCopyProtocol::initialize(stage);
    if(stage != 4){
        return;
    }
    minP = par("minP").doubleValue();
}

bool DTNRandom::isBetterThanMe(Neighbor *neighbor)
{
    RandomNeighbor *rndNeigh = dynamic_cast<RandomNeighbor*>(neighbor);
    ASSERT(rndNeigh != NULL);
    return rndNeigh->getP() > minP;
}



