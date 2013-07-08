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

#include "SumoNetwork.h"
#include "TraCIScenarioManager.h"

// All the Coord objects in this module refer to TraCI coordinates.

Define_Module(SumoNetwork);

SumoNetwork::SumoNetwork() {
    // TODO Auto-generated constructor stub

}

SumoNetwork::~SumoNetwork() {
    // TODO Auto-generated destructor stub
}

void SumoNetwork::initialize(int stage){
    if(stage!=2){
        return;
    }
    manager = dynamic_cast<TraCIScenarioManager *>(simulation.getModuleByPath("manager"));
    debug = par("debug").boolValue();
    cXMLElement* networkFile = par("networkConfig").xmlValue();

    std::string rootTag = networkFile->getTagName();
    ASSERT(rootTag == "net");

    cXMLElementList junctionList = networkFile->getElementsByTagName("junction");
    ASSERT(junctionList.size()!=0);
    for (cXMLElementList::const_iterator i = junctionList.begin(); i != junctionList.end(); ++i) {
           cXMLElement* e = *i;
           Junction junction;
           std::string id;
           double x;
           double y;

           ASSERT(e->getAttribute("id"));
           id = e->getAttribute("id");
           ASSERT(e->getAttribute("x"));
           x = atof(e->getAttribute("x"));
           ASSERT(e->getAttribute("y"));
           y = atof(e->getAttribute("y"));

           junction.id=id;
           junction.position = TraCIScenarioManager::TraCICoord(x,y);


           addJunction(junction);
    }

    cXMLElementList edgeList = networkFile->getElementsByTagName("edge");
    ASSERT(edgeList.size()!=0);
    for (cXMLElementList::const_iterator i = edgeList.begin(); i != edgeList.end(); ++i) {
           cXMLElement* e = *i;
           Edge edge;
           std::vector<TraCIScenarioManager::TraCICoord> shape;
           std::string id;
           Junction* from;
           Junction* to;
           double length;
           bool internal=false;
           cXMLElementList laneList = e->getChildrenByTagName("lane");
           ASSERT(laneList.size()!=0);

           for(cXMLElementList::iterator j = laneList.begin(); j!= laneList.end(); j++){
               edge.laneList.push_back((*j)->getAttribute("id"));
           }



           ASSERT(e->getAttribute("id"));
           id = e->getAttribute("id");
           if(e->getAttribute("function")){
               std::string function =  e->getAttribute("function");
               if(function == "internal")
               {
                   edge.internal = true;
                   edge.id=id;
                   addEdge(edge);
                   continue;
               }
           }
           ASSERT(e->getAttribute("from"));
           std::string fromId = e->getAttribute("from");
           ASSERT(junctionMap.find(fromId)!=junctionMap.end());
           from = &(junctionMap[fromId]);
           ASSERT(e->getAttribute("to"));
           std::string toId = e->getAttribute("to");
           ASSERT(junctionMap.find(toId)!=junctionMap.end());
           to = &(junctionMap[toId]);

           if(e->getAttribute("shape")){
               shape = String2Shape(e->getAttribute("shape"));
           }
           else{
               cXMLElement* l = e->getFirstChildWithTag("lane");
               ASSERT(l->getAttribute("shape"));
               shape= String2Shape(l->getAttribute("shape"));
           }

           length = 0;

           for(uint i=0; i< shape.size()-1; i++){
               length += Coord(shape.at(i).x,shape.at(i).y).distance(Coord(shape.at(i+1).x,shape.at(i+1).y));
           }

           double maxSpeed = 0;

           if(e->getAttribute("speed")){
                maxSpeed = atof( e->getAttribute("speed") );
           }
           else{
               for (cXMLElementList::const_iterator j = laneList.begin(); j != laneList.end(); ++j) {
                   cXMLElement* l = *j;
                   ASSERT( l->getAttribute("speed") );
                   double speed = atof( l->getAttribute("speed") );

                   if( speed > maxSpeed ){
                       maxSpeed = speed;
                   }
               }
           }

           edge.from = from;
           edge.to = to;
           edge.length = length;
           edge.id = id;
           edge.maxSpeed = maxSpeed;
           edge.shape = shape;
           edge.internal = internal;
           ASSERT(edge.from != NULL && edge.to != NULL);
           addEdge(edge);
    }

     if(debug){
         EV << "Found " << this->junctionList.size() << " Junctions" << endl;
         EV << "Found " << this->edgeList.size() << " Edges" << endl;
     }
}

