
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/SabooraHub2Config.h"
#include "SabooraHub2/SabooraHub2.h"
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
    SabooraHub2Config* saboorahub2Config;
    DeviceManager* deviceManager;
    SabooraHub2* saboorahub2;

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

    saboorahub2Config = new SabooraHub2Config(appContext);
    deviceManager = new DeviceManager(appContext);
    saboorahub2 = new SabooraHub2(appContext);

    appContext->setSabooraHub2Config(saboorahub2Config);    
    appContext->setDeviceManager(deviceManager);

    appContext->setsaboorahub2(saboorahub2);

    //initialize saboorahub2Config first of all initialization
    saboorahub2Config->initialize();
    deviceManager->initialize();
    saboorahub2->initialize();

    createApis(appContext);

    Permissions::addPermissions(systemContext);
    
    ostad->begin();
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    saboorahub2->update();
}

#endif //RUNTIME_H
