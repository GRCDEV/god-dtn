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

package inet.GRC.applications.dtn;
import inet.applications.IUDPApp;

simple SinkApp like IUDPApp{
    parameters:
        string wirelessIf = default("wlan");
        string backboneIf = default("eth0");
        string backboneModule = default("DTNBackBone");
        bool useAck=default(true);
        bool useBroadcast=default(false);
        @signal[dtnDataRx](type="cPacket");
        @statistic[DirectDataRx](title="Reception";source="packetBytes(dtnDataRx)"; record=count, sum, vector);
        @signal[dtnAckTx](type="cPacket");
        @statistic[DirectAckTx](title="AckTransmission";source="packetBytes(dtnAckTx)"; record=count, sum, vector);
    gates:
   	    output 	udpOut;
   	    input	udpIn;
}