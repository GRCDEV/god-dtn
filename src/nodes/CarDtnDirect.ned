//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package inet.GRC.nodes;

import inet.base.NotificationBoard;
import inet.networklayer.autorouting.ipv4.HostAutoConfigurator;
import inet.networklayer.common.InterfaceTable;
import inet.mobility.models.TraCIMobility;
import inet.networklayer.ipv4.RoutingTable;
import inet.transport.udp.UDP;
import inet.nodes.inet.NetworkLayer;
import inet.linklayer.ieee80211.Ieee80211Nic;
import inet.GRC.navigationSystem.NavigationSystem;
import inet.GRC.applications.dtn.random.DTNRandom;
import inet.GRC.applications.dtn.direct.DirectBeaconsApp;
import inet.GRC.applications.dtn.DTNMsgGenerator;

module CarDtnDirect
{
    parameters:
        @node();

    gates:
        input radioIn[2] @directIn;

    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=140,462");
        }
        ac_wlan: HostAutoConfigurator {
            parameters:
                @display("p=415,462");
                interfaces = "wlan0 wlan1";
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=140,326");
        }
        mobility: TraCIMobility {
            parameters:
                @display("p=60,459");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = "";
                routingFile = "";
                @display("p=60,326");
        }
        udp: UDP {
            parameters:
                @display("p=343,188");
        }
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=304,327;q=queue");
            gates:
                ifIn[2];
                ifOut[2];
        }
        wlan0: Ieee80211Nic {
            parameters:
                opMode = "p";
                mgmtType = "Ieee80211MgmtAdhoc";
                @display("p=258,462;q=queue");
        }
        wlan1: Ieee80211Nic {
            parameters:
                opMode = "p";
                mgmtType = "Ieee80211MgmtAdhoc";
                @display("p=349,462;q=queue");
        }
        navigationSystem: NavigationSystem {
            @display("p=50,47");
        }
        dtnProtocol: DTNRandom {
            parameters:
                @display("p=415,117");
                wirelessIf = "wlan1";
        }
        beaconsApp: DirectBeaconsApp {
            parameters:
                @display("p=343,117");
                interface = "wlan0";
                serviceInterface = "wlan1";
        }
        msgGenerator: DTNMsgGenerator {
            @display("p=415,57");
        }
    connections allowunconnected:
        udp.appOut++ --> beaconsApp.udpIn;
        udp.appIn++ <-- beaconsApp.udpOut;

        udp.appOut++ --> dtnProtocol.udpIn;
        udp.appIn++ <-- dtnProtocol.udpOut;

        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        wlan0.upperLayerOut --> networkLayer.ifIn[0];
        wlan0.upperLayerIn <-- networkLayer.ifOut[0];

        wlan1.upperLayerOut --> networkLayer.ifIn[1];
        wlan1.upperLayerIn <-- networkLayer.ifOut[1];

        radioIn[0] --> wlan0.radioIn;
        radioIn[1] --> wlan1.radioIn;
}