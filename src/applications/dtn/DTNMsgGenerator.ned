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


simple DTNMsgGenerator
{
    parameters:
        int numberOfMessages = default(-1); //-1 infinites packets, 0 no packets
        double phaseTime @unit(seconds) = default(uniform(0s,10s));
        volatile double msgSize @unit(Byte) = default(2KiB);
        volatile double interMsgTime @unit(seconds) = default(0s);
        @signal[msgGenerated](type="double");
        @statistic[MsgGenerated](title="Generated Messages";source="msgGenerated"; record=count, sum, vector);
}
