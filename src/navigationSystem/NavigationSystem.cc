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

#include "NavigationSystem.h"
#include "csimulation.h"
#include <cfloat>
#include <math.h>

Define_Module(NavigationSystem)

NavigationSystem::NavigationSystem() {
    // TODO Auto-generated constructor stub
}

NavigationSystem::~NavigationSystem() {
    // TODO Auto-generated destructor stub
}

void NavigationSystem::initialize(int stage)
{
    if(stage != 2)
    {
        return;
    }

    debug = par("debug");
    mobility = ModuleAccess<TraCIMobility>("mobility").get();
    traciId = mobility->getExternalId();
    manager = mobility->getManager();
    network = dynamic_cast<SumoNetwork *>(simulation.getModuleByPath("sumoNetwork"));
    poaExists = parsePOA();
    inTxOp = false;
    nSpeed = 0;
    avgSpeedWindow = par("avgSpeedWindow");
    updateRoute();
    registerSignals();
    updateStatus();
}

Coord NavigationSystem::getCurrentPosition() const
{
    Enter_Method_Silent();
    Coord position;
    simtime_t time= simTime() - lastUpdate;
    position.x = lastPosition.x + lastSpeed.x*time.dbl();
    position.y = lastPosition.y + lastSpeed.y*time.dbl();
    return position;
}

Coord NavigationSystem::getCurrentSpeed() const
{
    Enter_Method_Silent();
    return lastSpeed;
}

double NavigationSystem::getSpeedMod() const
{
    Enter_Method_Silent();
    return mobility->getSpeed();
}

double NavigationSystem::getSpeedAngle() const
{
    Enter_Method_Silent();
    return atan(lastSpeed.y/lastSpeed.x);
}

void NavigationSystem::registerSignals()
{
    //Traci signal registration
    mobilityStateChangedSignal = registerSignal("mobilityStateChanged");
    mobility->subscribe(mobilityStateChangedSignal, this);
}

void NavigationSystem::finish()
{
}

double NavigationSystem::getDistanceNextTxOpportunity()
{
    Enter_Method_Silent();

    if(hasRouteChanged()){
        updateRoute();
    }

    const TxOp *txOp = getNextTxOp();
    Coord currentLoc = getCurrentPosition();
    if(txOp == NULL){
        return FLT_MAX;
    }

    if(txOp == nextTxOpCache.nextTxOp && nextTxOpCache.lastLocation == currentLoc){
        return nextTxOpCache.distance;
    }

    std::vector<std::string> leftEdge= getLeftEdges();
    double currentPos;
    if(currentEdge != leftEdge[0]){
        currentPos = 0;
    }
    else{
        currentPos = manager->commandGetLanePosition(traciId);
    }

    double distance;


    std::string startEdge = txOp->edgeList.front();
    /*If it is currently connected, return 0*/
    if( checkCoverage( currentLoc , NULL) ){
        distance = 0;
    }
    /*If current edge is equal to the first edge of the opportunity
     * return the distance from the current pos to the start pos.
     */
    else if(leftEdge.at(0) == startEdge){
        if(txOp->startPos < currentPos){
            distance = 0;
        }
        distance = txOp->startPos-currentPos;
    }
    /*
     * In any other case:
     * Sum the rest of the current edge
     * Sum the length of every edge in the route until i==startEdge
     * Sum the portion of the previous edge.
     */
    else {
        distance = network->getEdgeLength(leftEdge.at(0))-currentPos;
        for(std::vector<std::string>::const_iterator i=(leftEdge.begin()+1); i!= leftEdge.end() && (*i) != startEdge ; i++){
            if(debug){
                EV << "*i "<< *i << " startEdge "<< startEdge<< endl;
            }
            distance+=(network-> getEdgeLength(*i));
        }
        distance+= distance+txOp->startPos;
    }
    nextTxOpCache.distance = distance;
    nextTxOpCache.lastLocation = currentLoc;
    return nextTxOpCache.distance;
}

