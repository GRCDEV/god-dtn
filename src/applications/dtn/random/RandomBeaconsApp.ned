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

package inet.GRC.applications.dtn.random;

import inet.applications.IUDPApp;


simple RandomBeaconsApp like IUDPApp{
    parameters:
    	string nodeType @enum("CAR","SINK") = default("CAR");
    	bool debug = default(false);
        double neighTimeOut @unit(s) = default( 5s );
    	double beaconTime @unit(s) = default( 1s );
    	volatile double phaseTime @unit(s) = default(uniform(-beaconTime,beaconTime));
    	volatile double jitterTime @unit(s) = default(uniform(-5ms,5ms));
    	string interface = default("wlan");
    	string serviceInterface = default("wlan");
   	gates:
   	    output 	udpOut;
   	    input	udpIn;
}

