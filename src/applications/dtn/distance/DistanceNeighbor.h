/*
 * DistanceNeighbor.h
 *
 *  Created on: Nov 9, 2012
 *      Author: sertinell
 */

#ifndef DISTANCENEIGHBOR_H_
#define DISTANCENEIGHBOR_H_

#include "Neighbor.h"

class DistanceNeighbor: public Neighbor {
public:
    DistanceNeighbor();
    virtual ~DistanceNeighbor();
    double getSqrDistanceToPoa() const;
    void setSqrDistanceToPoa(double distanceToPoa);
private:
    double srqDistanceToPoa;
};

#endif /* DISTANCENEIGHBOR_H_ */