double NavigationSystem::getTimeToNextTxOpportunity()
{
    Enter_Method_Silent();

    if(hasRouteChanged()){
        updateRoute();
    }

    const TxOp *txOp = getNextTxOp();
    Coord currentLoc = getCurrentPosition();

    if(txOp == nextTxOpCache.nextTxOp && nextTxOpCache.lastUpdate == simTime()){
        return nextTxOpCache.time;
    }

    std::vector<std::string> leftEdge= getLeftEdges();
    double currentPos;
    if(currentEdge != leftEdge[0]){
        currentPos = 0;
    }
    else{
        currentPos = manager->commandGetLanePosition(traciId);
    }


    double time;

    if(txOp == NULL){
        time = FLT_MAX;
        return time;
    }

    std::string startEdge = txOp->edgeList.front();

    if( checkCoverage(currentLoc, NULL) ){
        return 0;
    }
    else if(leftEdge.at(0) == startEdge){
        if(txOp->startPos > currentPos){
            return 0;
        }
        return txOp->startPos/network->getEdgeMaxSpeed(txOp->edgeList.at(0));
    }
    else {
        time = (network->getEdgeLength(leftEdge.at(0))-currentPos)/network->getEdgeMaxSpeed(leftEdge.at(0));
        for(std::vector<std::string>::const_iterator i=(leftEdge.begin()+1); i!= leftEdge.end() && (*i) != startEdge ; i++){
            if(debug){
                EV << "*i "<< *i << " startEdge "<< startEdge<< endl;
            }
            time+=(network-> getEdgeLength(*i))/network->getEdgeMaxSpeed(*i);;
        }
    }
    nextTxOpCache.lastUpdate = simTime();
    nextTxOpCache.time = time+txOp->startPos/network->getEdgeMaxSpeed(txOp->edgeList.at(0));
    return nextTxOpCache.time;
}

double NavigationSystem::getDurationNextTxOpportunity()
{
    Enter_Method_Silent();
    /*
     * Check if the route has changed
     */
    if( hasRouteChanged() ){
        updateRoute();
    }

    /*
     * Get the next transmission opportunity and return if it does not exist
     */
    const TxOp *txOp = getNextTxOp();
    if(txOp == NULL){
        return 0;
    }

    /*
     * Get the current location to check if the node is alredy connected
     */
    Coord currentLoc = getCurrentPosition();

    double currentPos;

    if(network->getEdgeIsInternal(currentEdge)){
        currentPos = 0;
    }
    else{
        currentPos = manager->commandGetLanePosition(traciId);
    }

    std::vector<std::string>::const_iterator startEdge=txOp->edgeList.begin();
    double time = 0;
    /*
     * if the node is already connected find the current road in the txOp and sum up the remaining time in the current road
     */
    if( checkCoverage(getCurrentPosition(), NULL)){
        std::string nextRoad = getLeftEdges().front();
        for(std::vector<std::string>::const_iterator i = txOp->edgeList.begin();i != txOp->edgeList.end(); i++){
            /*
             * Sum the time that left in the current street.
             */
            if( (*i) == nextRoad){
                startEdge = i+1;
                double length = network->getEdgeLength(nextRoad)-currentPos;
                double speed = network->getEdgeMaxSpeed(nextRoad);
                time +=  length/ speed;
                ASSERT(length > 0 && speed > 0 && time > 0);
                break;
            }
        }
    }
    else {
        /*
         * Sum the time from startPos to the end of the first edge
         */
        if(txOp->edgeList.size() != 1){
            double length = network->getEdgeLength(*startEdge)-txOp->startPos;
            double speed = network->getEdgeMaxSpeed(*startEdge);
            time +=  length/ speed;
            ASSERT(length > 0 && speed > 0 && time > 0);
        }
        else{
            return (txOp->endPos-txOp->startPos)/network->getEdgeMaxSpeed(*startEdge);
        }
        startEdge++;
    }

    for(;startEdge != txOp->edgeList.end(); startEdge++ ) {
        /*
         * Sum the time to cover the edge *i, including the last one.
         */
        double length = network->getEdgeLength(*startEdge);
        double speed = network->getEdgeMaxSpeed(*startEdge);
        time +=  length/ speed;
        ASSERT(length > 0 && speed > 0 && time > 0);
        /*
         * Subtract the non-traversed part of the last edge
         */
        if( startEdge == (txOp->edgeList.end()-1)){
            double length = network->getEdgeLength(*startEdge)-txOp->endPos;
            double speed = network->getEdgeMaxSpeed(*startEdge);
            time -=  length/ speed;
            ASSERT(length >= 0 && speed > 0 && time >= 0);
        }
    }
    return time;
}

