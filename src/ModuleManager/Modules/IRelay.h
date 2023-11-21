#ifndef IRELAY_H
#define IRELAY_H

#include "../../Database/Entities/Modules/RelayFullEntity.h"
#include <Arduino.h>

class IRelay
{
public:
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
