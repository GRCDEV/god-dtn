//
// Generated file, do not edit! Created by opp_msgc 4.3 from applications/dtn/epidemic/Epidemic.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Epidemic_m.h"

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
    cEnum *e = cEnum::find("EpidemicType");
    if (!e) enums.getInstance()->add(e = new cEnum("EpidemicType"));
    e->insert(PKT_OFFER, "PKT_OFFER");
    e->insert(PKT_REQUEST, "PKT_REQUEST");
);

Register_Class(EpidemicPkt);

EpidemicPkt::EpidemicPkt(const char *name, int kind) : cPacket(name,kind)
{
    this->srcId_var = 0;
    this->dstId_var = 0;
    this->type_var = 0;
}

EpidemicPkt::EpidemicPkt(const EpidemicPkt& other) : cPacket(other)
{
    copy(other);
}

EpidemicPkt::~EpidemicPkt()
{
}

EpidemicPkt& EpidemicPkt::operator=(const EpidemicPkt& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void EpidemicPkt::copy(const EpidemicPkt& other)
{
    this->srcId_var = other.srcId_var;
    this->dstId_var = other.dstId_var;
    this->type_var = other.type_var;
}

void EpidemicPkt::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->srcId_var);
    doPacking(b,this->dstId_var);
    doPacking(b,this->type_var);
}

void EpidemicPkt::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcId_var);
    doUnpacking(b,this->dstId_var);
    doUnpacking(b,this->type_var);
}

uint64 EpidemicPkt::getSrcId() const
{
    return srcId_var;
}

void EpidemicPkt::setSrcId(uint64 srcId)
{
    this->srcId_var = srcId;
}

uint64 EpidemicPkt::getDstId() const
{
    return dstId_var;
}

void EpidemicPkt::setDstId(uint64 dstId)
{
    this->dstId_var = dstId;
}

uint8 EpidemicPkt::getType() const
{
    return type_var;
}

void EpidemicPkt::setType(uint8 type)
{
    this->type_var = type;
}

class EpidemicPktDescriptor : public cClassDescriptor
{
  public:
    EpidemicPktDescriptor();
    virtual ~EpidemicPktDescriptor();

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

Register_ClassDescriptor(EpidemicPktDescriptor);

EpidemicPktDescriptor::EpidemicPktDescriptor() : cClassDescriptor("EpidemicPkt", "cPacket")
{
}

EpidemicPktDescriptor::~EpidemicPktDescriptor()
{
}

bool EpidemicPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EpidemicPkt *>(obj)!=NULL;
}

const char *EpidemicPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EpidemicPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int EpidemicPktDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *EpidemicPktDescriptor::getFieldName(void *object, int field) const
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
        "type",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int EpidemicPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstId")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EpidemicPktDescriptor::getFieldTypeString(void *object, int field) const
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
        "uint8",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *EpidemicPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int EpidemicPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPkt *pp = (EpidemicPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string EpidemicPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPkt *pp = (EpidemicPkt *)object; (void)pp;
    switch (field) {
        case 0: return uint642string(pp->getSrcId());
        case 1: return uint642string(pp->getDstId());
        case 2: return ulong2string(pp->getType());
        default: return "";
    }
}

bool EpidemicPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPkt *pp = (EpidemicPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcId(string2uint64(value)); return true;
        case 1: pp->setDstId(string2uint64(value)); return true;
        case 2: pp->setType(string2ulong(value)); return true;
        default: return false;
    }
}

const char *EpidemicPktDescriptor::getFieldStructName(void *object, int field) const
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