const std::vector<std::string> NavigationSystem::getLeftEdges() const
{
    Enter_Method("getLeftEdges");
    std::vector<std::string> leftEdges;
    uint i=0;
    for( uint j=0; j < visitedRoads.size() && i < edgeList.size(); j++){
        if(visitedRoads.at(j) == edgeList.at(i)){
            i++;
        }
    }

    for(;i<edgeList.size(); i++){
        leftEdges.push_back(edgeList.at(i));
    }

    ASSERT(!leftEdges.empty());
    return leftEdges;
}

const std::vector<std::string> NavigationSystem::getRoute() const
{
    Enter_Method_Silent();
    return edgeList;
}

const std::vector<Coord> NavigationSystem::getCurrentPath() const
{
    Enter_Method_Silent();
    std::vector<Coord> path;
    TraCIScenarioManager::TraCICoord coord = network->getEdgeFrom(edgeList[0]);
    path.push_back(manager->traci2omnet(coord));
    for(uint i=0; i < edgeList.size(); i++)
    {
        std::vector<TraCIScenarioManager::TraCICoord> shape = network->getEdgeShape(edgeList[i]);

        for(std::vector<TraCIScenarioManager::TraCICoord>::iterator i = shape.begin(); i != shape.end(); i++){
            TraCIScenarioManager::TraCICoord to = *i;
            path.push_back(manager->traci2omnet(to));
        }
    }
    return path;
}

const std::string NavigationSystem::getCurrentRoad() const
{
    Enter_Method_Silent();
    return manager->commandGetEdgeId(traciId);
}

double NavigationSystem::getDistanceNextJoint() const
{
    Enter_Method_Silent();
    return network->getEdgeLength(manager->commandGetEdgeId(traciId))-manager->commandGetLanePosition(traciId);
}

bool NavigationSystem::parsePOA()
{
    cXMLElement* networkFile = par("poaConfig").xmlValue();

    std::string rootTag = networkFile->getTagName();
    ASSERT(rootTag == "poas");
    cXMLElementList poaList = networkFile->getElementsByTagName("poa");
    if(poaList.size() == 0)
    {
        return false;
    }

    for (cXMLElementList::const_iterator i = poaList.begin(); i != poaList.end(); ++i) {
        cXMLElement* e = *i;
        Ap poa;
        std::string id;

        double x;
        double y;
        double rate;
        double range;
        ASSERT(e->getAttribute("id"));
        id = e->getAttribute("id");
        ASSERT(e->getAttribute("x"));
        x = atof(e->getAttribute("x"));
        ASSERT(e->getAttribute("y"));
        y = atof(e->getAttribute("y"));
        ASSERT(e->getAttribute("rate"));
        rate= atof(e->getAttribute("rate"));
        ASSERT(e->getAttribute("range"));
        range= atof(e->getAttribute("range"));
        poa.id=id;
        poa.traciPosition = TraCIScenarioManager::TraCICoord(x,y);
        poa.omnetPosition = manager-> traci2omnet(TraCIScenarioManager::TraCICoord(x,y));
        poa.rate=rate;
        poa.range = range;
        poa.sqrRange = range*range;

        this->poaList.push_back(poa);
    }
    return true;
}

std::vector<Coord> NavigationSystem::getIntersection(Coord from, Coord to, Coord center, double R)
{
    Enter_Method_Silent();
    double m = 0;
    bool vertical=false;
    if(to.x != from.x){
     m = (to.y-from.y) / (to.x-from.x); //Step of the segment
     vertical = false;
    }
    else {
        vertical = true;
    }
    std::vector<Coord> out;
    Coord point1;
    Coord point2;
    //Solve the system
    // y= mx+alpha
    // (x_0-x)^2+(y_0-y)^2 = r^2
    if(!vertical){
        double alpha = from.y-m*from.x;
        double a = m*m+1;
        double b = 2*m*alpha - 2*center.x - 2*m*center.y;
        double c = center.x*center.x +alpha*alpha+center.y*center.y - 2*center.y*alpha - R*R;

        if((b*b - 4*a*c) < 0 )
        {
            return out;
        }


        point1.x = (-b + sqrt(b*b-4*a*c)) / (2*a);
        point1.y = m*point1.x+alpha;

        point2.x = (-b - sqrt(b*b-4*a*c)) / (2*a);
        point2.y = m*point2.x+alpha;
    }
    else{
        point1.x = point2.x = from.x;
        double a = 1;
        double b = -2*center.y;
        double c = from.x*from.x - 2*from.x*center.x + to.x*to.x + center.y*center.y - R*R;

        if((b*b-4*a*c) < 0 )
        {
            return out;
        }

        point1.y = (-b + sqrt(b*b-4*a*c))/(2*a);
        point2.y = (-b - sqrt(b*b-4*a*c))/(2*a);
    }
    out.push_back(point1);
    out.push_back(point2);
    return out;
}

