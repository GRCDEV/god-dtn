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

#ifndef MSDPBEACONSAPP_H_
#define MSDPBEACONSAPP_H_

#include "BeaconsApp.h"
#include "DtnOneCopyProtocol.h"
#include <omnetpp.h>
class MSDPBeaconsApp: public BeaconsApp {
public:
    MSDPBeaconsApp();
    virtual ~MSDPBeaconsApp();
    double getMyDTNIndex();
protected:
    virtual void initialize(int stage);
private:
    double calcDtnIndex();
    virtual void addExtraInfo(BeaconPkt *beacon);
    virtual void readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh);
    virtual Neighbor *createNeighbor();
    double confidence;
    double beta;
    double alpha;
    DtnOneCopyProtocol *dtnProtocol;
};

#endif /* MSDPBEACONSAPP_H_ */
