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

#include "IdealMacRadio.h"
#include <IInterfaceTable.h>
#include <InterfaceTableAccess.h>
Define_Module(IdealMacRadio);

void IdealMacRadio::initialize(int stage)
{
    ChannelAccess::initialize(stage);

    if(stage == 0)
    {
        cc = getChannelControl();
        gate("radioIn")->setDeliverOnReceptionStart(false);

        upperLayerIn = findGate("upperLayerIn");
        upperLayerOut = findGate("upperLayerOut");

        bitrate= par("bitrate");
        basicBitrate = par("basicBitrate");
        channelNumber = par("channelNumber");
        commDistance = par("maxDistance");
        sqrCommDistance = pow(commDistance, 2);
        obstacles = ObstacleControlAccess().getIfExists();
        if (obstacles) EV << "Found ObstacleControl" << endl;

        const char *addressString = par("address");
        address = isInterfaceRegistered();
        if (address.isUnspecified())
        {
            if (!strcmp(addressString, "auto"))
            {
                // assign automatic address
                address = MACAddress::generateAutoAddress();
                // change module parameter from "auto" to concrete address
                par("address").setStringValue(address.str().c_str());
            }
            else
                address.setAddress(addressString);
        }
        sequenceNumber=0;
        if (isInterfaceRegistered().isUnspecified())
                    registerInterface();
    }
    else if (stage == 2)
    {
        // tell initial channel number to ChannelControl; should be done in
        // stage==2 or later, because base class initializes myRadioRef in that stage
        cc->setRadioChannel(myRadioRef, getChannelNumber());
    }
}

void IdealMacRadio::handleMessage(cMessage *msg)
{
    if (msg->getArrivalGateId() == upperLayerIn)
    {
        // packet from upper layers, to be sent out
        cPacket *pk = PK(msg);
        handleUpperMsg(pk);
    }
    else
    {
        AirFrame *airframe = (AirFrame *) msg;
        handleLowerMsg(airframe);
    }
}

bool IdealMacRadio::processAirFrame(AirFrame *airframe)
{
    return airframe->getChannelNumber() == getChannelNumber();
}

void IdealMacRadio::handleUpperMsg(cPacket *pk){
    EV << "Packet arrived from upper layers: " << pk << "\n";
    if (pk->getByteLength() > 2312)
        error("message from higher layer (%s)%s is too long for 802.11, %d bytes (fragmentation is not supported yet)",
                pk->getClassName(), pk->getName(), (int)(pk->getByteLength()));

    Ieee80211DataFrame *frame = encapsulateInIeee80211(pk);

    if (frame->getByteLength() > fragmentationThreshold)
        error("message from higher layer (%s)%s is too long for 802.11b, %d bytes (fragmentation is not supported yet)",
                pk->getClassName(), pk->getName(), (int)(pk->getByteLength()));
    EV << "frame " << frame << " received from higher layer, receiver = " << frame->getReceiverAddress() << endl;

    // if you get error from this assert check if is client associated to AP
    ASSERT(!frame->getReceiverAddress().isUnspecified());

    // fill in missing fields (receiver address, seq number), and insert into the queue
    frame->setTransmitterAddress(address);
    frame->setSequenceNumber(sequenceNumber);
    sequenceNumber = (sequenceNumber+1) % 4096;  //XXX seqNum must be checked upon reception of frames!
    frame->setMACArrive(simTime());
    AirFrame* airframe = encapsulateInAirFrame(frame);
    EV << "sending airframe " << airframe << " on channel "<< airframe->getChannelNumber()<< " My Channel="<<getChannelNumber()<<" received from higher layer, receiver = " << frame->getReceiverAddress() << endl;
    sendDown(airframe);
}

void IdealMacRadio::handleLowerMsg(AirFrame *airframe)
{
    const Coord& framePos = airframe->getSenderPos();
    double sqrDistance = getRadioPosition().sqrdist(framePos);

    double attenuation=0;

    if(!processAirFrame(airframe)){
        EV << "airFrame discarded" <<  endl;
        delete airframe;
        return;
    }

    if (obstacles)
    {
        attenuation = obstacles->calculateReceivedPower(1, 2.4e6, framePos, 0, getRadioPosition(), 0);
        /*
         * convert to dB
         */
        attenuation = 10*log10(attenuation);
    }

    Ieee80211DataFrame *frame = check_and_cast<Ieee80211DataFrame*>(airframe->decapsulate());

    EV << "frame " << frame << " received from lower layer, receiver = " << frame->getReceiverAddress() << " My Address = " << address <<  endl;


    if(sqrDistance > sqrCommDistance || attenuation < 0)
    {
        EV << "frame " << frame << " have been discarded" << endl;
    }
    else if(isMulticast(frame) || isForUs(frame)){
        sendUp(decapsulateIeee80211(frame));
    }
    else{
     EV << "frame " << frame << " Not for us" << endl;
    }
    delete frame;
    delete airframe;
}

