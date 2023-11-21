
#ifndef RUNTIME_H
#define RUNTIME_H

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/ElevatorControlConfig.h"
#include "ElevatorControl/ElevatorControl.h"
#include "Apis/Apis.h"

class Runtime
{
private:
    OStad* ostad;
    ElevatorControlConfig* elevatorcontrolConfig;
    DeviceManager* deviceManager;
    ElevatorControl* elevatorcontrol;

public:
    Runtime();
    void update();

    AppContext* appContext;
    Context* systemContext;
};

Runtime::Runtime()
{
    ostad = new OStad(StorageType::SPIFFS_TYPE);
    systemContext = ostad->getContext();
    appContext = new AppContext(systemContext);

    elevatorcontrolConfig = new ElevatorControlConfig(appContext);
    deviceManager = new DeviceManager(appContext);
    elevatorcontrol = new ElevatorControl(appContext);

    appContext->setElevatorControlConfig(elevatorcontrolConfig);    
    appContext->setDeviceManager(deviceManager);

    appContext->setelevatorcontrol(elevatorcontrol);

    // initialize elevatorcontrolConfig first of all initialization
    elevatorcontrolConfig->initialize();
    deviceManager->initialize();
    elevatorcontrol->initialize();

    createApis(appContext);

    // Permissions::addPermissions(systemContext);
    
    ostad->begin();
    Serial.println("EBP Loaded");
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    elevatorcontrol->update();
}

#endif //RUNTIME_H
