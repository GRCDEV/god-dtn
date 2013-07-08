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


#ifndef NEIGHBORH_H_
#define NEIGHBORH_H_

#include "Coord.h"
#include "IPvXAddress.h"
class Neighbor {
public:
    Neighbor();
    virtual ~Neighbor();
    double getAngle() const;
    uint64 getId() const;
    uint32 getLastMsgId() const;
    simtime_t getLastUpdate() const;
    Coord getLocation() const;
    double getSpeed() const;
    void setAngle(double angle);
    void setId(uint64_t id);
    void setLastMsgId(uint32_t lastMsgId);
    void setLastUpdate(simtime_t lastUpdate);
    void setLocation(Coord location);
    void setSpeed(double speed);
    bool operator==(const Neighbor & rhs) const;
    bool operator <(const Neighbor & rhs) const;
    IPvXAddress getIpAddr() const;
    void setIpAddr(IPvXAddress ipAddr);
    int getNodeType() const;
    void setNodeType(int nodeType);
private:
    uint64 id;
    int nodeType;
    uint32 lastMsgId;
    Coord location;
    IPvXAddress ipAddr;
    double speed;
    double angle;
    simtime_t lastUpdate;
};

#endif /* NEIGHBORH_H_ */
