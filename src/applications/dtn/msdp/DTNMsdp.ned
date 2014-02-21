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

package inet.GRC.applications.dtn.msdp;
import inet.GRC.applications.dtn.DtnOneCopyProtocol;

simple DTNMsdp like DtnOneCopyProtocol
{
     parameters:
        @display("i=block/app");
        double ackTimeOut @unit(seconds) = default(5s);
        string wirelessIf = default("wlan");
        int windowSize = default(30);
        double redundancy = default(0);
        int bitrate @unit(bps)= default(27Mbps);
        int maxHops = default(0);
        int fragmentSize @unit(bytes)= default(200B);
        double maxRange @unit(meters) = default(300m);
        double transmissionPenalty = default(1);//Penalty applied to neighbours when evaluating their DTN index. By default no penalty is applied
        bool oneFragPerMsg=default(false);
        bool useAck =default (true);
        bool useBroadcast =default(false); 
       @signal[dtnFragmentGenerated](type="double");
        @statistic[FragmentGenerated](title="Generated Fragments";source="dtnFragmentGenerated"; record=count, sum, vector);
        @signal[dtnDataTx](type="cPacket");
        @statistic[DataTx](title="Transmission";source="packetBytes(dtnDataTx)"; record=count, sum, vector);
        @signal[directDataTx](type="cPacket");
        @statistic[DirectDataTx](title="Direct Transmission";source="packetBytes(directDataTx)"; record=count, sum, vector);
        @signal[dtnDataRx](type="cPacket");
        @statistic[DataRx](title="Reception";source="packetBytes(dtnDataRx)"; record=count, sum, vector);
        @signal[dtnAckTx](type="cPacket");
        @statistic[AckTx](title="AckTransmission";source="packetBytes(dtnAckTx)"; record=count, sum, vector);
        @signal[dtnAckRx](type="cPacket");
        @statistic[AckRx](title="AckReception";source="packetBytes(dtnAckRx)"; record=count, sum, vector);
        @signal[dtnAckTO](type="cPacket");
        @statistic[AckTO](title="AckTimeOut";source="dtnAckTO"; record=count, sum);
        @signal[oppExpired](type="double");
        @statistic[OppExpired](title="OppExpired";source="oppExpired"; record=count, vector, mean);
        @signal[dropMsg](type="int");
        @statistic[DropFragments](title="DropMessages";source="dropMsg"; record=sum);        
     gates:
        input udpIn @labels(UDPControlInfo/up);
        output udpOut @labels(UDPControlInfo/down);
}
