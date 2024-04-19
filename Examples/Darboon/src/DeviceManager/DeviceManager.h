
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    Button* _resetButton;
    String _resetButtonStr = "resetButton";
    Button* _doorButton;
    String _doorButtonStr = "doorButton";
    Button* _remote1Button;
    String _remote1ButtonStr = "remote1Button";
    Button* _remote2Button;
    String _remote2ButtonStr = "remote2Button";
    Button* _remote3Button;
    String _remote3ButtonStr = "remote3Button";
    Relay* _doorRelay;
    String _doorRelayStr = "doorRelay";

    String _mainRFIDStr = "mainRFID";
    RFID125Kh* _mainRFID;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    Button* doorButton() override;
    Button* remote1Button() override;
    Button* remote2Button() override;
    Button* remote3Button() override;
    Relay* doorRelay() override;
    RFID125Kh* mainRFID() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _doorButton = new Button(0, "doorButton", false, false, ButtonType::PIN);
    _remote1Button = new Button(13, "remote1Button", false, false, ButtonType::PIN);
    _remote2Button = new Button(12, "remote2Button", false, false, ButtonType::PIN);
    _remote3Button = new Button(14, "remote3Button", false, false, ButtonType::PIN);
    _doorRelay = new Relay(33, "doorRelay", false);
    _mainRFID = new RFID125Kh("mainRFID", 26, 27);
}

void DeviceManager::update()
{
    _resetButton->update();
    _doorRelay->update();
    _mainRFID->update();
    _doorButton->update();
    _remote1Button->update();
    _remote2Button->update();
    _remote3Button->update();
}

Button* DeviceManager::resetButton()
{
    return _resetButton;
}

Button* DeviceManager::doorButton()
{
    return _doorButton;
}

Button* DeviceManager::remote1Button()
{
    return _remote1Button;
}

Button* DeviceManager::remote2Button()
{
    return _remote2Button;
}

Button* DeviceManager::remote3Button()
{
    return _remote3Button;
}

Relay* DeviceManager::doorRelay()
{
    return _doorRelay;
}

RFID125Kh* DeviceManager::mainRFID()
{
    return _mainRFID;
}



#endif
