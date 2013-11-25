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

package inet.GRC.applications.beacons;
import inet.applications.IUDPApp;


simple BeaconsApp like IUDPApp{
    parameters:
    	string nodeType @enum("CAR","SINK") = default("CAR");
    	bool debug = default(false);
    	double beaconTime @unit(s) = default( 1s );
    	double neighTimeOut @unit(s) = default( 5s );
    	volatile double phaseTime @unit(s) = default(uniform(-beaconTime,beaconTime));
    	volatile double jitterTime @unit(s) = default(uniform(-5ms,5ms));
    	string interface = default("wlan");
    	string serviceInterface = default("wlan");
    	@signal[newNeighbor](type="integer");
        @statistic[NewNeighbor](title="New Neighbor Detected";source="newNeighbor"; record=count, vector);
        @signal[rmNeighbor](type="integer");
        @statistic[RmNeighbor](title="Neighbor Removed";source="rmNeighbor"; record=count, vector);
   	gates:
   	    output 	udpOut;
   	    input	udpIn;
}