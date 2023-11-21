
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

    String _mainLCDStr = "mainLCD";
    OLEDLCD* _mainLCD;

    String _pumpRelayStr = "pumpRelay";
    Relay* _pumpRelay;

    String _soilMoistureStr = "soilMoisture";
    SoilMoistureSensor* _soilMoisture;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    OLEDLCD* mainLCD() override;
    Relay* pumpRelay() override;
    SoilMoistureSensor* soilMoisture() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _mainLCD = new OLEDLCD("mainLCD", 0x3C, 128, 64);
    _pumpRelay = new Relay(0, "pumpRelay", true);
    _soilMoisture = new SoilMoistureSensor("soilMoisture", "PIN", 1, A0, 300, 700);
}

void DeviceManager::update()
{
    _resetButton->update();
    _pumpRelay->update();
}

Button* DeviceManager::resetButton()
{
    return appContext->systemContext->getModules()->getButton("resetButton");
}

OLEDLCD* DeviceManager::mainLCD()
{
    return appContext->systemContext->getModules()->getOLEDLCD("mainLCD");
}

Relay* DeviceManager::pumpRelay()
{
    return appContext->systemContext->getModules()->getRelay("pumpRelay");
}

SoilMoistureSensor* DeviceManager::soilMoisture()
{
    return appContext->systemContext->getModules()->getSoilMoistureSensor("soilMoisture");
}



#endif
