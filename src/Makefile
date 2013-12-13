#
# OMNeT++/OMNEST Makefile for libgod-dtn
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -I../../inet/src/linklayer/ieee80211/radio -I../../inet/src/linklayer/ethernet -I../../inet/src/networklayer/common -I../../inet/src/networklayer/icmpv6 -I../../inet/src -I../../inet/src/world/obstacles -I../../inet/src/networklayer/xmipv6 -I../../inet/src/mobility/models -I../../inet/src/networklayer/manetrouting/base -I../../inet/src/networklayer/contract -I../../inet/src/mobility -I../../inet/src/networklayer/autorouting/ipv4 -I../../inet/src/linklayer/ieee80211/mgmt -I../../inet/src/world/VACaMobil -I../../inet/src/util -I../../inet/src/transport/contract -I../../inet/src/linklayer/common -I../../inet/src/status -I../../inet/src/linklayer/radio/propagation -I../../inet/src/world/traci -I../../inet/src/linklayer/ieee80211/radio/errormodel -I../../inet/src/linklayer/radio -I../../inet/src/util/headerserializers/tcp -I../../inet/src/networklayer/ipv4 -I../../inet/src/util/headerserializers/ipv4 -I../../inet/src/base -I../../inet/src/util/headerserializers -I../../inet/src/world/radio -I../../inet/src/linklayer/ieee80211/mac -I../../inet/src/transport/sctp -I../../inet/src/networklayer/ipv6 -I../../inet/src/util/headerserializers/udp -I../../inet/src/networklayer/ipv6tunneling -I../../inet/src/battery/models -I../../inet/src/applications/pingapp -I../../inet/src/util/headerserializers/sctp -I../../inet/src/linklayer/contract -I../../inet/src/transport/tcp_common -I../../inet/src/networklayer/arp -I../../inet/src/transport/udp -L../../inet/out/$(CONFIGNAME)/src -linet -DWITH_TRACI -DINET_IMPORT -KINET_PROJ=../../inet
#

# Name of target to be created (-o option)
TARGET = libgod-dtn$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet/src/linklayer/ieee80211/radio \
    -I../../inet/src/linklayer/ethernet \
    -I../../inet/src/networklayer/common \
    -I../../inet/src/networklayer/icmpv6 \
    -I../../inet/src \
    -I../../inet/src/world/obstacles \
    -I../../inet/src/networklayer/xmipv6 \
    -I../../inet/src/mobility/models \
    -I../../inet/src/networklayer/manetrouting/base \
    -I../../inet/src/networklayer/contract \
    -I../../inet/src/mobility \
    -I../../inet/src/networklayer/autorouting/ipv4 \
    -I../../inet/src/linklayer/ieee80211/mgmt \
    -I../../inet/src/world/VACaMobil \
    -I../../inet/src/util \
    -I../../inet/src/transport/contract \
    -I../../inet/src/linklayer/common \
    -I../../inet/src/status \
    -I../../inet/src/linklayer/radio/propagation \
    -I../../inet/src/world/traci \
    -I../../inet/src/linklayer/ieee80211/radio/errormodel \
    -I../../inet/src/linklayer/radio \
    -I../../inet/src/util/headerserializers/tcp \
    -I../../inet/src/networklayer/ipv4 \
    -I../../inet/src/util/headerserializers/ipv4 \
    -I../../inet/src/base \
    -I../../inet/src/util/headerserializers \
    -I../../inet/src/world/radio \
    -I../../inet/src/linklayer/ieee80211/mac \
    -I../../inet/src/transport/sctp \
    -I../../inet/src/networklayer/ipv6 \
    -I../../inet/src/util/headerserializers/udp \
    -I../../inet/src/networklayer/ipv6tunneling \
    -I../../inet/src/battery/models \
    -I../../inet/src/applications/pingapp \
    -I../../inet/src/util/headerserializers/sctp \
    -I../../inet/src/linklayer/contract \
    -I../../inet/src/transport/tcp_common \
    -I../../inet/src/networklayer/arp \
    -I../../inet/src/transport/udp \
    -I. \
    -IPruebas \
    -IPruebas/beacons \
    -Iapplications \
    -Iapplications/beacons \
    -Iapplications/dtn \
    -Iapplications/dtn/GeOpps \
    -Iapplications/dtn/direct \
    -Iapplications/dtn/distance \
    -Iapplications/dtn/epidemic \
    -Iapplications/dtn/msdp \
    -Iapplications/dtn/random \
    -Iapplications/sumo \
    -Ietc \
    -Ietc/DataAnalisys \
    -Ietc/DataAnalisys/dtn \
    -Ietc/DataAnalisys/dtn/Scripts \
    -Ietc/DataAnalisys/dtn/Scripts/Ploting \
    -Ietc/DataAnalisys/dtn/Scripts/processing \
    -Ilinklayer \
    -Ilinklayer/Ideal \
    -InavigationSystem \
    -Inodes \
    -Itools \
    -Itools/osmParser \
    -Itools/osmParser/lib \
    -Iworld \
    -Iworld/sumoNav

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/applications/beacons/Neighbor.o \
    $O/applications/beacons/BeaconsApp.o \
    $O/applications/dtn/DTNMsgGenerator.o \
    $O/applications/dtn/DtnOneCopyProtocol.o \
    $O/applications/dtn/BackBoneApp.o \
    $O/applications/dtn/SinkApp.o \
    $O/applications/dtn/GeOpps/DTNGeOpps.o \
    $O/applications/dtn/GeOpps/GeOppsBeaconsApp.o \
    $O/applications/dtn/GeOpps/GeOppsNeighbor.o \
    $O/applications/dtn/direct/DirectBeaconsApp.o \
    $O/applications/dtn/distance/DistanceBeaconsApp.o \
    $O/applications/dtn/distance/DTNDistanceBased.o \
    $O/applications/dtn/distance/DistanceNeighbor.o \
    $O/applications/dtn/epidemic/EpiBeaconsApp.o \
    $O/applications/dtn/epidemic/EpidemicProtocol.o \
    $O/applications/dtn/epidemic/EpiNeighbor.o \
    $O/applications/dtn/msdp/MsdpNeighbor.o \
    $O/applications/dtn/msdp/DTNMsdp.o \
    $O/applications/dtn/msdp/MSDPBeaconsApp.o \
    $O/applications/dtn/random/RandomBeaconsApp.o \
    $O/applications/dtn/random/DTNRandom.o \
    $O/applications/dtn/random/RandomNeighbor.o \
    $O/applications/sumo/NavClient.o \
    $O/linklayer/Ideal/IdealMacRadio.o \
    $O/navigationSystem/NavigationSystem.o \
    $O/world/sumoNav/SumoNetwork.o \
    $O/applications/beacons/BeaconPkt_m.o \
    $O/applications/dtn/DTNDataMsg_m.o \
    $O/applications/dtn/GeOpps/GeOppsData_m.o \
    $O/applications/dtn/epidemic/Epidemic_m.o \
    $O/applications/dtn/msdp/MSDPDataMsg_m.o

