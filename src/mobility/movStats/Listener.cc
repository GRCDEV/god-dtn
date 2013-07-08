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

#include "Listener.h"
#include "MobilityBase.h"

Listener::Listener(cComponent* padre) {
    speed = -1;
    this->padre = padre;
}

Listener::~Listener() {
    // TODO Auto-generated destructor stub
}

void Listener::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    MobilityBase* mb = check_and_cast<MobilityBase*>(obj);
    if(padre->getParentModule()->getId()
            == mb->getParentModule()->getId()){
        this->speed = sqrt(mb->getCurrentSpeed().x * mb->getCurrentSpeed().x + mb->getCurrentSpeed().y * mb->getCurrentSpeed().y);
    }
}



double Listener::getSpeed()
{
    return speed;
}




