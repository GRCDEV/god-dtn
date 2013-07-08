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

#ifndef DTNDISTANCEBASED_H_
#define DTNDISTANCEBASED_H_

#include "DtnOneCopyProtocol.h"
#include "DistanceNeighbor.h"
#include "DistanceBeaconsApp.h"
#include "IDTNProtocol.h"
#include "omnetpp.h"

class DTNDistanceBased: public DtnOneCopyProtocol{
public:
    DTNDistanceBased();
    virtual ~DTNDistanceBased();
protected:
    virtual void initialize(int stage);
private:
    DistanceBeaconsApp *distBeacons;
    struct distanceComparator{
      virtual bool operator() (Neighbor* const& lhs, Neighbor* const& rhs) const
      {
          DistanceNeighbor *dLhs = dynamic_cast<DistanceNeighbor *>(lhs);
          DistanceNeighbor *dRhs = dynamic_cast<DistanceNeighbor *>(rhs);
          ASSERT(dLhs != NULL && dRhs != NULL);
          if(lhs == rhs){
                        return false;
                    }
          if(dLhs->getSqrDistanceToPoa() != dRhs->getSqrDistanceToPoa()){
              return dLhs->getSqrDistanceToPoa()< dRhs->getSqrDistanceToPoa();
          }
          else{
              return dLhs->getId()<dRhs->getId();
          }
      }
    };

    virtual bool isBetterThanMe(Neighbor *neighbor);
};

#endif /* DTNDISTANCEBASED_H_ */
