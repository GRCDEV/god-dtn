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

#include "EpiBeaconsApp.h"
#include "EpiNeighbor.h"
#include "Epidemic_m.h"

Define_Module(EpiBeaconsApp);

EpiBeaconsApp::EpiBeaconsApp() {
    // TODO Auto-generated constructor stub

}

EpiBeaconsApp::~EpiBeaconsApp() {
    // TODO Auto-generated destructor stub
}

void EpiBeaconsApp::addExtraInfo(BeaconPkt *beacon)
{
    EpiInfo *epiInfo = new EpiInfo();
    epiInfo->setLastBufferUpdate(epiProtocol->getLastAddedFragment());
    epiInfo->setByteLength(sizeof(double));
    beacon->encapsulate(epiInfo);
}

Neighbor *EpiBeaconsApp::createNeighbor()
{
    return new EpiNeighbor();
}

void EpiBeaconsApp::readExtraInfo(BeaconPkt *beacon, Neighbor *neighbor, bool newNeigh)
{
    cPacket *info= beacon->decapsulate();
    if (dynamic_cast<EpiInfo *>(info) != NULL) {
        EpiInfo *epiInfo = check_and_cast<EpiInfo *>(info);
        EpiNeighbor *epi = dynamic_cast<EpiNeighbor*>(neighbor);
        ASSERT(epi != NULL);
        epi->setLastBufferUpdate(epiInfo->getLastBufferUpdate());
    }
    delete info;

}

void EpiBeaconsApp::initialize(int stage)
{
    BeaconsApp::initialize(stage);
    if(stage != 3){
        return;
    }
    epiProtocol = ModuleAccess<EpidemicProtocol>("dtnProtocol").get();
    ASSERT(epiProtocol != NULL);
}

bool EpiBeaconsApp::hasChanged(Neighbor *neighbor)
{
    EpiNeighbor *epi = dynamic_cast<EpiNeighbor*>(neighbor);
    EpiNeighbor *old = dynamic_cast<EpiNeighbor*>(neighborsList.at(neighbor->getId()));
    ASSERT(epi != NULL);
    ASSERT( neighborsList.find(neighbor->getId()) != neighborsList.end());
    return (epi->getLastBufferUpdate() != old->getLastBufferUpdate());
}



