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

package inet.GRC.linklayer.Ideal;
import inet.linklayer.IWirelessNic;


//
// TODO auto-generated module
//
simple IdealMacRadio like IWirelessNic
{
    parameters:
        string address = default("auto");
        double bitrate @unit("bps") = default(27e6bps);
        double basicBitrate @unit("bps") = default(6e6bps);
        double maxDistance @unit("m") = default(250m);
        int channelNumber = default(0);
        bool multiMac = default(false);
    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        input radioIn @labels(AirFrame); // to receive AirFrames
}
