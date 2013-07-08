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

#ifndef EPIBEACONSAPP_H_
#define EPIBEACONSAPP_H_

#include "BeaconsApp.h"
#include "EpidemicProtocol.h"
#include <omnetpp.h>
class EpiBeaconsApp: public BeaconsApp {
public:
    EpiBeaconsApp();
    virtual ~EpiBeaconsApp();
protected:
    virtual void initialize(int stage);
private:
    EpidemicProtocol *epiProtocol;

    virtual void addExtraInfo(BeaconPkt *beacon);
    virtual void readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh);
    virtual bool hasChanged(Neighbor *neighbor);
    virtual Neighbor *createNeighbor();

};

#endif /* EPIBEACONSAPP_H_ */