void SumoNetwork::finish(){
}

void SumoNetwork::addJunction(Junction junc){
    junctionMap[junc.id]=junc;
    junctionList.push_back(junc.id);
}

void SumoNetwork::addEdge(Edge edge){
    edgeMap[edge.id]=edge;
    edgeList.push_back(edge.id);
}

const std::list<std::string> SumoNetwork::getJunctionIds(){
    return junctionList;
}

TraCIScenarioManager::TraCICoord SumoNetwork::getJunctionPosition(std::string junctionId){
    ASSERT(junctionMap.find(junctionId)!=junctionMap.end());
    return junctionMap[junctionId].position;
}

const std::list<std::string> SumoNetwork::getEdgeIds(){
    return edgeList;
}

const TraCIScenarioManager::TraCICoord SumoNetwork::getEdgeFrom(std::string edgeId){
    ASSERT(edgeMap.find(edgeId)!=edgeMap.end());
    return edgeMap[edgeId].from->position;
}

const TraCIScenarioManager::TraCICoord SumoNetwork::getEdgeTo(std::string edgeId){
    ASSERT(edgeMap.find(edgeId)!=edgeMap.end());
    return edgeMap[edgeId].to->position;
}

double SumoNetwork::getEdgeLength(std::string edgeId){
    ASSERT(edgeMap.find(edgeId)!=edgeMap.end());
    return edgeMap[edgeId].length;
}

double SumoNetwork::getEdgeMaxSpeed(std::string edgeId){
    ASSERT(edgeMap.find(edgeId)!=edgeMap.end());
    return edgeMap[edgeId].maxSpeed;
}

/*
   * Converts a string with the format "X1,Y1 X2,Y2 X3,Y3 [···] Xn,Yn"
   * into a vector of Coord
   */
std::vector<TraCIScenarioManager::TraCICoord> SumoNetwork::String2Shape(const std::string &str)
  {
    std::vector<TraCIScenarioManager::TraCICoord> shape;
    int next=0;
    int pos;
    std::string str2;
    do
    {
      pos=str.find_first_of(' ',next);
      str2=str.substr(next,pos-next);
      next=pos+1;
      shape.push_back(String2Coord(str2));
    }while(pos!=-1);
    return shape;
  }

/*
 * Converts a string with the format  XX,YY into a Coord
 */
TraCIScenarioManager::TraCICoord SumoNetwork::String2Coord(const std::string &str)
{
  int pos=str.find_first_of(",",0);
  std::string x=str.substr(0,pos);
  std::string y=str.substr(pos+1, str.size()-(pos+1));
  TraCIScenarioManager::TraCICoord point;
  point.x=atof(x.c_str());
  point.y=atof(y.c_str());
  return point;
}

std::vector<TraCIScenarioManager::TraCICoord> SumoNetwork::getEdgeShape(std::string edgeId)
{
    ASSERT(edgeMap.find(edgeId) != edgeMap.end());
    return edgeMap[edgeId].shape;
}

std::list<std::string> SumoNetwork::getEdgeLanes(std::string edgeId)
{
    ASSERT(edgeMap.find(edgeId) != edgeMap.end());
    return edgeMap[edgeId].laneList;
}

bool SumoNetwork::getEdgeIsInternal(std::string edgeId)
{
    ASSERT(edgeMap.find(edgeId) != edgeMap.end());
    return edgeMap.at(edgeId).internal;
}






