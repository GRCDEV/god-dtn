//
// Generated file, do not edit! Created by opp_msgc 4.3 from applications/beacons/BeaconPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BeaconPkt_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("NodeType");
    if (!e) enums.getInstance()->add(e = new cEnum("NodeType"));
    e->insert(Car, "Car");
    e->insert(Sink, "Sink");
);

Register_Class(BeaconPkt);

BeaconPkt::BeaconPkt(const char *name, int kind) : cPacket(name,kind)
{
    this->msgId_var = 0;
    this->srcId_var = 0;
    this->serviceIp_var = 0;
    this->nodeType_var = 0;
    this->lat_var = 0;
    this->lon_var = 0;
    this->speed_var = 0;
    this->bearing_var = 0;
}

BeaconPkt::BeaconPkt(const BeaconPkt& other) : cPacket(other)
{
    copy(other);
}

BeaconPkt::~BeaconPkt()
{
}

BeaconPkt& BeaconPkt::operator=(const BeaconPkt& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void BeaconPkt::copy(const BeaconPkt& other)
{
    this->msgId_var = other.msgId_var;
    this->srcId_var = other.srcId_var;
    this->serviceIp_var = other.serviceIp_var;
    this->nodeType_var = other.nodeType_var;
    this->lat_var = other.lat_var;
    this->lon_var = other.lon_var;
    this->speed_var = other.speed_var;
    this->bearing_var = other.bearing_var;
}

void BeaconPkt::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->msgId_var);
    doPacking(b,this->srcId_var);
    doPacking(b,this->serviceIp_var);
    doPacking(b,this->nodeType_var);
    doPacking(b,this->lat_var);
    doPacking(b,this->lon_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->bearing_var);
}

void BeaconPkt::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->msgId_var);
    doUnpacking(b,this->srcId_var);
    doUnpacking(b,this->serviceIp_var);
    doUnpacking(b,this->nodeType_var);
    doUnpacking(b,this->lat_var);
    doUnpacking(b,this->lon_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->bearing_var);
}

uint32 BeaconPkt::getMsgId() const
{
    return msgId_var;
}

void BeaconPkt::setMsgId(uint32 msgId)
{
    this->msgId_var = msgId;
}

uint64 BeaconPkt::getSrcId() const
{
    return srcId_var;
}

void BeaconPkt::setSrcId(uint64 srcId)
{
    this->srcId_var = srcId;
}

uint32 BeaconPkt::getServiceIp() const
{
    return serviceIp_var;
}

void BeaconPkt::setServiceIp(uint32 serviceIp)
{
    this->serviceIp_var = serviceIp;
}

int BeaconPkt::getNodeType() const
{
    return nodeType_var;
}

void BeaconPkt::setNodeType(int nodeType)
{
    this->nodeType_var = nodeType;
}

double BeaconPkt::getLat() const
{
    return lat_var;
}

void BeaconPkt::setLat(double lat)
{
    this->lat_var = lat;
}

double BeaconPkt::getLon() const
{
    return lon_var;
}

void BeaconPkt::setLon(double lon)
{
    this->lon_var = lon;
}

double BeaconPkt::getSpeed() const
{
    return speed_var;
}

void BeaconPkt::setSpeed(double speed)
{
    this->speed_var = speed;
}

double BeaconPkt::getBearing() const
{
    return bearing_var;
}

void BeaconPkt::setBearing(double bearing)
{
    this->bearing_var = bearing;
}

class BeaconPktDescriptor : public cClassDescriptor
{
  public:
    BeaconPktDescriptor();
    virtual ~BeaconPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BeaconPktDescriptor);

BeaconPktDescriptor::BeaconPktDescriptor() : cClassDescriptor("BeaconPkt", "cPacket")
{
}

BeaconPktDescriptor::~BeaconPktDescriptor()
{
}

bool BeaconPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BeaconPkt *>(obj)!=NULL;
}

const char *BeaconPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BeaconPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int BeaconPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *BeaconPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msgId",
        "srcId",
        "serviceIp",
        "nodeType",
        "lat",
        "lon",
        "speed",
        "bearing",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int BeaconPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "serviceIp")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeType")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "lat")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "lon")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+6;
    if (fieldName[0]=='b' && strcmp(fieldName, "bearing")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BeaconPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32",
        "uint64",
        "uint32",
        "int",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *BeaconPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3:
            if (!strcmp(propertyname,"enum")) return "NodeType";
            return NULL;
        default: return NULL;
    }
}

int BeaconPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BeaconPkt *pp = (BeaconPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BeaconPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BeaconPkt *pp = (BeaconPkt *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getMsgId());
        case 1: return uint642string(pp->getSrcId());
        case 2: return ulong2string(pp->getServiceIp());
        case 3: return long2string(pp->getNodeType());
        case 4: return double2string(pp->getLat());
        case 5: return double2string(pp->getLon());
        case 6: return double2string(pp->getSpeed());
        case 7: return double2string(pp->getBearing());
        default: return "";
    }
}

bool BeaconPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BeaconPkt *pp = (BeaconPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsgId(string2ulong(value)); return true;
        case 1: pp->setSrcId(string2uint64(value)); return true;
        case 2: pp->setServiceIp(string2ulong(value)); return true;
        case 3: pp->setNodeType(string2long(value)); return true;
        case 4: pp->setLat(string2double(value)); return true;
        case 5: pp->setLon(string2double(value)); return true;
        case 6: pp->setSpeed(string2double(value)); return true;
        case 7: pp->setBearing(string2double(value)); return true;
        default: return false;
    }
}

const char *BeaconPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *BeaconPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BeaconPkt *pp = (BeaconPkt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


