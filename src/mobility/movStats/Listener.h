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

#ifndef LISTENER_H_
#define LISTENER_H_

#include <clistener.h>

class Listener: public cListener {
private:
    double speed;
    cComponent* padre;
public:
    Listener(cComponent* padre);
    virtual ~Listener();

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject * obj);

    virtual double getSpeed();
};

#endif /* LISTENER_H_ */
