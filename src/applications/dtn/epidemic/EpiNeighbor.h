/*
 * EpiNeighbor.h
 *
 *  Created on: Oct 29, 2012
 *      Author: sertinell
 */

#ifndef EPINEIGHBOR_H_
#define EPINEIGHBOR_H_

#include "Neighbor.h"

class EpiNeighbor: public Neighbor {
public:
    EpiNeighbor();
    virtual ~EpiNeighbor();
    simtime_t getLastBufferUpdate() const;
    void setLastBufferUpdate(simtime_t lastBufferUpdate);
private:
    simtime_t lastBufferUpdate;
};

#endif /* EPINEIGHBOR_H_ */