# Message files
MSGFILES = \
    applications/beacons/BeaconPkt.msg \
    applications/dtn/DTNDataMsg.msg \
    applications/dtn/GeOpps/GeOppsData.msg \
    applications/dtn/epidemic/Epidemic.msg \
    applications/dtn/msdp/MSDPDataMsg.msg

# Other makefile variables (-K)
INET_PROJ=../../inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DWITH_TRACI -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
CFLAGS+= -std=c++0x

# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f god-dtn god-dtn.exe libgod-dtn.so libgod-dtn.a libgod-dtn.dll libgod-dtn.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f Pruebas/*_m.cc Pruebas/*_m.h
	$(Q)-rm -f Pruebas/beacons/*_m.cc Pruebas/beacons/*_m.h
	$(Q)-rm -f applications/*_m.cc applications/*_m.h
	$(Q)-rm -f applications/beacons/*_m.cc applications/beacons/*_m.h
	$(Q)-rm -f applications/dtn/*_m.cc applications/dtn/*_m.h
	$(Q)-rm -f applications/dtn/GeOpps/*_m.cc applications/dtn/GeOpps/*_m.h
	$(Q)-rm -f applications/dtn/direct/*_m.cc applications/dtn/direct/*_m.h
	$(Q)-rm -f applications/dtn/distance/*_m.cc applications/dtn/distance/*_m.h
	$(Q)-rm -f applications/dtn/epidemic/*_m.cc applications/dtn/epidemic/*_m.h
	$(Q)-rm -f applications/dtn/msdp/*_m.cc applications/dtn/msdp/*_m.h
	$(Q)-rm -f applications/dtn/random/*_m.cc applications/dtn/random/*_m.h
	$(Q)-rm -f applications/sumo/*_m.cc applications/sumo/*_m.h
	$(Q)-rm -f etc/*_m.cc etc/*_m.h
	$(Q)-rm -f etc/DataAnalisys/*_m.cc etc/DataAnalisys/*_m.h
	$(Q)-rm -f etc/DataAnalisys/dtn/*_m.cc etc/DataAnalisys/dtn/*_m.h
	$(Q)-rm -f etc/DataAnalisys/dtn/Scripts/*_m.cc etc/DataAnalisys/dtn/Scripts/*_m.h
	$(Q)-rm -f etc/DataAnalisys/dtn/Scripts/Ploting/*_m.cc etc/DataAnalisys/dtn/Scripts/Ploting/*_m.h
	$(Q)-rm -f etc/DataAnalisys/dtn/Scripts/processing/*_m.cc etc/DataAnalisys/dtn/Scripts/processing/*_m.h
	$(Q)-rm -f linklayer/*_m.cc linklayer/*_m.h
	$(Q)-rm -f linklayer/Ideal/*_m.cc linklayer/Ideal/*_m.h
	$(Q)-rm -f navigationSystem/*_m.cc navigationSystem/*_m.h
	$(Q)-rm -f nodes/*_m.cc nodes/*_m.h
	$(Q)-rm -f tools/*_m.cc tools/*_m.h
	$(Q)-rm -f tools/osmParser/*_m.cc tools/osmParser/*_m.h
	$(Q)-rm -f tools/osmParser/lib/*_m.cc tools/osmParser/lib/*_m.h
	$(Q)-rm -f world/*_m.cc world/*_m.h
	$(Q)-rm -f world/sumoNav/*_m.cc world/sumoNav/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Pruebas/*.cc Pruebas/beacons/*.cc applications/*.cc applications/beacons/*.cc applications/dtn/*.cc applications/dtn/GeOpps/*.cc applications/dtn/direct/*.cc applications/dtn/distance/*.cc applications/dtn/epidemic/*.cc applications/dtn/msdp/*.cc applications/dtn/random/*.cc applications/sumo/*.cc etc/*.cc etc/DataAnalisys/*.cc etc/DataAnalisys/dtn/*.cc etc/DataAnalisys/dtn/Scripts/*.cc etc/DataAnalisys/dtn/Scripts/Ploting/*.cc etc/DataAnalisys/dtn/Scripts/processing/*.cc linklayer/*.cc linklayer/Ideal/*.cc navigationSystem/*.cc nodes/*.cc tools/*.cc tools/osmParser/*.cc tools/osmParser/lib/*.cc world/*.cc world/sumoNav/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/applications/beacons/BeaconPkt_m.o: applications/beacons/BeaconPkt_m.cc \
	applications/beacons/BeaconPkt_m.h
$O/applications/beacons/BeaconsApp.o: applications/beacons/BeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNcommon.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/beacons/Neighbor.o: applications/beacons/Neighbor.cc \
	applications/beacons/Neighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/dtn/BackBoneApp.o: applications/dtn/BackBoneApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/BackBoneApp.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/epidemic/EpiNeighbor.h \
	applications/dtn/epidemic/EpidemicProtocol.h \
	applications/dtn/epidemic/Epidemic_m.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/DTNDataMsg_m.o: applications/dtn/DTNDataMsg_m.cc \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h
$O/applications/dtn/DTNMsgGenerator.o: applications/dtn/DTNMsgGenerator.cc \
	applications/dtn/DTNMsgGenerator.h \
	applications/dtn/IDTNProtocol.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/ModuleAccess.h
$O/applications/dtn/DtnOneCopyProtocol.o: applications/dtn/DtnOneCopyProtocol.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/IDTNProtocol.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/SinkApp.o: applications/dtn/SinkApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/BackBoneApp.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/SinkApp.h \
	applications/dtn/epidemic/EpiNeighbor.h \
	applications/dtn/epidemic/EpidemicProtocol.h \
	applications/dtn/epidemic/Epidemic_m.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/GeOpps/DTNGeOpps.o: applications/dtn/GeOpps/DTNGeOpps.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/GeOpps/DTNGeOpps.h \
	applications/dtn/GeOpps/GeOppsBeaconsApp.h \
	applications/dtn/GeOpps/GeOppsData_m.h \
	applications/dtn/GeOpps/GeOppsNeighbor.h \
	applications/dtn/IDTNProtocol.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/GeOpps/GeOppsBeaconsApp.o: applications/dtn/GeOpps/GeOppsBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/GeOpps/GeOppsBeaconsApp.h \
	applications/dtn/GeOpps/GeOppsData_m.h \
	applications/dtn/GeOpps/GeOppsNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/GeOpps/GeOppsData_m.o: applications/dtn/GeOpps/GeOppsData_m.cc \
	applications/dtn/GeOpps/GeOppsData_m.h
$O/applications/dtn/GeOpps/GeOppsNeighbor.o: applications/dtn/GeOpps/GeOppsNeighbor.cc \
	applications/beacons/Neighbor.h \
	applications/dtn/GeOpps/GeOppsNeighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/dtn/direct/DirectBeaconsApp.o: applications/dtn/direct/DirectBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/direct/DirectBeaconsApp.h \
	applications/dtn/random/RandomBeaconsApp.h \
	applications/dtn/random/RandomNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/distance/DTNDistanceBased.o: applications/dtn/distance/DTNDistanceBased.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/distance/DTNDistanceBased.h \
	applications/dtn/distance/DistanceBeaconsApp.h \
	applications/dtn/distance/DistanceNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/distance/DistanceBeaconsApp.o: applications/dtn/distance/DistanceBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/distance/DistanceBeaconsApp.h \
	applications/dtn/distance/DistanceNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/distance/DistanceNeighbor.o: applications/dtn/distance/DistanceNeighbor.cc \
	applications/beacons/Neighbor.h \
	applications/dtn/distance/DistanceNeighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/dtn/epidemic/EpiBeaconsApp.o: applications/dtn/epidemic/EpiBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/epidemic/EpiBeaconsApp.h \
	applications/dtn/epidemic/EpiNeighbor.h \
	applications/dtn/epidemic/EpidemicProtocol.h \
	applications/dtn/epidemic/Epidemic_m.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/epidemic/EpiNeighbor.o: applications/dtn/epidemic/EpiNeighbor.cc \
	applications/beacons/Neighbor.h \
	applications/dtn/epidemic/EpiNeighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/dtn/epidemic/EpidemicProtocol.o: applications/dtn/epidemic/EpidemicProtocol.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/BackBoneApp.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/epidemic/EpiNeighbor.h \
	applications/dtn/epidemic/EpidemicProtocol.h \
	applications/dtn/epidemic/Epidemic_m.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/epidemic/Epidemic_m.o: applications/dtn/epidemic/Epidemic_m.cc \
	applications/dtn/DTNcommon.h \
	applications/dtn/epidemic/Epidemic_m.h
$O/applications/dtn/msdp/DTNMsdp.o: applications/dtn/msdp/DTNMsdp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/msdp/DTNMsdp.h \
	applications/dtn/msdp/MSDPBeaconsApp.h \
	applications/dtn/msdp/MsdpNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/msdp/MSDPBeaconsApp.o: applications/dtn/msdp/MSDPBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/msdp/MSDPBeaconsApp.h \
	applications/dtn/msdp/MSDPDataMsg_m.h \
	applications/dtn/msdp/MsdpNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/msdp/MSDPDataMsg_m.o: applications/dtn/msdp/MSDPDataMsg_m.cc \
	applications/dtn/msdp/MSDPDataMsg_m.h
$O/applications/dtn/msdp/MsdpNeighbor.o: applications/dtn/msdp/MsdpNeighbor.cc \
	applications/beacons/Neighbor.h \
	applications/dtn/msdp/MsdpNeighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/dtn/random/DTNRandom.o: applications/dtn/random/DTNRandom.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNDataMsg_m.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/DtnOneCopyProtocol.h \
	applications/dtn/IDTNProtocol.h \
	applications/dtn/random/DTNRandom.h \
	applications/dtn/random/RandomBeaconsApp.h \
	applications/dtn/random/RandomNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/random/RandomBeaconsApp.o: applications/dtn/random/RandomBeaconsApp.cc \
	applications/beacons/BeaconPkt_m.h \
	applications/beacons/BeaconsApp.h \
	applications/beacons/Neighbor.h \
	applications/dtn/DTNcommon.h \
	applications/dtn/random/RandomBeaconsApp.h \
	applications/dtn/random/RandomNeighbor.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/applications/dtn/random/RandomNeighbor.o: applications/dtn/random/RandomNeighbor.cc \
	applications/beacons/Neighbor.h \
	applications/dtn/random/RandomNeighbor.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/applications/sumo/NavClient.o: applications/sumo/NavClient.cc \
	applications/sumo/NavClient.h \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/linklayer/Ideal/IdealMacRadio.o: linklayer/Ideal/IdealMacRadio.cc \
	linklayer/Ideal/IdealMacRadio.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Consts.h \
	$(INET_PROJ)/src/linklayer/ieee80211/mac/Ieee80211Frame_m.h \
	$(INET_PROJ)/src/linklayer/radio/AirFrame_m.h \
	$(INET_PROJ)/src/linklayer/radio/ModulationType.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/annotations/AnnotationManager.h \
	$(INET_PROJ)/src/world/obstacles/Obstacle.h \
	$(INET_PROJ)/src/world/obstacles/ObstacleControl.h \
	$(INET_PROJ)/src/world/radio/ChannelAccess.h \
	$(INET_PROJ)/src/world/radio/ChannelControl.h \
	$(INET_PROJ)/src/world/radio/IChannelControl.h
$O/navigationSystem/NavigationSystem.o: navigationSystem/NavigationSystem.cc \
	navigationSystem/NavigationSystem.h \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/TraCIMobility.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/VACaMobil/RSUManager.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h
$O/world/sumoNav/SumoNetwork.o: world/sumoNav/SumoNetwork.cc \
	world/sumoNav/SumoNetwork.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/util/FWMath.h \
	$(INET_PROJ)/src/world/traci/TraCIScenarioManager.h

