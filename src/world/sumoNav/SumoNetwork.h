// Sergio Martínez Tornell sertinell@gmail.com htttp://www.grc.upv.es
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

#ifndef SUMONETWORK_H_
#define SUMONETWORK_H_

#include <omnetpp.h>
#include "INETDefs.h"
#include <csimplemodule.h>
#include "TraCIScenarioManager.h"
#include <map>

class SumoNetwork: public cSimpleModule {

private:
    typedef struct _junction{
        std::string id;
        TraCIScenarioManager::TraCICoord position;
    }Junction;

    typedef struct _edge{
        std::string id;
        std::vector<TraCIScenarioManager::TraCICoord> shape;
        Junction* from;
        Junction* to;
        double length;
        double maxSpeed;
        bool internal;
        std::list<std::string> laneList;
    }Edge;

    bool debug;

    TraCIScenarioManager::TraCICoord String2Coord(const std::string &str);
    std::vector<TraCIScenarioManager::TraCICoord> String2Shape(const std::string &str);
    TraCIScenarioManager* manager;
    std::map<std::string, Junction> junctionMap;
    std::map<std::string, Edge>     edgeMap;
    std::list<std::string> junctionList;
    std::list<std::string> edgeList;
public:
    SumoNetwork();
    virtual ~SumoNetwork();
    virtual int numInitStages() const { return std::max(cSimpleModule::numInitStages(), 3); }
    virtual void initialize(int stage);
    virtual void finish();

    void addJunction(Junction junction);
    void addEdge(Edge edge);

    const std::list<std::string> getJunctionIds();
    TraCIScenarioManager::TraCICoord getJunctionPosition(std::string junctionId);

    const std::list<std::string> getEdgeIds();
    const TraCIScenarioManager::TraCICoord getEdgeFrom(std::string edgeId);
    const TraCIScenarioManager::TraCICoord getEdgeTo(std::string edgeId);
    double getEdgeLength(std::string edgeId);
    double getEdgeMaxSpeed(std::string edgeId);
    std::vector<TraCIScenarioManager::TraCICoord> getEdgeShape(std::string edgeId);
    std::list<std::string> getEdgeLanes(std::string edgeId);
    bool getEdgeIsInternal(std::string edgeId);
};

#endif /* SUMONETWORK_H_ */
