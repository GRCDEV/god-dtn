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

//
//	This app must run inside a backbone dtn node. Such nodes will consume and reasemble packets
//  from DTNSinkNodes. 
//
simple BackBoneApp 
{
    parameters:
        @signal[msgReceived](type="double");
        @signal[fragmentReceived](type="double");
        @statistic[MsgReceived](title="Received Messages";source="msgReceived"; record=count, sum, vector);
        @statistic[FragmentReceived](title="Received Fragments";source="fragmentReceived"; record=count, sum, vector);
        @signal[msgReceivedDelay](type="double");
        @signal[fragmentReceivedDelay](type="double");
        @statistic[MsgReceivedDelay](title="Received Messages Delay";source="msgReceivedDelay"; record= vector, histogram);
        @statistic[FragmentReceivedDelay](title="Received Fragments Delay";source="fragmentReceivedDelay"; record= vector, histogram);
    gates:
        input dataIn;
}