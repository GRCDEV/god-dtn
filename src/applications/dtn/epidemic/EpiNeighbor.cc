/*
 * EpiNeighborh.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: sertinell
 */

#include "EpiNeighbor.h"

EpiNeighbor::EpiNeighbor() {
    // TODO Auto-generated constructor stub

}

EpiNeighbor::~EpiNeighbor() {
    // TODO Auto-generated destructor stub
}

simtime_t EpiNeighbor::getLastBufferUpdate() const
{
    return lastBufferUpdate;
}

void EpiNeighbor::setLastBufferUpdate(simtime_t lastBufferUpdate)
{
    this->lastBufferUpdate = lastBufferUpdate;
}



