
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/ElevatorControlConfig.h"
#include "ElevatorControl/ElevatorControl.h"
#include "Apis/Apis.h"
#include "cert_key.h"

// LogLevel definition
#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR

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
    // CertificateData certificateData;
    // certificateData.certificate = const_cast<unsigned char*>(certificate);
    // certificateData.privatekey = const_cast<unsigned char*>(private_key);
    // certificateData.certificate_length = sizeof(certificate);
    // certificateData.privateky_length = sizeof(private_key);

    // ostad = new OStad(StorageType::SPIFFS_TYPE, certificateData);
    // If you want to use HTTPS on ESP32 server, add certificate and private_key and uncomment above code and comment below line
    ostad = new OStad(StorageType::SPIFFS_TYPE);

    
    systemContext = ostad->getContext();
    appContext = new AppContext(systemContext);

    elevatorcontrolConfig = new ElevatorControlConfig(appContext);
    deviceManager = new DeviceManager(appContext);
    elevatorcontrol = new ElevatorControl(appContext);

    appContext->setElevatorControlConfig(elevatorcontrolConfig);    
    appContext->setDeviceManager(deviceManager);

    appContext->setelevatorcontrol(elevatorcontrol);

    //initialize elevatorcontrolConfig first of all initialization
    elevatorcontrolConfig->initialize();
    deviceManager->initialize();
    elevatorcontrol->initialize();

    createApis(appContext);

    Permissions::addPermissions(systemContext);
    
    ostad->begin();
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    elevatorcontrol->update();
}

#endif //RUNTIME_H
