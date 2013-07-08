//
// Generated file, do not edit! Created by opp_msgc 4.3 from applications/dtn/DTNDataMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DTNDataMsg_m.h"

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




Register_Class(DTNDataMsg);

DTNDataMsg::DTNDataMsg(const char *name, int kind) : cPacket(name,kind)
{
    this->srcId_var = 0;
    this->dstId_var = 0;
    this->msgId_var = 0;
    fragments_arraysize = 0;
    this->fragments_var = 0;
}

DTNDataMsg::DTNDataMsg(const DTNDataMsg& other) : cPacket(other)
{
    fragments_arraysize = 0;
    this->fragments_var = 0;
    copy(other);
}

DTNDataMsg::~DTNDataMsg()
{
    delete [] fragments_var;
}

DTNDataMsg& DTNDataMsg::operator=(const DTNDataMsg& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void DTNDataMsg::copy(const DTNDataMsg& other)
{
    this->srcId_var = other.srcId_var;
    this->dstId_var = other.dstId_var;
    this->msgId_var = other.msgId_var;
    delete [] this->fragments_var;
    this->fragments_var = (other.fragments_arraysize==0) ? NULL : new DTNFragment[other.fragments_arraysize];
    fragments_arraysize = other.fragments_arraysize;
    for (unsigned int i=0; i<fragments_arraysize; i++)
        this->fragments_var[i] = other.fragments_var[i];
}

void DTNDataMsg::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->srcId_var);
    doPacking(b,this->dstId_var);
    doPacking(b,this->msgId_var);
    b->pack(fragments_arraysize);
    doPacking(b,this->fragments_var,fragments_arraysize);
}

void DTNDataMsg::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcId_var);
    doUnpacking(b,this->dstId_var);
    doUnpacking(b,this->msgId_var);
    delete [] this->fragments_var;
    b->unpack(fragments_arraysize);
    if (fragments_arraysize==0) {
        this->fragments_var = 0;
    } else {
        this->fragments_var = new DTNFragment[fragments_arraysize];
        doUnpacking(b,this->fragments_var,fragments_arraysize);
    }
}

uint64 DTNDataMsg::getSrcId() const
{
    return srcId_var;
}

void DTNDataMsg::setSrcId(uint64 srcId)
{
    this->srcId_var = srcId;
}

uint64 DTNDataMsg::getDstId() const
{
    return dstId_var;
}

void DTNDataMsg::setDstId(uint64 dstId)
{
    this->dstId_var = dstId;
}

uint32 DTNDataMsg::getMsgId() const
{
    return msgId_var;
}

void DTNDataMsg::setMsgId(uint32 msgId)
{
    this->msgId_var = msgId;
}

void DTNDataMsg::setFragmentsArraySize(unsigned int size)
{
    DTNFragment *fragments_var2 = (size==0) ? NULL : new DTNFragment[size];
    unsigned int sz = fragments_arraysize < size ? fragments_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        fragments_var2[i] = this->fragments_var[i];
    fragments_arraysize = size;
    delete [] this->fragments_var;
    this->fragments_var = fragments_var2;
}

unsigned int DTNDataMsg::getFragmentsArraySize() const
{
    return fragments_arraysize;
}

DTNFragment& DTNDataMsg::getFragments(unsigned int k)
{
    if (k>=fragments_arraysize) throw cRuntimeError("Array of size %d indexed by %d", fragments_arraysize, k);
    return fragments_var[k];
}

void DTNDataMsg::setFragments(unsigned int k, const DTNFragment& fragments)
{
    if (k>=fragments_arraysize) throw cRuntimeError("Array of size %d indexed by %d", fragments_arraysize, k);
    this->fragments_var[k] = fragments;
}

class DTNDataMsgDescriptor : public cClassDescriptor
{
  public:
    DTNDataMsgDescriptor();
    virtual ~DTNDataMsgDescriptor();

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

Register_ClassDescriptor(DTNDataMsgDescriptor);

DTNDataMsgDescriptor::DTNDataMsgDescriptor() : cClassDescriptor("DTNDataMsg", "cPacket")
{
}

DTNDataMsgDescriptor::~DTNDataMsgDescriptor()
{
}

bool DTNDataMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DTNDataMsg *>(obj)!=NULL;
}

