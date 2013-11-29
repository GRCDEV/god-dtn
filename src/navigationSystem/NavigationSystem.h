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


// This module provide information about routes and road topology
// obtained from TraCiScenarioManager and SumoNetwork
// Every coordinate is in Traci reference system.

#ifndef NAVIGATIONSYSTEM_H_
#define NAVIGATIONSYSTEM_H_

#include "Coord.h"
#include <csimplemodule.h>
#include "TraCIScenarioManager.h"
#include "SumoNetwork.h"
#include "TraCIMobility.h"
#include "clistener.h"

class NavigationSystem: public cSimpleModule,  protected cListener{
public:

    typedef struct _ap{
        std::string id;
        TraCIScenarioManager::TraCICoord traciPosition;
        Coord omnetPosition;
        double range;
        double sqrRange;
        double rate;
    }Ap;

    typedef struct _txOp{
        std::vector<std::string> edgeList;
        double startPos;
        double endPos;
        double length;
        Ap* ap;
    }TxOp;

    NavigationSystem();
    virtual ~NavigationSystem();

    virtual void initialize(int stage);
    virtual void finish();
    virtual int numInitStages() const{
        return 3;
    }

    struct _nextTxOpCache{
        Coord   lastLocation;
        simtime_t lastUpdate;
        TxOp    *nextTxOp;
        double  duration;
        double  distance;
        double  time;
    } nextTxOpCache;

    /*
     * This class assumes circular coverage areas
     */
    //Return the distance in meters to next transmission opportunity.
    double getDistanceNextTxOpportunity();

    //Return the estimated time to the next transmission opportunity.
    double getTimeToNextTxOpportunity();

    //Return the estimated duration of the next Tx Opportunity
    double getDurationNextTxOpportunity();

    const TxOp* getNextTxOp() const{
        if(!oportunities.empty())
            return oportunities.front();
        else
            return NULL;
    }

    //Return current route edges
    const std::vector<std::string> getRoute() const;
    //Return the not visited edge list, including the current edge
    const std::vector<std::string> getLeftEdges() const;
    //get the current path on *result
    const std::vector<Coord> getCurrentPath() const;

    //Return the current Edge id
    const std::string getCurrentRoad() const;


    //Return the nearest point of the route to the closest POA
    struct _NPCache{
        std::string lastRouteId;
        uint lastModId;
        double previousDistance;
        double previousAvgSpeed;
        double previousTotalLength;
        double previousTime;
        Coord previousPos;
        Coord previousBestPoint;
        simtime_t previousCall;
    } NPCache;

    Coord getNearestPointInRouteToPoa(double &timeToArrive, double &distance, double &avgSpeed);

    double getDistanceNextJoint() const;

    void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    simsignal_t mobilityStateChangedSignal;

    Coord getCurrentPosition() const;

    Coord getCurrentSpeed() const;

    double getSpeedMod() const;
    double getSpeedAngle() const;

    int getNumOp() const;

    /*
     * return a list of Poas ID that the node will traverse
     */
    const std::list<std::string> getPoas() const;

    const std::list<NavigationSystem::TxOp*> getTxOpList() const;

    const std::vector<NavigationSystem::Ap> getPoaList() const;

    const NavigationSystem::Ap getClosestPoa() const;

    /*
     * return a list of the Poas sorted by distance. The first element of the list is the closest Poa.
     */
    const std::list <NavigationSystem::Ap> getPoasSortedByDistance() const;

    double getAverageSpeed() const;
private:
    //Parse POA xml file, return false if not defined.
    bool parsePOA();

    //Intersection between a segment defined by coord0 and coord1 and a circumference defined by
    //center and radius
    std::vector<Coord> getIntersection(Coord Coord0, Coord Coord1, Coord center, double radius);

    //Get the distance between a segment and a point
    double getDistance(Coord coord0, Coord coord1, Coord coord3, Coord &nearestPoint);

    //Check if route has changed since last update
    bool hasRouteChanged();

    bool hasEdgeChanged();

    //Update current route and recalculate all the values
    void updateRoute();

    void updateStatus();

    void registerSignals();

    bool checkCoverage(Coord coord, Ap **ap);

    std::string traciId;
    std::string routeId;
    std::vector<std::string> edgeList;
    uint lastEdgeIndex;
    std::vector<std::string> visitedRoads;
    std::string currentEdge;
    Coord lastPosition;
    Coord lastSpeed;
    double avgSpeed;
    uint   nSpeed;
    uint avgSpeedWindow;
    std::vector<double> speedMeasurements;
    simtime_t lastUpdate;
    Ap *currentAp;
    std::vector<Ap> poaList;
    std::list<TxOp*> oportunities;
    bool inTxOp;
    TraCIMobility *mobility;
    TraCIScenarioManager* manager;
    SumoNetwork* network;
    bool poaExists;
    bool initialized;
    bool debug;
};

#endif /* NAVIGATIONSYSTEM_H_ */