bool NavigationSystem::hasRouteChanged()
{
    return manager->commandGetRouteId(traciId)!=routeId;
}

bool NavigationSystem::hasEdgeChanged()
{
    return manager->commandGetEdgeId(traciId)!= currentEdge;
}

void NavigationSystem::updateRoute()
{
    routeId = manager->commandGetRouteId(traciId);
    std::list<std::string> route = manager->commandGetRouteEdgeIds(routeId);
    ASSERT(!route.empty());
    currentEdge = manager->commandGetEdgeId(traciId);

    visitedRoads.clear();
    edgeList.clear();
    lastEdgeIndex = 0;

    bool connected=false;
    bool started = false;
    for(std::list<std::string>::const_iterator i= route.begin(); i!= route.end(); i++)
    {
        std::string edgeId=*i;
        if(currentEdge != edgeId && started == false )
        {
        }
        else {
            started = true;
        }
        edgeList.push_back(edgeId);
        std::vector<TraCIScenarioManager::TraCICoord> shape = network->getEdgeShape(edgeId);
        std::vector<TraCIScenarioManager::TraCICoord>::const_iterator j = shape.begin();
        j++;
        for(std::vector<TraCIScenarioManager::TraCICoord>::const_iterator previous=shape.begin(); j!=shape.end(); j++, previous++)
        {
            TraCIScenarioManager::TraCICoord traciFrom = *previous;
            TraCIScenarioManager::TraCICoord traciTo = *j;

            Coord from = manager->traci2omnet(traciFrom);
            Coord to = manager-> traci2omnet(traciTo);
            for(uint k=0; k< poaList.size();k++)
            {
                Ap ap = poaList[k];
                Coord nearestPoint;
                double distance = getDistance(from, to, ap.omnetPosition, nearestPoint);
                //part of the segment is under the coverage of an AP
                if( distance < ap.range )
                {
                    TxOp *txOp;
                    if(connected==false)
                    {
                        txOp= new TxOp;
                        txOp->startPos=0;
                        txOp->length=0;
                        oportunities.push_back(txOp);
                    }
                    else
                    {
                        txOp = oportunities.back();
                    }

                    txOp->ap = &poaList[k];
                    txOp->endPos = network->getEdgeLength(edgeId);
                    if(txOp->edgeList.empty() || txOp->edgeList.back() != edgeId)
                    {
                        txOp->edgeList.push_back(edgeId);
                    }


                    std::vector<Coord> intersection = getIntersection(from, to, ap.omnetPosition, ap.range);

                    ASSERT(intersection.size() == 2);

                    if(to.sqrdist(ap.omnetPosition) > ap.sqrRange && from.sqrdist(ap.omnetPosition) > ap.sqrRange)
                    {
                        // from O-----X++++++++++X-----O to
                        ASSERT(!connected);
                        //This opportunity starts and ends during this segment.

                        txOp->length = intersection[0].distance(intersection[1]);

                        if(intersection[0].distance(from) < intersection[1].distance(from))
                        {
                            txOp->startPos = intersection[0].distance(from);
                            txOp->endPos = intersection[1].distance(from);
                        }
                        else
                        {
                            txOp->endPos = intersection[0].distance(from);
                            txOp->startPos = intersection[1].distance(from);
                        }

                        connected=false;
                    }
                    else if(to.sqrdist(ap.omnetPosition) > ap.sqrRange && from.sqrdist(ap.omnetPosition) < ap.sqrRange)
                    {
                        // from O+++++++X-----O to
                        //This opportunity ends during this segment
                        double dist0 = from.distance(intersection[0]);
                        double dist1 = from.distance(intersection[1]);
                        double dist;

                        if( dist0+to.distance(intersection[0]) <
                            dist1+to.distance(intersection[1]) )
                        {
                            dist=dist0;
                        }
                        else
                        {
                            dist=dist1;
                        }

                        txOp->length += dist;
                        txOp->endPos = dist;
                        connected=false;
                    }
                    else if(to.sqrdist(ap.omnetPosition) < ap.sqrRange && from.sqrdist(ap.omnetPosition)  > ap.sqrRange)
                    {
                        // from O----X+++++++++O to
                        //This opportunity starts in this segment
                        double dist0 = to.distance(intersection[0]);
                        double dist1 = to.distance(intersection[1]);
                        double dist;

                        if( dist0+from.distance(intersection[0]) <
                                dist1+from.distance(intersection[1]) )
                        {
                            dist=dist0;
                            txOp->startPos = from.distance(intersection[0]);
                        }
                        else
                        {
                            dist=dist1;
                            txOp->startPos = from.distance(intersection[1]);
                        }

                        txOp->length = dist;
                        connected=true;
                    }
                    else
                    {
                        // from O+++++++++++O to
                        //The whole segment is under the coverage of the AP
                        txOp->length += from.distance(to);
                        connected=true;
                    }
                }
            }
        }
    }



}

