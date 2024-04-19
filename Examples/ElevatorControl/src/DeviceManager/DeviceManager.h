
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

    String _EMSButtonStr = "EMSButton";
    Button* _EMSButton;

    String _floorSensor1Str = "floorSensor1";
    Button* _floorSensor1;

    String _floorSensor2Str = "floorSensor2";
    Button* _floorSensor2;

    String _floorSensor3Str = "floorSensor3";
    Button* _floorSensor3;

    String _floorSensor4Str = "floorSensor4";
    Button* _floorSensor4;

    String _mainLCDStr = "mainLCD";
    OLEDLCD* _mainLCD;

    String _upRelayStr = "upRelay";
    Relay* _upRelay;

    String _downRelayStr = "downRelay";
    Relay* _downRelay;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    Button* EMSButton() override;
    Button* floorSensor1() override;
    Button* floorSensor2() override;
    Button* floorSensor3() override;
    Button* floorSensor4() override;
    OLEDLCD* mainLCD() override;
    Relay* upRelay() override;
    Relay* downRelay() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _EMSButton = new Button(1, "EMSButton", true, false, ButtonType::PIN);
    _floorSensor1 = new Button(2, "floorSensor1", true, true, ButtonType::PIN);
    _floorSensor2 = new Button(2, "floorSensor2", true, true, ButtonType::PIN);
    _floorSensor3 = new Button(2, "floorSensor3", true, true, ButtonType::PIN);
    _floorSensor4 = new Button(2, "floorSensor4", true, true, ButtonType::PIN);
    _mainLCD = new OLEDLCD("mainLCD", 0x3C, 128, 64);
    _upRelay = new Relay(4, "upRelay", true);
    _downRelay = new Relay(5, "downRelay", true);
}

void DeviceManager::update()
{
    _resetButton->update();
    _EMSButton->update();
    _floorSensor1->update();
    _floorSensor2->update();
    _floorSensor3->update();
    _floorSensor4->update();
    _upRelay->update();
    _downRelay->update();
}

Button* DeviceManager::resetButton()
{
    return _resetButton;
}

Button* DeviceManager::EMSButton()
{
    return _EMSButton;
}

Button* DeviceManager::floorSensor1()
{
    return _floorSensor1;
}

Button* DeviceManager::floorSensor2()
{
    return _floorSensor2;
}

Button* DeviceManager::floorSensor3()
{
    return _floorSensor3;
}

Button* DeviceManager::floorSensor4()
{
    return _floorSensor4;
}

OLEDLCD* DeviceManager::mainLCD()
{
    return _mainLCD;
}

Relay* DeviceManager::upRelay()
{
    return _upRelay;
}

Relay* DeviceManager::downRelay()
{
    return _downRelay;
}



#endif
