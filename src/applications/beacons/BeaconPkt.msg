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

enum NodeType{
    Car = 0; 
    Sink = 1;
}

packet BeaconPkt {
    uint32 msgId;
    uint64 srcId;
    uint32 serviceIp;
    int 	nodeType  @enum(NodeType);
    double lat;
    double lon;
    double speed;
    double bearing;
}