double NavigationSystem::getDistance(Coord coord0, Coord coord1, Coord coord3, Coord &nearestPoint)
{
    Enter_Method_Silent();
    double dist10= coord1.distance(coord0);
    double projection;
    Coord intersection;
    projection = ((coord3.x-coord0.x)*(coord1.x-coord0.x)+(coord3.y-coord0.y)*(coord1.y-coord0.y))/dist10;

    double u = projection/dist10;

    if( u <= 0 )
    {
        nearestPoint = coord0;
    }
    else if( u >= 1 )
    {
        nearestPoint = coord1;
    }
    else{
        intersection.x = coord0.x + u * (coord1.x-coord0.x);
        intersection.y = coord0.y + u * (coord1.y-coord0.y);
        nearestPoint = intersection;
    }
    return coord3.distance(nearestPoint);
}

void NavigationSystem::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    if (signalID == mobilityStateChangedSignal) {
        updateStatus();
    } else {
        EV << "Signal received" << signalID << endl;
    }
}

void NavigationSystem::updateStatus()
{
    Enter_Method("updatreStatus");
    if(hasEdgeChanged())
    {
        if(!network->getEdgeIsInternal(currentEdge)){
            std::vector<std::string> edgesPassed;
            uint last = lastEdgeIndex;
            bool found=false;
            while(!found && last < edgeList.size()){
                if(edgeList.at(last) != currentEdge){
                    edgesPassed.push_back(edgeList.at(last));
                    last++;
                }
                else{
                    found = true;
                    lastEdgeIndex = ++last;
                }
            }

            if(found && edgesPassed.size()>0){
                /*
                 * add every edge until the previous One
                 */
                visitedRoads.insert(visitedRoads.end(), edgesPassed.begin(), edgesPassed.end());
            }

            /*
             * add the last edge
             */
            visitedRoads.push_back(currentEdge);
        }
        currentEdge = manager->commandGetEdgeId(traciId);
    }

    if(hasRouteChanged())
    {
        updateRoute();
    }

    lastPosition= mobility->getCurrentPosition();
    lastPosition.x = lastPosition.x+par("gpsError").doubleValue();
    lastPosition.y = lastPosition.y+par("gpsError").doubleValue();

    lastSpeed = mobility-> getCurrentSpeed();
    avgSpeed = (avgSpeed*nSpeed + mobility->getSpeed())/(nSpeed+1);
    nSpeed++;
    speedMeasurements[nSpeed%avgSpeedWindow] = mobility->getSpeed();
    lastUpdate = simTime();

    bool connected=checkCoverage(getCurrentPosition(), &currentAp);

    if(connected != inTxOp && connected == false)
    {
        ASSERT(!oportunities.empty());
        oportunities.pop_front();
    }

    if(connected == true && !oportunities.empty() && currentAp->id == oportunities.front()->ap->id){
        inTxOp = connected;
    }
    else {
        inTxOp = false;
        currentAp = NULL;
    }
}

