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
#include "GeOppsNeighbor.h"
#include "GeOppsBeaconsApp.h"
#include "IDTNProtocol.h"

class DTNGeOpps: public DtnOneCopyProtocol{
public:
    DTNGeOpps();
    virtual ~DTNGeOpps();
protected:
    virtual void initialize(int stage);
private:
    GeOppsBeaconsApp *geOppsBeacons;
    struct geOppsComparator{
      virtual bool operator() (Neighbor* const& lhs, Neighbor* const& rhs) const
      {
          GeOppsNeighbor *dLhs = dynamic_cast<GeOppsNeighbor *>(lhs);
          GeOppsNeighbor *dRhs = dynamic_cast<GeOppsNeighbor *>(rhs);
          ASSERT(dLhs != NULL && dRhs != NULL);
          if(lhs == rhs){
              return false;
          }
          if(dLhs->getMetd() != dRhs->getMetd()){
              return dLhs->getMetd() < dRhs->getMetd();
          }
          else {
              return dLhs->getId() < dRhs->getId();
          }
      }
   };

    virtual bool isBetterThanMe(Neighbor *neighbor);
};

#endif /* DTNGeOpps_H_ */
