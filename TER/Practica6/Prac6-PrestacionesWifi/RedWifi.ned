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

import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.ethernet.Eth1G;
import inet.nodes.inet.StandardHost;
import inet.nodes.inet.WirelessHost;
import inet.nodes.wireless.AccessPoint;
import inet.world.radio.ChannelControl;


network RedWifi
{
    parameters:
        @display("bgb=628,553");
        int nClients = default(1);

    submodules:
        iPv4NetworkConfigurator: IPv4NetworkConfigurator {
            @display("p=116,60");
            assignDisjunctSubnetAddresses = false;
            addStaticRoutes = false;
            config = xml("<config> \
        <interface hosts='**' address='10.0.1.x' netmask='255.255.255.0'/> \
        <route hosts='wirelessHost*' destination='10.0.1.0' netmask='255.255.255.0' interface='wlan0' /> \
        <route hosts='server*' destination='10.0.1.0' netmask='255.255.255.0' interface='eth0' /> \
        </config>");
        }
        channelControl: ChannelControl {
            @display("p=121,173");
            propagationModel = "NakagamiModel";
        }
        wirelessHost[nClients]: WirelessHost {
            @display("p=121,315");
            mobility.initFromDisplayString = false;
        }
        accessPoint: AccessPoint {
            @display("p=345,314");
            mobilityType = "StationaryMobility";
            mobility.initFromDisplayString = false;
            mobility.initialZ = 1m;
        }
        server: StandardHost {
            @display("p=345,52");
            mobility.initFromDisplayString = false;
            mobility.initialZ = 1m;
        }
    connections:
        server.ethg++ <--> Eth1G <--> accessPoint.ethg++;
}
