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

moduleinterface DtnOneCopyProtocol extends IUDPApp
{
    parameters:
        @display("i=block/app");
        string wirelessIf;
        double ackTimeOut @unit(seconds);
        double redundancy;
        int windowSize;
        int bitrate @unit(bits);
        int maxHops;
        int fragmentSize @unit(bytes);
        double maxRange @unit(meters);
        bool oneFragPerMsg;
        bool useAck;
        bool useBroadcast;
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
}