/*From Ieee80211MgmtAdhoc*/
Ieee80211DataFrame *IdealMacRadio::encapsulateInIeee80211(cPacket *msg)
{
    Ieee80211DataFrameWithSNAP *frame = new Ieee80211DataFrameWithSNAP(msg->getName());

    // copy receiver address from the control info (sender address will be set in MAC)
    Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl *>(msg->removeControlInfo());
    frame->setReceiverAddress(ctrl->getDest());
    frame->setEtherType(ctrl->getEtherType());
    delete ctrl;

    frame->encapsulate(msg);
    return frame;
}

/*From Radio.cc*/
AirFrame *IdealMacRadio::encapsulateInAirFrame(Ieee80211DataFrame *frame)
{

    // Note: we don't set length() of the AirFrame, because duration will be used everywhere instead
    //if (ctrl && ctrl->getAdaptiveSensitivity()) updateSensitivity(ctrl->getBitrate());
    AirFrame *airframe = createAirFrame();
    airframe->setName(frame->getName());
    airframe->setChannelNumber(getChannelNumber());
    airframe->encapsulate(frame);

    double bitrate;
    if(frame->getReceiverAddress().isMulticast())
    {
        bitrate=this->basicBitrate;
    }
    else
    {
        bitrate= this->bitrate;
    }
    airframe->setBitrate(bitrate);
    airframe->setDuration(airframe->getBitLength()/bitrate);
    airframe->setSenderPos(getRadioPosition());

    EV << "Frame (" << frame->getClassName() << ")" << frame->getName()
            << " will be transmitted at " << (airframe->getBitrate()/1e6) << "Mbps\n";
    return airframe;
}

cPacket *IdealMacRadio::decapsulateIeee80211(Ieee80211DataFrame *frame)
{
    cPacket *payload = frame->decapsulate();

    Ieee802Ctrl *ctrl = new Ieee802Ctrl();
    ctrl->setSrc(frame->getAddress3());
    ctrl->setDest(frame->getReceiverAddress());
    //TODO ctrl->setEtherType(...);
    payload->setControlInfo(ctrl);
    return payload;
}

bool IdealMacRadio::isMulticast(Ieee80211Frame *frame)
{
    return frame && frame->getReceiverAddress().isMulticast();
}

bool IdealMacRadio::isForUs(Ieee80211Frame *frame)
{
    return frame && frame->getReceiverAddress() == address;
}

void IdealMacRadio::sendDown(AirFrame *airframe)
{
    sendToChannel(airframe);
}

void IdealMacRadio::sendUp(cPacket *msg)
{
    send(msg, "upperLayerOut");
}

const MACAddress & IdealMacRadio::isInterfaceRegistered()
{
    IInterfaceTable *ift = InterfaceTableAccess().getIfExists();
    if (!ift)
        return MACAddress::UNSPECIFIED_ADDRESS;
    char *interfaceName = new char[strlen(getParentModule()->getFullName()) + 1];
    char *d = interfaceName;
    for (const char *s = getParentModule()->getFullName(); *s; s++)
        if (isalnum(*s))
            *d++ = *s;
    *d = '\0';
    InterfaceEntry * e = ift->getInterfaceByName(interfaceName);
    delete [] interfaceName;
    if (e)
        return e->getMacAddress();
    return MACAddress::UNSPECIFIED_ADDRESS;
}

void IdealMacRadio::registerInterface()
{
    IInterfaceTable *ift = InterfaceTableAccess().getIfExists();
    if (!ift)
        return;

    InterfaceEntry *e = new InterfaceEntry(this);

    // interface name: NetworkInterface module's name without special characters ([])
    char *interfaceName = new char[strlen(getFullName()) + 1];
    char *d = interfaceName;
    for (const char *s = getFullName(); *s; s++)
        if (isalnum(*s))
            *d++ = *s;
    *d = '\0';

    e->setName(interfaceName);
    delete [] interfaceName;

    // address
    e->setMACAddress(address);
    e->setInterfaceToken(address.formInterfaceIdentifier());

    e->setMtu(fragmentationThreshold);

    // capabilities
    e->setBroadcast(true);
    e->setMulticast(true);
    e->setPointToPoint(false);

    // add
    ift->addInterface(e);
}
