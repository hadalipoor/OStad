
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

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    OLEDLCD* mainLCD() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _mainLCD = new OLEDLCD("mainLCD", 0x3C, 128, 64);
}

void DeviceManager::update()
{
    _resetButton->update();
}

Button* DeviceManager::resetButton()
{
    return appContext->systemContext->getModules()->getButton("resetButton");
}

OLEDLCD* DeviceManager::mainLCD()
{
    return appContext->systemContext->getModules()->getOLEDLCD("mainLCD");
}



#endif
