
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
    virtual Button* EMSButton() = 0;
    virtual Button* floorSensor1() = 0;
    virtual Button* floorSensor2() = 0;
    virtual Button* floorSensor3() = 0;
    virtual Button* floorSensor4() = 0;
    virtual OLEDLCD* mainLCD() = 0;
    virtual Relay* upRelay() = 0;
    virtual Relay* downRelay() = 0;

};

#endif
