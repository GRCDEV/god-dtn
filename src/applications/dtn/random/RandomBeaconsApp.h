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

#ifndef RANDOMBEACONSAPP_H_
#define RANDOMBEACONSAPP_H_

#include "BeaconsApp.h"
#include "RandomNeighbor.h"
class RandomBeaconsApp: public BeaconsApp {
public:
    RandomBeaconsApp();
    virtual ~RandomBeaconsApp();
private:
    std::vector<NavigationSystem::Ap> poaList;

    virtual void addExtraInfo(BeaconPkt *beacon);
    virtual void readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh);
    virtual bool hasChanged(Neighbor *neighbor);
    virtual Neighbor *createNeighbor();
};

#endif /* DISTANCEBEACONSAPP_H_ */