const char *DTNDataMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DTNDataMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int DTNDataMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *DTNDataMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcId",
        "dstId",
        "msgId",
        "fragments",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DTNDataMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstId")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "fragments")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DTNDataMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint64",
        "uint64",
        "uint32",
        "DTNFragment",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *DTNDataMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DTNDataMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataMsg *pp = (DTNDataMsg *)object; (void)pp;
    switch (field) {
        case 3: return pp->getFragmentsArraySize();
        default: return 0;
    }
}

std::string DTNDataMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataMsg *pp = (DTNDataMsg *)object; (void)pp;
    switch (field) {
        case 0: return uint642string(pp->getSrcId());
        case 1: return uint642string(pp->getDstId());
        case 2: return ulong2string(pp->getMsgId());
        case 3: {std::stringstream out; out << pp->getFragments(i); return out.str();}
        default: return "";
    }
}

bool DTNDataMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataMsg *pp = (DTNDataMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcId(string2uint64(value)); return true;
        case 1: pp->setDstId(string2uint64(value)); return true;
        case 2: pp->setMsgId(string2ulong(value)); return true;
        default: return false;
    }
}

const char *DTNDataMsgDescriptor::getFieldStructName(void *object, int field) const
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
        "DTNFragment",
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *DTNDataMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataMsg *pp = (DTNDataMsg *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getFragments(i)); break;
        default: return NULL;
    }
}

Register_Class(DTNDataAck);

DTNDataAck::DTNDataAck(const char *name, int kind) : cPacket(name,kind)
{
    this->srcId_var = 0;
    this->dstId_var = 0;
    this->msgId_var = 0;
}

DTNDataAck::DTNDataAck(const DTNDataAck& other) : cPacket(other)
{
    copy(other);
}

DTNDataAck::~DTNDataAck()
{
}

DTNDataAck& DTNDataAck::operator=(const DTNDataAck& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void DTNDataAck::copy(const DTNDataAck& other)
{
    this->srcId_var = other.srcId_var;
    this->dstId_var = other.dstId_var;
    this->msgId_var = other.msgId_var;
}

void DTNDataAck::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->srcId_var);
    doPacking(b,this->dstId_var);
    doPacking(b,this->msgId_var);
}

void DTNDataAck::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcId_var);
    doUnpacking(b,this->dstId_var);
    doUnpacking(b,this->msgId_var);
}

uint64 DTNDataAck::getSrcId() const
{
    return srcId_var;
}

void DTNDataAck::setSrcId(uint64 srcId)
{
    this->srcId_var = srcId;
}

uint64 DTNDataAck::getDstId() const
{
    return dstId_var;
}

void DTNDataAck::setDstId(uint64 dstId)
{
    this->dstId_var = dstId;
}

uint32 DTNDataAck::getMsgId() const
{
    return msgId_var;
}

void DTNDataAck::setMsgId(uint32 msgId)
{
    this->msgId_var = msgId;
}

class DTNDataAckDescriptor : public cClassDescriptor
{
  public:
    DTNDataAckDescriptor();
    virtual ~DTNDataAckDescriptor();

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

Register_ClassDescriptor(DTNDataAckDescriptor);

DTNDataAckDescriptor::DTNDataAckDescriptor() : cClassDescriptor("DTNDataAck", "cPacket")
{
}

DTNDataAckDescriptor::~DTNDataAckDescriptor()
{
}

bool DTNDataAckDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DTNDataAck *>(obj)!=NULL;
}

const char *DTNDataAckDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DTNDataAckDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DTNDataAckDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DTNDataAckDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcId",
        "dstId",
        "msgId",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DTNDataAckDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstId")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DTNDataAckDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint64",
        "uint64",
        "uint32",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DTNDataAckDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DTNDataAckDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataAck *pp = (DTNDataAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DTNDataAckDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataAck *pp = (DTNDataAck *)object; (void)pp;
    switch (field) {
        case 0: return uint642string(pp->getSrcId());
        case 1: return uint642string(pp->getDstId());
        case 2: return ulong2string(pp->getMsgId());
        default: return "";
    }
}

bool DTNDataAckDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataAck *pp = (DTNDataAck *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcId(string2uint64(value)); return true;
        case 1: pp->setDstId(string2uint64(value)); return true;
        case 2: pp->setMsgId(string2ulong(value)); return true;
        default: return false;
    }
}

const char *DTNDataAckDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DTNDataAckDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DTNDataAck *pp = (DTNDataAck *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


