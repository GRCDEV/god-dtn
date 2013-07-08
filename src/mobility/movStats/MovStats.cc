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

#include "MovStats.h"

Define_Module(MovStats);

MovStats::MovStats()
{
    l = new Listener(this);
    speed = registerSignal("speedSignal");
    simulation.getSystemModule()->subscribe("mobilityStateChanged", l);
}

void MovStats::initialize(){
    scheduleAt(simTime() + 1, new cMessage("Probe"));
}

void MovStats::handleMessage(cMessage *msg)
{
    delete msg;
    emit(speed, l->getSpeed());
    scheduleAt(simTime() + 1, new cMessage("Probe"));
}

void MovStats::finish()
{
    simulation.getSystemModule()->unsubscribe("mobilityStateChanged", l);
}


