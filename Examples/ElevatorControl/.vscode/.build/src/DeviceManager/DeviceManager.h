
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>
#include <PCF8574.h>
class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    String _resetButtonStr = "resetButton";
    Button* _resetButton;

    String _EMSButtonUPStr = "EMSButtonUp";
    Button* _EMSButtonUp;

    String _EMSButtonDownStr = "EMSButtonDown";
    Button* _EMSButtonDown;

    String _calibrationSensorStr = "calibrationSensor";
    Button* _calibrationSensor;

    String _floorSensor1Str = "floorSensor1";
    Button* _floorSensor1;

    String _floorSensor2Str = "floorSensor2";
    Button* _floorSensor2;

    String _floorSensor3Str = "floorSensor3";
    Button* _floorSensor3;

    String _floorSensor4Str = "floorSensor4";
    Button* _floorSensor4;

    String _floorSensor5Str = "floorSensor5";
    Button* _floorSensor5;


    String _mainLCDStr = "mainLCD";
    OLEDLCD* _mainLCD;

    String _upRelayStr = "upRelay";
    Relay* _upRelay;

    String _downRelayStr = "downRelay";
    Relay* _downRelay;

    std::vector<Button*> _floorButtonsRemote;
    std::vector<Button*> _floorButtons;

    SimCardManager* simCard;

    int floor_button_pins[5] = {4,3,2,1,0};
    int floor_button_remote_pins[4] = {36,39,34,35};

    String getFloorButtonName(int index);
