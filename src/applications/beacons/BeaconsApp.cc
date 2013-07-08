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

#include "BeaconsApp.h"
#include "BeaconPkt_m.h"
#include "IPvXAddressResolver.h"
#include  <vector>

Define_Module(BeaconsApp);

void BeaconsApp::initialize(int stage) {

    if (stage == 3) {
        std::string typeStr = par("nodeType").stdstringValue();

        if(typeStr == "CAR"){
            type = Car;
            nav = ModuleAccess<NavigationSystem>("navigationSystem").get();
        }
        else{
            type = Sink;
            mobility = ModuleAccess<MobilityBase>("mobility").get();
        }
        localPort = destPort = BEACON_PORT;
        //Obtain the broadcast interface
        IInterfaceTable *ift = InterfaceTableAccess().get();
        InterfaceEntry *ie = ift->getInterfaceByName(par("interface").stringValue());
        if (ie == NULL) {
            throw cRuntimeError(this, "Invalid output interface name" );
        }

        //Obtain the service interface where apps must listen
        InterfaceEntry *serviceIe = ift->getInterfaceByName(par("serviceInterface").stringValue());
        if (ie == NULL) {
            throw cRuntimeError(this, "Invalid output interface name" );
        }

        outputInterface = ie->getInterfaceId();
        myAddr = ie->ipv4Data()->getIPAddress();
        myServiceAddr = serviceIe->ipv4Data()->getIPAddress();
        myId = getId();

        beaconID = intrand(100);

        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);
        socket.setBroadcast(true);
        cMessage *msg = new cMessage("NEXT_BEACON");
        msg->setKind(NEW_BEACON);
        interBeaconTime = par("beaconTime").doubleValue();
        scheduleAt(simTime()+par("phaseTime")+interBeaconTime, msg);
    }
}

void BeaconsApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()){
        if(msg->getKind() == NEW_BEACON) {
            sendNewBeacon();
            double jitter = par("jitterTime").doubleValue();
            scheduleAt(simTime()+interBeaconTime+jitter, msg);
        }else if(msg->getKind()==REMOVE_NEIGH){
            uint64 *id= (uint64*)msg->getContextPointer();
            std::map<uint64, Neighbor *>::iterator i = neighborsList.find(*id);
            ASSERT(i!=neighborsList.end());
            Neighbor *neigh = (i->second);
            informRemoveNeighborSubscribers(neigh);
            neighborsList.erase(*id);
            msgMap.erase(*id);
            delete msg;
            delete neigh;
        }
    } else {
        if (dynamic_cast<BeaconPkt *>(msg) != NULL) {
            BeaconPkt *beacon = check_and_cast<BeaconPkt *>(msg);
            if(beacon->getSrcId() != myId ){
                processBeacon(beacon);
            }
            else{
                delete beacon;
            }
        }
    }
}

