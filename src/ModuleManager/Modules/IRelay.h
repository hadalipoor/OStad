#ifndef IRELAY_H
#define IRELAY_H

#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/RelayFullEntity.h"
#include "BaseModule.h"

class IRelay: public BaseModule
{

public:
    IRelay(int module_id, int server_id, String name, String moduleType, int device_id): BaseModule(module_id, server_id, name, moduleType, device_id){}

    virtual bool getNormallyOpen() = 0;
    virtual void setNormallyOpen(bool normallyOpen) = 0;
    virtual int getPinNumber() = 0;
    virtual void setPinNumber(int pinNumber) = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool getState() = 0;
    virtual void update() = 0;
    virtual void turnOnAfterDelay(unsigned long delay_millis) = 0;
    virtual void turnOffAfterDelay(unsigned long delay_millis) = 0;
    virtual void turnOnForDelay(unsigned long delay_millis) = 0;
    virtual void turnOffForDelay(unsigned long delay_millis) = 0;
    virtual RelayFullEntity* getEntity() = 0;

};

#endif
