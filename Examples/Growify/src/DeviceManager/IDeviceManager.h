
#ifndef IDEVICEMANAGER_H
#define IDEVICEMANAGER_H

#include <EBPInterfaces.h>

class IDeviceManager
{
public:
    virtual ~IDeviceManager(){}

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual Button* resetButton() = 0;
    virtual OLEDLCD* mainLCD() = 0;
    virtual Relay* pumpRelay() = 0;
    virtual SoilMoistureSensor* soilMoisture() = 0;

};

#endif
