
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    String _resetButtonStr = "resetButton";
    Button* _resetButton;

    String _doorRelayStr = "doorRelay";
    Relay* _doorRelay;

    String _mainRFIDStr = "mainRFID";
    RFID125Kh* _mainRFID;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    Relay* doorRelay() override;
    RFID125Kh* mainRFID() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _doorRelay = new Relay(26, "doorRelay", true);
    _mainRFID = new RFID125Kh("mainRFID", 26, 26);
}

void DeviceManager::update()
{
    _resetButton->update();
    _doorRelay->update();
    _mainRFID->update();
}

Button* DeviceManager::resetButton()
{
    return appContext->systemContext->getModules()->getButton("resetButton");
}

Relay* DeviceManager::doorRelay()
{
    return appContext->systemContext->getModules()->getRelay("doorRelay");
}

RFID125Kh* DeviceManager::mainRFID()
{
    return appContext->systemContext->getModules()->getRFID125Kh("mainRFID");
}



#endif