void *EpidemicPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPkt *pp = (EpidemicPkt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(EpidemicPktOffer);

EpidemicPktOffer::EpidemicPktOffer(const char *name, int kind) : EpidemicPkt(name,kind)
{
    this->setType(PKT_OFFER);

    offer_arraysize = 0;
    this->offer_var = 0;
}

EpidemicPktOffer::EpidemicPktOffer(const EpidemicPktOffer& other) : EpidemicPkt(other)
{
    offer_arraysize = 0;
    this->offer_var = 0;
    copy(other);
}

EpidemicPktOffer::~EpidemicPktOffer()
{
    delete [] offer_var;
}

EpidemicPktOffer& EpidemicPktOffer::operator=(const EpidemicPktOffer& other)
{
    if (this==&other) return *this;
    EpidemicPkt::operator=(other);
    copy(other);
    return *this;
}

void EpidemicPktOffer::copy(const EpidemicPktOffer& other)
{
    delete [] this->offer_var;
    this->offer_var = (other.offer_arraysize==0) ? NULL : new DTNUnique[other.offer_arraysize];
    offer_arraysize = other.offer_arraysize;
    for (unsigned int i=0; i<offer_arraysize; i++)
        this->offer_var[i] = other.offer_var[i];
}

void EpidemicPktOffer::parsimPack(cCommBuffer *b)
{
    EpidemicPkt::parsimPack(b);
    b->pack(offer_arraysize);
    doPacking(b,this->offer_var,offer_arraysize);
}

void EpidemicPktOffer::parsimUnpack(cCommBuffer *b)
{
    EpidemicPkt::parsimUnpack(b);
    delete [] this->offer_var;
    b->unpack(offer_arraysize);
    if (offer_arraysize==0) {
        this->offer_var = 0;
    } else {
        this->offer_var = new DTNUnique[offer_arraysize];
        doUnpacking(b,this->offer_var,offer_arraysize);
    }
}

void EpidemicPktOffer::setOfferArraySize(unsigned int size)
{
    DTNUnique *offer_var2 = (size==0) ? NULL : new DTNUnique[size];
    unsigned int sz = offer_arraysize < size ? offer_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        offer_var2[i] = this->offer_var[i];
    offer_arraysize = size;
    delete [] this->offer_var;
    this->offer_var = offer_var2;
}

unsigned int EpidemicPktOffer::getOfferArraySize() const
{
    return offer_arraysize;
}

DTNUnique& EpidemicPktOffer::getOffer(unsigned int k)
{
    if (k>=offer_arraysize) throw cRuntimeError("Array of size %d indexed by %d", offer_arraysize, k);
    return offer_var[k];
}

void EpidemicPktOffer::setOffer(unsigned int k, const DTNUnique& offer)
{
    if (k>=offer_arraysize) throw cRuntimeError("Array of size %d indexed by %d", offer_arraysize, k);
    this->offer_var[k] = offer;
}

class EpidemicPktOfferDescriptor : public cClassDescriptor
{
  public:
    EpidemicPktOfferDescriptor();
    virtual ~EpidemicPktOfferDescriptor();

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

Register_ClassDescriptor(EpidemicPktOfferDescriptor);

EpidemicPktOfferDescriptor::EpidemicPktOfferDescriptor() : cClassDescriptor("EpidemicPktOffer", "EpidemicPkt")
{
}

EpidemicPktOfferDescriptor::~EpidemicPktOfferDescriptor()
{
}

bool EpidemicPktOfferDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EpidemicPktOffer *>(obj)!=NULL;
}

const char *EpidemicPktOfferDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EpidemicPktOfferDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int EpidemicPktOfferDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EpidemicPktOfferDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "offer",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int EpidemicPktOfferDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "offer")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EpidemicPktOfferDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "DTNUnique",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *EpidemicPktOfferDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int EpidemicPktOfferDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktOffer *pp = (EpidemicPktOffer *)object; (void)pp;
    switch (field) {
        case 0: return pp->getOfferArraySize();
        default: return 0;
    }
}

std::string EpidemicPktOfferDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktOffer *pp = (EpidemicPktOffer *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getOffer(i); return out.str();}
        default: return "";
    }
}

bool EpidemicPktOfferDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktOffer *pp = (EpidemicPktOffer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EpidemicPktOfferDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "DTNUnique",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *EpidemicPktOfferDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktOffer *pp = (EpidemicPktOffer *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getOffer(i)); break;
        default: return NULL;
    }
}

Register_Class(EpidemicPktAsk);

EpidemicPktAsk::EpidemicPktAsk(const char *name, int kind) : EpidemicPkt(name,kind)
{
    this->setType(PKT_REQUEST);

    ask_arraysize = 0;
    this->ask_var = 0;
}

EpidemicPktAsk::EpidemicPktAsk(const EpidemicPktAsk& other) : EpidemicPkt(other)
{
    ask_arraysize = 0;
    this->ask_var = 0;
    copy(other);
}

EpidemicPktAsk::~EpidemicPktAsk()
{
    delete [] ask_var;
}

EpidemicPktAsk& EpidemicPktAsk::operator=(const EpidemicPktAsk& other)
{
    if (this==&other) return *this;
    EpidemicPkt::operator=(other);
    copy(other);
    return *this;
}

void EpidemicPktAsk::copy(const EpidemicPktAsk& other)
{
    delete [] this->ask_var;
    this->ask_var = (other.ask_arraysize==0) ? NULL : new DTNUnique[other.ask_arraysize];
    ask_arraysize = other.ask_arraysize;
    for (unsigned int i=0; i<ask_arraysize; i++)
        this->ask_var[i] = other.ask_var[i];
}

void EpidemicPktAsk::parsimPack(cCommBuffer *b)
{
    EpidemicPkt::parsimPack(b);
    b->pack(ask_arraysize);
    doPacking(b,this->ask_var,ask_arraysize);
}

