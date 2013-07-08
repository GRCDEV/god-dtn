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

//
// TODO generated message class
//

cplusplus {{
    #include "DTNcommon.h"
}}

struct DTNFragment;
struct DTNUnique;
//0 and 1 are used by DTNCommon values
enum EpidemicType{
    PKT_OFFER = 2;
    PKT_REQUEST = 3;
}

packet EpidemicPkt{
    uint64 srcId;
    uint64 dstId;
    uint8 type;
}

packet EpidemicPktOffer extends EpidemicPkt {
    type = PKT_OFFER;
    DTNUnique offer[];
}

packet EpidemicPktAsk extends EpidemicPkt{
    type = PKT_REQUEST;
    DTNUnique ask[];
}

packet EpiInfo{
    simtime_t lastBufferUpdate;
}