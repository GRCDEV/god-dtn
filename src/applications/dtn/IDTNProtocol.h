/*
 * IDTNProtocol.h
 *
 *  Created on: Oct 26, 2012
 *      Author: sertinell
 */

#ifndef IDTNPROTOCOL_H_
#define IDTNPROTOCOL_H_

#include <csimplemodule.h>

class IDTNProtocol: public cSimpleModule {
public:
    IDTNProtocol(){;}
    virtual ~IDTNProtocol(){;}
    virtual void sendMessage(uint64 destId, uint64 msgId, bool broadcast, uint32  length) = 0;
protected:
    uint32 fragmentSize;
};

#endif /* IDTNPROTOCOL_H_ */