public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    Button* EMSButtonUp() override;
    Button* EMSButtonDown() override;
    Button* calibrationSensor() override;
    Button* floorButtons(int index) override;
    Button* floorButtonsRemote(int index) override;
    Button* floorSensor1() override;
    Button* floorSensor2() override;
    Button* floorSensor3() override;
    Button* floorSensor4() override;
    Button* floorSensor5() override;
    OLEDLCD* mainLCD() override;
    Relay* upRelay() override;
    Relay* downRelay() override;
    SimCardManager* SimCard() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    // _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    PCF8574* pcf8574 = new PCF8574(0x21);

    _EMSButtonUp = new Button(27, _EMSButtonUPStr, false, false, ButtonType::PIN);
    _EMSButtonDown = new Button(12, _EMSButtonDownStr, false, false, ButtonType::PIN);
    _calibrationSensor = new Button(0, _calibrationSensorStr, true, false, ButtonType::PIN);
    
    //define modules
    _floorSensor1 = new Button(14, _floorSensor1Str, false, false, ButtonType::PIN);
    _floorSensor2 = new Button(13, _floorSensor2Str, false, false, ButtonType::PIN);
    _floorSensor3 = new Button(7, _floorSensor3Str, false, false, ButtonType::PCF8574, pcf8574);
    _floorSensor4 = new Button(6, _floorSensor4Str, false, false, ButtonType::PCF8574, pcf8574);
    _floorSensor5 = new Button(5, _floorSensor5Str, false, false, ButtonType::PCF8574, pcf8574);
    _mainLCD = new OLEDLCD(_mainLCDStr, 0x3C, 128, 64);
    _upRelay = new Relay(32, _upRelayStr, true);
    _downRelay = new Relay(25, _downRelayStr, true);    
    
    
    appContext->systemContext->getModules()->addButton(_EMSButtonUp);
    _EMSButtonUp = appContext->systemContext->getModules()->getButton(_EMSButtonUPStr, pcf8574);

    appContext->systemContext->getModules()->addButton(_EMSButtonDown);
    _EMSButtonDown = appContext->systemContext->getModules()->getButton(_EMSButtonDownStr, pcf8574);

    appContext->systemContext->getModules()->addButton(_calibrationSensor);
    _calibrationSensor = appContext->systemContext->getModules()->getButton(_calibrationSensorStr, pcf8574);

    appContext->systemContext->getModules()->addButton(_floorSensor1);
    _floorSensor1 = appContext->systemContext->getModules()->getButton(_floorSensor1Str, pcf8574);
    
    appContext->systemContext->getModules()->addButton(_floorSensor2);
    _floorSensor2 = appContext->systemContext->getModules()->getButton(_floorSensor2Str, pcf8574);
    
    appContext->systemContext->getModules()->addButton(_floorSensor3);
    // _floorSensor3 = appContext->systemContext->getModules()->getButton(_floorSensor3Str, pcf8574);
    
    appContext->systemContext->getModules()->addButton(_floorSensor4);
    // _floorSensor4 = appContext->systemContext->getModules()->getButton(_floorSensor4Str, pcf8574);
    
    appContext->systemContext->getModules()->addButton(_floorSensor5);
    // _floorSensor5 = appContext->systemContext->getModules()->getButton(_floorSensor5Str, pcf8574);
    
    appContext->systemContext->getModules()->addOLEDLCD(_mainLCD);
    _mainLCD = appContext->systemContext->getModules()->getOLEDLCD(_mainLCDStr);
    
    appContext->systemContext->getModules()->addRelay(_upRelay);
    _upRelay = appContext->systemContext->getModules()->getRelay(_upRelayStr);
    
    appContext->systemContext->getModules()->addRelay(_downRelay);
    _downRelay = appContext->systemContext->getModules()->getRelay(_downRelayStr);
    
    for (size_t i = 0; i < 4; i++)
    {
        Button* _floorButton = new Button(floor_button_remote_pins[i], getFloorButtonName(i)+ "_remote", false, false, ButtonType::PIN);
        appContext->systemContext->getModules()->addButton(_floorButton);
        // _floorButton = appContext->systemContext->getModules()->getButton(getFloorButtonName(i)+ "_remote", pcf8574);
        _floorButton->setDebounceDelay(0);
        _floorButton->setLongPressTime(0);
        _floorButtonsRemote.push_back(_floorButton);
    }

    for (size_t i = 0; i < 5; i++)
    {
        Button* _floorButton = new Button(floor_button_pins[i], getFloorButtonName(i), false, false, ButtonType::PCF8574, pcf8574);
        appContext->systemContext->getModules()->addButton(_floorButton);
        // _floorButton = appContext->systemContext->getModules()->getButton(getFloorButtonName(i), pcf8574);
        _floorButton->setDebounceDelay(0);
        _floorButton->setLongPressTime(0);
        _floorButtons.push_back(_floorButton);
    }

    //set settings for modules
    _EMSButtonDown->setDebounceDelay(0);
    _EMSButtonUp->setDebounceDelay(0);
    _calibrationSensor->setDebounceDelay(0);
    _calibrationSensor->setLongPressTime(0);
    _floorSensor1->setDebounceDelay(1);
    _floorSensor2->setDebounceDelay(1);
    _floorSensor3->setDebounceDelay(0);
    _floorSensor4->setDebounceDelay(0);
    _floorSensor5->setDebounceDelay(0);

    Serial.print("Init pcf8574->..");
    if (pcf8574->begin()){
        Serial.println("OK");
    }else{
        Serial.println("KO");
    }
    Serial.println("deviceM ends");
}

void DeviceManager::update()
{
    // _resetButton->update();
    _EMSButtonUp->update();
    _EMSButtonDown->update();
    _calibrationSensor->update();
    _floorSensor1->update();
    _floorSensor2->update();
    _floorSensor3->update();
    _floorSensor4->update();
    _floorSensor5->update();
    _upRelay->update();
    _downRelay->update();
    for (size_t i = 0; i < sizeof(floor_button_pins) / sizeof(floor_button_pins[0]); i++)
    {
        _floorButtons.at(i)->update();
    }
    for (size_t i = 0; i < 4; i++)
    {
        _floorButtonsRemote.at(i)->update();
    }
}

Button* DeviceManager::resetButton()
{
    return _resetButton;
}

Button* DeviceManager::EMSButtonUp()
{
    return _EMSButtonUp;
}

Button* DeviceManager::EMSButtonDown()
{
    return _EMSButtonDown;
}

Button* DeviceManager::calibrationSensor()
{
    return _calibrationSensor;
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

Button* DeviceManager::floorSensor5()
{
    return _floorSensor5;
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

String DeviceManager::getFloorButtonName(int index)
{
    return String(index + 1);
}

Button* DeviceManager::floorButtons(int index)
{
    return _floorButtons.at(index);
}

SimCardManager* DeviceManager::SimCard()
{
    return simCard;
}

Button* DeviceManager::floorButtonsRemote(int index)
{
    return _floorButtonsRemote.at(index);
}


#endif
