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

#include "Neighbor.h"

Neighbor::Neighbor()
{
    id = 0;
    lastMsgId = 0;
    lastUpdate = 0;
    angle = 0;
    location.x = location.y = 0;
    speed = 0;
}

Neighbor::~Neighbor()
{

}

double Neighbor::getAngle() const
{
    return angle;
}

uint64 Neighbor::getId() const
{
    return id;
}

uint32 Neighbor::getLastMsgId() const
{
    return lastMsgId;
}

simtime_t Neighbor::getLastUpdate() const
{
    return lastUpdate;
}

Coord Neighbor::getLocation() const
{
    return location;
}

double Neighbor::getSpeed() const
{
    return speed;
}

void Neighbor::setAngle(double angle)
{
    this->angle = angle;
}

void Neighbor::setId(uint64_t id)
{
    this->id = id;
}

void Neighbor::setLastMsgId(uint32_t lastMsgId)
{
    this->lastMsgId = lastMsgId;
}

void Neighbor::setLastUpdate(simtime_t lastUpdate)
{
    this->lastUpdate = lastUpdate;
}

void Neighbor::setLocation(Coord location)
{
    this->location = location;
}

void Neighbor::setSpeed(double speed)
{
    this->speed = speed;
}

bool Neighbor::operator ==(const Neighbor & rhs) const
{
    return this->id == rhs.id;
}



bool Neighbor::operator <(const Neighbor & rhs) const
{
    return this->id < rhs.id;
}

IPvXAddress Neighbor::getIpAddr() const
{
    return ipAddr;
}

void Neighbor::setIpAddr(IPvXAddress ipAddr)
{
    this->ipAddr = ipAddr;
}

int Neighbor::getNodeType() const
{
    return nodeType;
}

void Neighbor::setNodeType(int nodeType)
{
    this->nodeType = nodeType;
}













