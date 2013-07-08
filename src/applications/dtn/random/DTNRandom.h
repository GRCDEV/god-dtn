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

#ifndef DTNRANDOM_H_
#define DTNRANDOM_H_

#include "DtnOneCopyProtocol.h"
#include "RandomNeighbor.h"
#include "RandomBeaconsApp.h"
#include "IDTNProtocol.h"
#include "omnetpp.h"

class DTNRandom: public DtnOneCopyProtocol{
public:
    DTNRandom();
    virtual ~DTNRandom();
protected:
    virtual void initialize(int stage);
private:
    double minP;
    struct randomComparator{
      virtual bool operator() (Neighbor* const& lhs, Neighbor* const& rhs) const
      {
          RandomNeighbor *dLhs = dynamic_cast<RandomNeighbor *>(lhs);
          RandomNeighbor *dRhs = dynamic_cast<RandomNeighbor *>(rhs);
          ASSERT(dLhs != NULL && dRhs != NULL);
          if(lhs == rhs){
                        return false;
                    }
          if(dLhs->getP() != dRhs->getP()){
              return dLhs->getP()> dRhs->getP();
          }
          else{
              return dLhs->getLastUpdate() < dRhs->getLastUpdate();
          }
      }
    };

    virtual bool isBetterThanMe(Neighbor *neighbor);
};

#endif /* DTNRANDOM_H_ */
