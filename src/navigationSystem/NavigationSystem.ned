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

package inet.GRC.navigationSystem;

//This module load the sumo network to provide SumoNav information not available throug TraCI
//Must be named navigationSystem inside the node.

simple NavigationSystem
{
    parameters:
        @display("i=block/app2;is=l");
        string networkModule = "sumoNetwork"; //name of the SumoNetwork module
        double gpsError = uniform(0, 5);
        int avgSpeedWindow = default(10); //number of measurements used to calculate the window averaged speed
        xml poaConfig = default(xml("<poas></poas>"));//Poas' parameters list, by default is empty
        double defaultRange @unit(meters) = default(200m);
        double defaultRate @unit(bps) = default(27Mbps);
        bool debug = default(false);  // emit debug messages? 
}

