
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    String _SetButtonStr = "SetButton";
    Button* _SetButton;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* SetButton() override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _SetButton = new Button(0, "SetButton", false, false, ButtonType::PIN);
}

void DeviceManager::update()
{
    _SetButton->update();
}

Button* DeviceManager::SetButton()
{
    return appContext->systemContext->getModules()->getButton("SetButton");
}



#endif
