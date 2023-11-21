
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
    virtual Button* EMSButtonUp() = 0;
    virtual Button* EMSButtonDown() = 0;
    virtual Button* calibrationSensor() = 0;
    virtual Button* floorButtons(int index) = 0;
    virtual Button* floorButtonsRemote(int index) = 0;
    virtual Button* floorSensor1() = 0;
    virtual Button* floorSensor2() = 0;
    virtual Button* floorSensor3() = 0;
    virtual Button* floorSensor4() = 0;
    virtual Button* floorSensor5() = 0;

    virtual OLEDLCD* mainLCD() = 0;
    virtual Relay* upRelay() = 0;
    virtual Relay* downRelay() = 0;
    virtual SimCardManager* SimCard() = 0;
};

#endif