Coord NavigationSystem::getNearestPointInRouteToPoa(double &timeToArrive, double &distance, double &avgSpeed)
{
    if(NPCache.previousDistance != 0 && NPCache.lastRouteId == routeId){
        distance = NPCache.previousDistance;
        avgSpeed = NPCache.previousAvgSpeed;
        timeToArrive = NPCache.previousTime;
        NPCache.previousCall = simTime();
        if(NPCache.previousPos != lastPosition){
            double delta = NPCache.previousPos.distance(lastPosition);
            double totalLength = NPCache.previousTotalLength-delta;
            timeToArrive = totalLength/NPCache.previousAvgSpeed;
            NPCache.previousTime = timeToArrive;
            NPCache.previousTotalLength = totalLength;
            NPCache.previousPos = lastPosition;
            if(totalLength > 0){
                return NPCache.previousBestPoint;
            }
        }
        else{
            return NPCache.previousBestPoint;
        }
    }
    std::vector<std::string> leftEdge = getLeftEdges();
    ASSERT(!leftEdge.empty());

    double currentPos;
    if(currentEdge != leftEdge[0]){
        currentPos = 0;
    }
    else{
        currentPos = manager->commandGetLanePosition(traciId);
    }
    avgSpeed = 0;
    double totalSpeed = 0;
    double totalLength = 0;
    //This is a fake Coord object!!
    Coord nearestPoint;
    double time = 0;
    double minDist = -1;
    std::string bestEdge;
    double bestEdgePos;
    bool bestPoaFound = false;
    /*
     * iterate over the sorted Poas to find the closest poa which the car has not passed by.
     */
    std::list<NavigationSystem::Ap> sortedPoas = getPoasSortedByDistance();
    for(std::list<NavigationSystem::Ap>::iterator poaIt = sortedPoas.begin(); poaIt != sortedPoas.end(); poaIt++){
        TraCIScenarioManager::TraCICoord poaLoc = poaIt->traciPosition;
        for(uint i = 0; i< leftEdge.size(); i++){
            double edgePos = 0;
            std::vector<TraCIScenarioManager::TraCICoord> shape = network->getEdgeShape(leftEdge[i]);
            for(std::vector<TraCIScenarioManager::TraCICoord>::iterator j = shape.begin(); j != shape.end()-1; j++){
                TraCIScenarioManager::TraCICoord from = *j;
                TraCIScenarioManager::TraCICoord to = *(j+1);
                Coord nearestPoint_t;
                Coord poaLoc2(poaLoc.x, poaLoc.y);
                Coord from2(from.x, from.y);
                Coord to2(to.x, to.y);
                double dist = getDistance(from2, to2, poaLoc2, nearestPoint_t);
                if(dist < minDist || minDist < 0){
                    minDist = dist;
                    nearestPoint = nearestPoint_t;
                    bestEdge = leftEdge[i];
                    bestEdgePos = edgePos+from2.distance(nearestPoint_t);
                }
                edgePos+=from2.distance(to2);
            }
        }
        if(bestEdge == currentEdge && bestEdgePos <= currentPos){
            minDist = -1;
            continue;
        }
        else{
            bestPoaFound = true;
            break;
        }
    }



    if(!bestPoaFound){
        minDist = FLT_MAX;
        totalLength = FLT_MAX;
        totalSpeed = 1;
    }
    else if(bestEdge == currentEdge){
        ASSERT(bestEdgePos > currentPos);
        time +=  (bestEdgePos - currentPos)/ network->getEdgeMaxSpeed(leftEdge[0]);
        totalSpeed += network->getEdgeMaxSpeed(leftEdge[0])* (bestEdgePos - currentPos);
        totalLength += (bestEdgePos - currentPos);
    }
    else{
        time += (network->getEdgeLength(leftEdge[0]) - currentPos ) / network->getEdgeMaxSpeed(leftEdge[0]);
        totalSpeed += network->getEdgeMaxSpeed(leftEdge[0])* (network->getEdgeLength(leftEdge[0]) - currentPos );
        totalLength += (network->getEdgeLength(leftEdge[0]) - currentPos);
        if(time < 0){
            time = 0;
            totalSpeed = 0;
            totalLength = 0;
        }
        for(uint i = 1; i< leftEdge.size() && leftEdge[i] != bestEdge; i++){
            time += network->getEdgeLength(leftEdge[i])/network->getEdgeMaxSpeed(leftEdge[i]);

            totalSpeed += network->getEdgeMaxSpeed(leftEdge[0])* network->getEdgeLength(leftEdge[i]);
            totalLength += network->getEdgeLength(leftEdge[i]);
        }

        time += bestEdgePos / network->getEdgeMaxSpeed(bestEdge);
        totalSpeed += network->getEdgeMaxSpeed(bestEdge) * bestEdgePos;
        totalLength += bestEdgePos;
    }

    timeToArrive = NPCache.previousTime = time;
    NPCache.previousDistance = distance = minDist;
    NPCache.previousTotalLength = totalLength;
    if(totalSpeed > 0 ){
        NPCache.previousAvgSpeed = avgSpeed = totalSpeed/totalLength;
    }
    else {
        NPCache.previousAvgSpeed = 0;
    }

    ASSERT(distance > 0 && totalLength >= 0 && avgSpeed >= 0);
    NPCache.lastRouteId = routeId;
    NPCache.previousPos = lastPosition;
    NPCache.previousCall = simTime();
    //Convert from TraciCoord to Coord
    NPCache.previousBestPoint = manager->traci2omnet(TraCIScenarioManager::TraCICoord(nearestPoint.x, nearestPoint.y));
    return NPCache.previousBestPoint;
}

