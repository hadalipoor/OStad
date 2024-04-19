
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
    virtual Button* remote1Button() = 0;
    virtual Button* remote2Button() = 0;
    virtual Button* remote3Button() = 0;
    virtual Button* remote4Button() = 0;
    virtual Relay* gardenRelay() = 0;
    virtual Relay* gazebo1lightRelay() = 0;
    virtual Relay* gazebo2lightRelay() = 0;

};

#endif