void BeaconsApp::sendNewBeacon(){
    BeaconPkt *beacon = new BeaconPkt();
    Coord myLoc;
    double speed, angle;
    if(type == Car){
        myLoc = nav->getCurrentPosition();
        speed = nav->getSpeedMod();
        angle = nav->getSpeedAngle();
    }else {
        /*
         * Obtain parameters directly from MobilityModule
         */
        myLoc = mobility->getCurrentPosition();
        speed = 0;
        angle = 0;
    }
    beacon->setSrcId(myId);
    beacon->setMsgId(beaconID++);
    beacon->setNodeType(type);
    beacon->setLat(myLoc.x);
    beacon->setLon(myLoc.y);
    beacon->setSpeed(speed);
    beacon->setBearing(angle);
    beacon->setTimestamp(simTime());
    beacon->setServiceIp(myServiceAddr.getInt());
    beacon->setByteLength(sizeof(myId)+sizeof(uint32)+sizeof(type)+sizeof(myLoc.x)*2+sizeof(double)*2+sizeof(uint64));
    addExtraInfo(beacon);
    socket.sendTo(beacon, IPv4Address::ALLONES_ADDRESS, destPort, outputInterface);
}
void BeaconsApp::processBeacon(BeaconPkt *beacon){
    bool newNeighbor=false;
    uint64 *id=new uint64(beacon->getSrcId());
    Neighbor *neighbor = createNeighbor();
    cMessage *msg;
    if(isNew(*id)){
        newNeighbor=true;
        msg = new cMessage("REMOVE_NEIGHBOR");
        msg->setKind(REMOVE_NEIGH);
        msg->setContextPointer(id);
        msgMap.insert(std::pair<uint64, cMessage*>({*id, msg}));
    }

    neighbor->setId(*id);
    neighbor->setLastMsgId(beacon->getMsgId());
    neighbor->setLastUpdate(beacon->getTimestamp());
    neighbor->setLocation(Coord(beacon->getLat(), beacon->getLon()));
    neighbor->setSpeed(beacon->getSpeed());
    neighbor->setAngle(beacon->getBearing());
    neighbor->setNodeType(beacon->getNodeType());
    // determine its source address
    IPvXAddress srcAddr = IPv4Address(beacon->getServiceIp());
    neighbor->setIpAddr(srcAddr);
    readExtraInfo(beacon, neighbor, newNeighbor);
    msg=msgMap.at(*id);
    cancelEvent(msg);
    scheduleAt(simTime()+par("neighTimeOut"), msg);


    if(newNeighbor){
        informNewNeighborSubscribers(neighbor);
    } else{
        informOnChagedNeighborSubscribers(neighbor);
    }

    if(neighborsList.find(*id) != neighborsList.end()){
        delete neighborsList.at(*id);
        neighborsList.erase(*id);
    }

    neighborsList.insert(std::pair<uint64, Neighbor*>({(*id),neighbor}));
    delete beacon;
}

bool BeaconsApp::isNew(uint64 id){
    if(neighborsList.find(id) == neighborsList.end()){
        return true;
    }
    else{
        return false;
    }
}

void BeaconsApp::subscribeNews(BeaconSubscriber *subscriber)
{
    Enter_Method_Silent();
    subscriberList.push_back(subscriber);
}

void BeaconsApp::unSubscribeNews(BeaconSubscriber *subscriber)
{
    subscriberList.remove(subscriber);
}

void BeaconsApp::sendBeaconNow()
{
    sendNewBeacon();
}

enum NodeType BeaconsApp::getType() const
{
    return type;
}

uint64 BeaconsApp::getMyId() const
{
    Enter_Method_Silent();
    return myId;
}

void BeaconsApp::informNewNeighborSubscribers(Neighbor *neighbor)
{
    for(std::list<BeaconSubscriber*>::iterator i = subscriberList.begin(); i != subscriberList.end(); i++){
        (*i)->onNewNeighbor(neighbor);
    }
}

bool BeaconsApp::hasChanged(Neighbor *neighbor)
{
    return true;
}

Neighbor *BeaconsApp::createNeighbor()
{
    return new Neighbor();
}

BeaconsApp::~BeaconsApp()
{
    for(std::map<uint64, Neighbor *>::iterator i=neighborsList.begin(); i != neighborsList.end(); i++){
        delete i->second;
    }
    neighborsList.clear();

    for(std::map<uint64, cMessage *>::iterator i=msgMap.begin(); i!= msgMap.end(); i++){
        cancelAndDelete(i->second);
    }

    msgMap.clear();
}

void BeaconsApp::informRemoveNeighborSubscribers(Neighbor *neighbor)
{
    for(std::list<BeaconSubscriber*>::iterator i = subscriberList.begin(); i != subscriberList.end(); i++){
        (*i)->onRemoveNeighbor(neighbor);
    }
}

Coord BeaconsApp::getMyLoc() const
{
    Coord myLoc;
    if(type == Car){
        myLoc = nav->getCurrentPosition();
    }
    else{
        myLoc = mobility->getCurrentPosition();
    }
    return myLoc;
}

Neighbor *BeaconsApp::getNeighborInfo(uint64 id)
{
    return neighborsList.at(id);
}

void BeaconsApp::informOnChagedNeighborSubscribers(Neighbor *neighbor)
{
    for(std::list<BeaconSubscriber*>::iterator i = subscriberList.begin(); i != subscriberList.end(); i++){
            (*i)->onNeighborChanged(neighbor);
        }
}






