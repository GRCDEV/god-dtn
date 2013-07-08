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

#ifndef MSDPNEIGHBOR_H_
#define MSDPNEIGHBOR_H_

#include "Neighbor.h"

#define MAX_DTN_INDEX 10000
#define MAX_DTN_NODE_INDEX 10
#define MAX_DTN_DELAY 3600

class MsdpNeighbor: public Neighbor {
public:
    MsdpNeighbor();
    MsdpNeighbor(Neighbor *neighbor);
    virtual ~MsdpNeighbor();
    double getDtnIndex() const;
    void setDtnIndex(double dtnIndex);
private:
    double DtnIndex;
};

#endif /* MSDPNEIGHBOR_H_ */
