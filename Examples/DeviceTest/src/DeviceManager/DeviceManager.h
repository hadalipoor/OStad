
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    
public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
}

void DeviceManager::update()
{
}



#endif
