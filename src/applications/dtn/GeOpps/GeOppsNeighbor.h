/*
 * GeOppsNeighbor.h
 *
 *  Created on: Nov 27, 2012
 *      Author: sertinell
 */

#ifndef GEOPPSNEIGHBOR_H_
#define GEOPPSNEIGHBOR_H_

#include "Neighbor.h"

class GeOppsNeighbor: public Neighbor {
public:
    GeOppsNeighbor();
    virtual ~GeOppsNeighbor();
    double getMetd() const;
    void setMetd(double metd);
private:
    double metd;
};

#endif /* GEOPPSNEIGHBOR_H_ */
