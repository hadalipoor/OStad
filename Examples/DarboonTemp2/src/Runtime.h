
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/DarboonTemp2Config.h"
#include "DarboonTemp2/DarboonTemp2.h"
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
    DarboonTemp2Config* darboontemp2Config;
    DeviceManager* deviceManager;
    DarboonTemp2* darboontemp2;

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

    darboontemp2Config = new DarboonTemp2Config(appContext);
    deviceManager = new DeviceManager(appContext);
    darboontemp2 = new DarboonTemp2(appContext);

    appContext->setDarboonTemp2Config(darboontemp2Config);    
    appContext->setDeviceManager(deviceManager);

    appContext->setdarboontemp2(darboontemp2);

    //initialize darboontemp2Config first of all initialization
    darboontemp2Config->initialize();
    deviceManager->initialize();
    darboontemp2->initialize();

    createApis(appContext);

    Permissions::addPermissions(systemContext);
    
    ostad->begin();
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    darboontemp2->update();
}

#endif //RUNTIME_H
