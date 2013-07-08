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

#include "NavClient.h"
#include "NavigationSystem.h"

Define_Module(NavClient);

void NavClient::initialize(int stage)
{
    if(stage!=3)
    {
        return;
    }
    nav = ModuleAccess<NavigationSystem>("navigationSystem").get();
    test();

    cMessage *msg = new cMessage("NEXT_PROBE");

    scheduleAt(simTime()+par("probeTime"), msg);
}

void NavClient::test(){
    //Get route
    std::vector<std::string> route = nav->getLeftEdges();

    EV<< "Route";
    for(uint i=0; i<  route.size();i++)
    {
        EV<<route[i]<<endl;
    }

    std::list<NavigationSystem::TxOp*> opportunities = nav->getTxOpList();

    for(std::list<NavigationSystem::TxOp*>::const_iterator i= opportunities.begin(); i!= opportunities.end(); i++)
    {
        EV<<"AP"<<(*i)->ap->id<<" Length:"<<(*i)->length<<"startPos"<<(*i)->endPos<<endl;

    }

    std::string currentRoad= nav->getCurrentRoad();

    EV<< "Current Road:"<< currentRoad<< endl;

    std::vector<Coord> currentPath = nav->getCurrentPath();

    EV<<"Path"<<endl;
    for(uint i=0; i< currentPath.size(); i++)
    {
        EV<<currentPath[i].x<<","<<currentPath[i].y<<":";
    }

    EV << endl;

    EV << "Distance to first Joint " << nav->getDistanceNextJoint() << endl;

    EV << "Distance to first TxOp " << nav->getDistanceNextTxOpportunity() << endl;

    EV << "Time to first TxOp " << nav->getTimeToNextTxOpportunity() << endl;

    EV << "Duration Next TxOp " << nav->getDurationNextTxOpportunity() << endl;

    EV << "Number of TxOp"<< nav->getNumOp()<<endl;
}

int NavClient::numInitStages() const{
        return 4;
    }

void NavClient::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        std::string currentRoad= nav->getCurrentRoad();

        EV<< simTime() << " Current Road:"<< currentRoad<< endl;
        scheduleAt(simTime()+par("probeTime"), msg);

    }
}
