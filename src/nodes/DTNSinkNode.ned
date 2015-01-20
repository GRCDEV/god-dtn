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
package inet.GRC.nodes;
import inet.GRC.applications.beacons.BeaconsApp;
import inet.GRC.applications.dtn.SinkApp;
import inet.base.NotificationBoard;
import inet.mobility.static.StationaryMobility;
import inet.networklayer.autorouting.ipv4.HostAutoConfigurator;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.transport.udp.UDP;
import inet.nodes.inet.NetworkLayer;
import inet.linklayer.ieee80211.Ieee80211Nic;

module DTNSinkNode
{
    parameters:
        @node();

        @display("i=device/antennatower,purple;is=vs");
    gates:
        input radioIn[2] @directIn;
        inout ethInOut @labels(EtherFrame-conn);
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=140,462");
        }
        ac_wlan: HostAutoConfigurator {
            parameters:
                @display("p=60,408");
                interfaces = "wlan0 wlan1";
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=140,326");
        }
        sinkApp: SinkApp {
            parameters:
                @display("p=384,46");
                wirelessIf = "wlan1";
        }
        beaconsApp: BeaconsApp {
            parameters:
                @display("p=513,46");
                nodeType = "SINK";
                interface = "wlan0";
                serviceInterface = "wlan1";
        }
        mobility: StationaryMobility {
            parameters:
                initFromDisplayString = false;
                @display("p=60,459");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = false;
                routerId = "";
                routingFile = "";
                @display("p=60,326");
        }
        udp: UDP {
            parameters:
                @display("p=384,146");
        }
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=353,326;q=queue");
            gates:
                ifIn[2];
                ifOut[2];
        }
        wlan0: Ieee80211Nic {
            parameters:
                @display("p=304,461;q=queue");
                mgmtType = "Ieee80211MgmtAdhoc";
                opMode = "p";
        }
        wlan1: Ieee80211Nic {
            parameters:
                @display("p=384,459;q=queue");
                mgmtType = "Ieee80211MgmtAdhoc";
                opMode = "p";
        }
    connections allowunconnected:
        udp.appOut++ --> sinkApp.udpIn;
        udp.appIn++ <-- sinkApp.udpOut;

        udp.appOut++ --> beaconsApp.udpIn;
        udp.appIn++ <-- beaconsApp.udpOut;

        udp.ipOut --> networkLayer.transportIn++;
        udp.ipIn <-- networkLayer.transportOut++;

        wlan0.upperLayerOut --> networkLayer.ifIn[0];
        wlan0.upperLayerIn <-- networkLayer.ifOut[0];
        radioIn[0] --> wlan0.radioIn;

        wlan1.upperLayerOut --> networkLayer.ifIn[1];
        wlan1.upperLayerIn <-- networkLayer.ifOut[1];
        radioIn[1] --> wlan1.radioIn;
}

