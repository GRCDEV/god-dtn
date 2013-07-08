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

#ifndef DTNGEOPPS_H_
#define DTNDTNGEOPPS_H_

#include "DtnOneCopyProtocol.h"
#include "MsdpNeighbor.h"
#include "MSDPBeaconsApp.h"
#include "IDTNProtocol.h"

class DTNMsdp: public DtnOneCopyProtocol{
public:
    DTNMsdp();
    virtual ~DTNMsdp();
protected:
    virtual void initialize(int stage);
private:
    MSDPBeaconsApp *msdpBeacons;
    double penalty;
    struct msdpComparator{
      virtual bool operator() (Neighbor* const& lhs, Neighbor* const& rhs) const
      {
          MsdpNeighbor *dLhs = dynamic_cast<MsdpNeighbor *>(lhs);
          MsdpNeighbor *dRhs = dynamic_cast<MsdpNeighbor *>(rhs);
          ASSERT(dLhs != NULL && dRhs != NULL);
          if(lhs == rhs){
              return false;
          }
          if(dLhs->getDtnIndex() != dRhs->getDtnIndex()){
              return dLhs->getDtnIndex() > dRhs->getDtnIndex();
          }
          else {
              return dLhs->getId() > dRhs->getId();
          }
      }
   };

    virtual bool isBetterThanMe(Neighbor *neighbor);
};

#endif /* DTNGeOpps_H_ */
