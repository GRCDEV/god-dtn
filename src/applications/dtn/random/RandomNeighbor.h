/*
 * RandomNeighbor.h
 *
 *  Created on: May 23, 2013
 *      Author: sertinell
 */

#ifndef DISTANCENEIGHBOR_H_
#define DISTANCENEIGHBOR_H_

#include "Neighbor.h"

class RandomNeighbor: public Neighbor {
public:
    RandomNeighbor();
    virtual ~RandomNeighbor();
    double getP() const;
    void setP(double distanceToPoa);
private:
    double p;
};

#endif /* DISTANCENEIGHBOR_H_ */
