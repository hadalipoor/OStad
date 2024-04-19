
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
    virtual Button* doorButton() = 0;
    virtual Button* remote1Button() = 0;
    virtual Button* remote2Button() = 0;
    virtual Button* remote3Button() = 0;
    virtual Relay* doorRelay() = 0;
    virtual RFID125Kh* mainRFID() = 0;

};

#endif
