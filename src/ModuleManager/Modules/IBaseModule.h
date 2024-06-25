#ifndef IBASEMODULE_H
#define IBASEMODULE_H

#include "ModuleTypes.h"

class IBaseModule
{
public:
    // Constructor
    virtual int getModuleID() = 0;
    virtual void setModuleID(int module_id) = 0;
    virtual int getServerId() = 0;
    virtual void setServerId(int id) = 0;
    virtual String getName() = 0;
    virtual void setName(String name) = 0;
    virtual String getModuleType() = 0;
    virtual void setModuleType(String moduleType) = 0;
    virtual int getDeviceID() = 0;
    virtual void setDeviceID(int device_id) = 0;
};

#endif // IBASEMODULE_H
