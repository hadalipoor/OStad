
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/DeviceTestConfig.h"
#include "DeviceTest/DeviceTest.h"
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
    DeviceTestConfig* devicetestConfig;
    DeviceManager* deviceManager;
    DeviceTest* devicetest;

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

    devicetestConfig = new DeviceTestConfig(appContext);
    deviceManager = new DeviceManager(appContext);
    devicetest = new DeviceTest(appContext);

    appContext->setDeviceTestConfig(devicetestConfig);    
    appContext->setDeviceManager(deviceManager);

    appContext->setdevicetest(devicetest);

    //initialize devicetestConfig first of all initialization
    devicetestConfig->initialize();
    deviceManager->initialize();
    devicetest->initialize();

    createApis(appContext);

    Permissions::addPermissions(systemContext);
    
    ostad->begin();
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    devicetest->update();
}

#endif //RUNTIME_H
