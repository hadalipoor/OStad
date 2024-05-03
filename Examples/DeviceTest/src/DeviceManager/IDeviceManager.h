
#ifndef IDEVICEMANAGER_H
#define IDEVICEMANAGER_H

#include <EBPInterfaces.h>

class IDeviceManager
{
public:
    virtual ~IDeviceManager(){}

    virtual void initialize() = 0;
    virtual void update() = 0;

};

#endif
