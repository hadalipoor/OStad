
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

    Button* _remote1Button;
    String _remote1ButtonStr = "remote1Button";
    Button* _remote2Button;
    String _remote2ButtonStr = "remote2Button";
    Button* _remote3Button;
    String _remote3ButtonStr = "remote3Button";
    Button* _remote4Button;
    String _remote4ButtonStr = "remote4Button";

    String _lightRelayStr = "lightRelay";
    Relay* _gardenRelay;

    String _gazebo1lightRelayStr = "gazebo1lightRelay";
    Relay* _gazebo1lightRelay;

    String _gazebo2lightRelayStr = "gazebo2lightRelay";
    Relay* _gazebo2lightRelay;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    Relay* gardenRelay() override;
    Relay* gazebo1lightRelay() override;
    Relay* gazebo2lightRelay() override;
    Button* remote1Button() override;
    Button* remote2Button() override;
    Button* remote3Button() override;
    Button* remote4Button() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _gardenRelay = new Relay(26, "lightRelay", false);
    _gazebo1lightRelay = new Relay(27, "gazebo1lightRelay", false);
    _gazebo2lightRelay = new Relay(25, "gazebo2lightRelay", false);
    _remote1Button = new Button(13, "remote1Button", false, false, ButtonType::PIN);
    _remote2Button = new Button(12, "remote2Button", false, false, ButtonType::PIN);
    _remote3Button = new Button(14, "remote3Button", false, false, ButtonType::PIN);
    // _remote4Button = new Button(1, "remote3Button", false, false, ButtonType::PIN);

}

void DeviceManager::update()
{
    _resetButton->update();
    _gardenRelay->update();
    _gazebo1lightRelay->update();
    _gazebo2lightRelay->update();
    _remote1Button->update();
    _remote2Button->update();
    _remote3Button->update();
}

Button* DeviceManager::resetButton()
{
    return _resetButton;
}

Relay* DeviceManager::gardenRelay()
{
    return _gardenRelay;
}

Relay* DeviceManager::gazebo1lightRelay()
{
    return _gazebo1lightRelay;
}

Relay* DeviceManager::gazebo2lightRelay()
{
    return _gazebo2lightRelay;
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

Button* DeviceManager::remote4Button()
{
    return _remote4Button;
}


#endif
