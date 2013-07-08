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

cplusplus {{
    #include "DTNcommon.h"
}}

struct DTNFragment;

//
//This msg file defines a basic data message for DTN, if a protocol 
//needs to attach information to this packets it must be encapsulated
//

packet DTNDataMsg{
 	uint64 srcId;
 	uint64 dstId;
 	uint32 msgId;
 	DTNFragment fragments[];
}

packet DTNDataAck{
    uint64 srcId;
 	uint64 dstId;
 	uint32 msgId;
}
