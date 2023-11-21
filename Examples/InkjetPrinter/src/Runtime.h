
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "OStad.h"
#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/InkjetPrinterConfig.h"
#include "InkjetPrinter/InkjetPrinter.h"
#include "Apis/Apis.h"
#include "cert_key.h"
// LogLevel definition

class Runtime
{
private:
    OStad* ostad;
    InkjetPrinterConfig* inkjetprinterConfig;
    DeviceManager* deviceManager;
    InkjetPrinter* inkjetprinter;

public:
    Runtime();
    void update();

    AppContext* appContext;
    Context* systemContext;
};

Runtime::Runtime()
{
    CertificateData certificateData;
    certificateData.certificate = const_cast<unsigned char*>(certificate);
    certificateData.privatekey = const_cast<unsigned char*>(private_key);
    certificateData.certificate_length = sizeof(certificate);
    certificateData.privateky_length = sizeof(private_key);

    ostad = new OStad(StorageType::SPIFFS_TYPE, certificateData);
    // If you want to use HTTPS on ESP32 server, add certificate and private_key and uncomment above code and comment below line
    // ostad = new OStad(StorageType::SPIFFS_TYPE);

    systemContext = ostad->getContext();
    appContext = new AppContext(systemContext);

    inkjetprinterConfig = new InkjetPrinterConfig(appContext);
    deviceManager = new DeviceManager(appContext);
    inkjetprinter = new InkjetPrinter(appContext);

    appContext->setInkjetPrinterConfig(inkjetprinterConfig);    
    appContext->setDeviceManager(deviceManager);

    appContext->setinkjetprinter(inkjetprinter);

    //initialize inkjetprinterConfig first of all initialization
    inkjetprinterConfig->initialize();
    deviceManager->initialize();
    inkjetprinter->initialize();

#ifdef OSTAD_NETWORK_ENABLE
    Permissions::addPermissions(systemContext);
    createApis(appContext);
#endif

    ostad->begin();
}

void Runtime::update()
{
    ostad->update();
    deviceManager->update();
    inkjetprinter->update();
}

#endif //RUNTIME_H