const NavigationSystem::Ap NavigationSystem::getClosestPoa() const
{
    double minSqrDist = 0;
    NavigationSystem::Ap ap;
    for(uint i=0; i< poaList.size(); i++){
        double sqrDist = getCurrentPosition().sqrdist(poaList[i].omnetPosition);
        if(sqrDist< minSqrDist || minSqrDist == 0){
            minSqrDist = sqrDist;
            ap = poaList[i];
        }
    }
    return ap;
}

double NavigationSystem::getAverageSpeed() const
{
    double sum=0;

    if(nSpeed<avgSpeedWindow){
        return avgSpeed;
    }

    for(uint i = 0; i< avgSpeedWindow; i++){
        sum+=speedMeasurements[i];
    }

    return sum / avgSpeedWindow;
}

const std::list<NavigationSystem::Ap> NavigationSystem::getPoasSortedByDistance() const
{
    std::list<NavigationSystem::Ap> sortedList;
    std::vector<NavigationSystem::Ap> poaList = getPoaList();
    sortedList.push_back(*poaList.begin());
    for(uint i=1; i < poaList.size(); i++){
        NavigationSystem::Ap poa = poaList.at(i);
        double sqrDistance = poa.omnetPosition.sqrdist(lastPosition);
        bool inserted = false;
        for(std::list<NavigationSystem::Ap>::iterator j=sortedList.begin(); j != sortedList.end(); j++){
            if(sqrDistance < (j->omnetPosition.sqrdist(lastPosition) ) ){
                sortedList.insert(j, poa);
                inserted = true;
                break;
            }
        }
        if(!inserted){
            sortedList.push_back(poa);
        }
    }
    return sortedList;
}

/*Check the coverage of current position, store the current ap in ap*/
bool NavigationSystem::checkCoverage(Coord coord, Ap **ap)
{
    for(uint i=0; i < poaList.size(); i++)
    {
        if(coord.sqrdist(poaList[i].omnetPosition) < poaList[i].sqrRange)
        {
            if(ap != NULL)
                *ap=&poaList[i];
            return true;
        }
    }
    return false;
}

int NavigationSystem::getNumOp() const
{
    Enter_Method_Silent();
    return oportunities.size();
}

const std::list<std::string> NavigationSystem::getPoas() const
{
    Enter_Method_Silent();
    std::list<std::string> poas;
    for(std::list<NavigationSystem::TxOp*>::const_iterator i= oportunities.begin();i!=oportunities.end(); i++)
    {
        poas.push_back((*i)->ap->id);
    }
    return poas;
}

const std::vector<NavigationSystem::Ap> NavigationSystem::getPoaList() const
{
    Enter_Method_Silent();
    return poaList;
}

const std::list<NavigationSystem::TxOp*> NavigationSystem::getTxOpList() const
{
    Enter_Method_Silent();
    return oportunities;
}








