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

#ifndef __INETMANET_2_0_IDEALMACRADIO_H_
#define __INETMANET_2_0_IDEALMACRADIO_H_

#include <omnetpp.h>
#include <Coord.h>
#include <Ieee80211Frame_m.h>
#include <AirFrame_m.h>
#include <IChannelControl.h>
#include <ChannelControl.h>
#include <ObstacleControl.h>
#include <ChannelAccess.h>

class IdealMacRadio : public ChannelAccess
{
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void handleUpperMsg(cPacket *msg);
    virtual void handleLowerMsg(AirFrame *airframe);
    virtual AirFrame *createAirFrame() {return new AirFrame();}
  private:
    /** Utility method: sends the packet to the upper layer */
    virtual void sendUp(cPacket *msg);
    /** Utility method: sends the packet to the ChannelControl */
    virtual void sendDown(AirFrame *airframe);
    /** Encapsulates an IP packet in a Mac frame */
    Ieee80211DataFrame *encapsulateInIeee80211(cPacket *msg);
    /** Encapsulates a MAC frame into an Air Frame */
    virtual AirFrame *encapsulateInAirFrame(Ieee80211DataFrame *msg);
    cPacket *decapsulateIeee80211(Ieee80211DataFrame *frame);
    const MACAddress & isInterfaceRegistered();


    bool isMulticast(Ieee80211Frame *frame);
    bool isForUs(Ieee80211Frame *frame);

    double calculateDuration(AirFrame *airframe);

    bool processAirFrame(AirFrame *airframe);
    int getChannelNumber(){return channelNumber;}

    void registerInterface();

    IChannelControl* cc;
    ObstacleControl* obstacles;

    double bitrate;
    bool registered;
    int channelNumber;
    double basicBitrate;
    int upperLayerIn;
    int upperLayerOut;
    MACAddress address;
    double commDistance;
    double sqrCommDistance;
    /** Messages longer than this threshold will be sent in multiple fragments. see spec 361 */
    static const int fragmentationThreshold = 2346;

    u_int sequenceNumber;
};

#endif