void EpidemicPktAsk::parsimUnpack(cCommBuffer *b)
{
    EpidemicPkt::parsimUnpack(b);
    delete [] this->ask_var;
    b->unpack(ask_arraysize);
    if (ask_arraysize==0) {
        this->ask_var = 0;
    } else {
        this->ask_var = new DTNUnique[ask_arraysize];
        doUnpacking(b,this->ask_var,ask_arraysize);
    }
}

void EpidemicPktAsk::setAskArraySize(unsigned int size)
{
    DTNUnique *ask_var2 = (size==0) ? NULL : new DTNUnique[size];
    unsigned int sz = ask_arraysize < size ? ask_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ask_var2[i] = this->ask_var[i];
    ask_arraysize = size;
    delete [] this->ask_var;
    this->ask_var = ask_var2;
}

unsigned int EpidemicPktAsk::getAskArraySize() const
{
    return ask_arraysize;
}

DTNUnique& EpidemicPktAsk::getAsk(unsigned int k)
{
    if (k>=ask_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ask_arraysize, k);
    return ask_var[k];
}

void EpidemicPktAsk::setAsk(unsigned int k, const DTNUnique& ask)
{
    if (k>=ask_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ask_arraysize, k);
    this->ask_var[k] = ask;
}

class EpidemicPktAskDescriptor : public cClassDescriptor
{
  public:
    EpidemicPktAskDescriptor();
    virtual ~EpidemicPktAskDescriptor();

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

Register_ClassDescriptor(EpidemicPktAskDescriptor);

EpidemicPktAskDescriptor::EpidemicPktAskDescriptor() : cClassDescriptor("EpidemicPktAsk", "EpidemicPkt")
{
}

EpidemicPktAskDescriptor::~EpidemicPktAskDescriptor()
{
}

bool EpidemicPktAskDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EpidemicPktAsk *>(obj)!=NULL;
}

const char *EpidemicPktAskDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EpidemicPktAskDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int EpidemicPktAskDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EpidemicPktAskDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ask",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int EpidemicPktAskDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "ask")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EpidemicPktAskDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "DTNUnique",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *EpidemicPktAskDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int EpidemicPktAskDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktAsk *pp = (EpidemicPktAsk *)object; (void)pp;
    switch (field) {
        case 0: return pp->getAskArraySize();
        default: return 0;
    }
}

std::string EpidemicPktAskDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktAsk *pp = (EpidemicPktAsk *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getAsk(i); return out.str();}
        default: return "";
    }
}

bool EpidemicPktAskDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktAsk *pp = (EpidemicPktAsk *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EpidemicPktAskDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "DTNUnique",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *EpidemicPktAskDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EpidemicPktAsk *pp = (EpidemicPktAsk *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getAsk(i)); break;
        default: return NULL;
    }
}

Register_Class(EpiInfo);

EpiInfo::EpiInfo(const char *name, int kind) : cPacket(name,kind)
{
    this->lastBufferUpdate_var = 0;
}

EpiInfo::EpiInfo(const EpiInfo& other) : cPacket(other)
{
    copy(other);
}

EpiInfo::~EpiInfo()
{
}

EpiInfo& EpiInfo::operator=(const EpiInfo& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void EpiInfo::copy(const EpiInfo& other)
{
    this->lastBufferUpdate_var = other.lastBufferUpdate_var;
}

void EpiInfo::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->lastBufferUpdate_var);
}

void EpiInfo::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->lastBufferUpdate_var);
}

simtime_t EpiInfo::getLastBufferUpdate() const
{
    return lastBufferUpdate_var;
}

void EpiInfo::setLastBufferUpdate(simtime_t lastBufferUpdate)
{
    this->lastBufferUpdate_var = lastBufferUpdate;
}

class EpiInfoDescriptor : public cClassDescriptor
{
  public:
    EpiInfoDescriptor();
    virtual ~EpiInfoDescriptor();

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

Register_ClassDescriptor(EpiInfoDescriptor);

EpiInfoDescriptor::EpiInfoDescriptor() : cClassDescriptor("EpiInfo", "cPacket")
{
}

EpiInfoDescriptor::~EpiInfoDescriptor()
{
}

bool EpiInfoDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EpiInfo *>(obj)!=NULL;
}

const char *EpiInfoDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EpiInfoDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int EpiInfoDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EpiInfoDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "lastBufferUpdate",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int EpiInfoDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastBufferUpdate")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EpiInfoDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *EpiInfoDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int EpiInfoDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EpiInfo *pp = (EpiInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string EpiInfoDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EpiInfo *pp = (EpiInfo *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getLastBufferUpdate());
        default: return "";
    }
}

bool EpiInfoDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EpiInfo *pp = (EpiInfo *)object; (void)pp;
    switch (field) {
        case 0: pp->setLastBufferUpdate(string2double(value)); return true;
        default: return false;
    }
}

const char *EpiInfoDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *EpiInfoDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EpiInfo *pp = (EpiInfo *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


