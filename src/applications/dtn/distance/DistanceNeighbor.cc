/*
 * DistanceNeighbor.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: sertinell
 */

#include "DistanceNeighbor.h"

DistanceNeighbor::DistanceNeighbor() {
    // TODO Auto-generated constructor stub

}

DistanceNeighbor::~DistanceNeighbor() {
    // TODO Auto-generated destructor stub
}

double DistanceNeighbor::getSqrDistanceToPoa() const
{
    return srqDistanceToPoa;
}



void DistanceNeighbor::setSqrDistanceToPoa(double distanceToPoa)
{
    this->srqDistanceToPoa = distanceToPoa;
}











