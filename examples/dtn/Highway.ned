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

package dtn;


import inet.world.radio.ChannelControl;
import inet.world.obstacles.ObstacleControl;
import inet.world.annotations.AnnotationManager;
import inet.nodes.ethernet.Eth100G;
import inet.nodes.ethernet.EtherSwitch;
import inet.world.VACaMobil.VACaMobil;
import inet.GRC.world.sumoNav.SumoNetwork;
import inet.GRC.applications.dtn.BackBoneApp;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

network Highway
{
    submodules:
        channelControl: ChannelControl {
            @display("p=140,216;is=s");
        }
        manager: VACaMobil {
            @display("p=140,173");
        }
        sumoNetwork: SumoNetwork {
            @display("p=73,204;is=s");
        }
        DTNBackBone: BackBoneApp {
            @display("p=73,112");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=73,161");
        }
        obstacles: ObstacleControl {
            @display("p=140,112");
        }
        annotations: AnnotationManager {
            @display("p=61,280");
        }
    connections allowunconnected:
}
