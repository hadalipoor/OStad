#ifndef OSTADDEV_H
#define OSTADDEV_H

#include <Arduino.h>
#include "Context.h"
#include "Config/Configs.h"
#include "Logging/Log.h"
#include "ErrorHandler/ErrorHandler.h"
#include "Validation/Validation.h"
#ifndef OSTAD_NETWORK_DISABLE
#include "NetworkManager/Network.h"
#include "Security/Security.h"
#endif
#include "Clock/Clock.h"
#include "FileManager/EBPFile.h"
#ifndef OSTAD_MODULES_DISABLE
#include <PCF8574.h>
#include "ModuleManager/Modules.h"
#endif
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
#include "DeviceManager/DeviceManager.h"
#endif
#include "SystemMonitor/SystemMonitor.h"
#include "DatabaseSeeder.h"

class OStad_dev
{
private:
    Context* context;
    Log* logger;
    Configs* configs;
    ErrorHandler* errorHandler;
    Validation* validation;
    Clock* _clock;
    EBPFile* ebpLittleFS;
    EBPFile* ebpSD;
#ifndef OSTAD_MODULES_DISABLE
    Modules* modules;
#endif
    SystemMonitor* systemMonitor;
#ifndef OSTAD_NETWORK_DISABLE
    Network* network;
    Security* security;
    CertificateData _certificateData;
#endif
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
    DeviceManager* _deviceManager;
#endif
    void initialize();


public:
    OStad_dev(StorageType storageType);
#ifndef OSTAD_NETWORK_DISABLE
    OStad_dev(StorageType storageType, CertificateData certificateDate);
#endif
    ~OStad_dev();

    void update();
    void begin();
    Context* getContext();
    DatabaseSeeder* dbSeeder;
};

#ifndef OSTAD_NETWORK_DISABLE
OStad_dev::OStad_dev(StorageType _storageType ,CertificateData certificateData) :  _certificateData(certificateData)
{
    _https_enabled = true;
    storageType = _storageType;
    initialize();
}
#endif

OStad_dev::OStad_dev(StorageType _storageType)
{
    storageType = _storageType;
    initialize();
}

OStad_dev::~OStad_dev()
{
}

Context* OStad_dev::getContext()
{
    return context;
}

void OStad_dev::initialize() {
    context = new Context();
    errorHandler = new ErrorHandler();
    validation = new Validation();
    configs = new Configs(context);
    logger = new Log(context);
    _clock = new Clock(context);
    ebpLittleFS = new EBPFile(context, StorageType::SPIFFS_TYPE);
    ebpSD = new EBPFile(context, StorageType::SD_TYPE);
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
    _deviceManager = new DeviceManager(context);
#endif
#ifndef OSTAD_NETWORK_DISABLE
    if (_https_enabled)
    {
        network = new Network(context, _certificateData);
    }
    else
    {
        network = new Network(context);
    }
    security = new Security(context);
#endif
#ifndef OSTAD_MODULES_DISABLE
    modules = new Modules(context);
#endif
    systemMonitor = new SystemMonitor();
    validation = new Validation(context);

    context->setConfig(configs);
    context->setLogger(logger);
    context->setErrorHandler(errorHandler);
    context->setValidation(validation);
    context->setClock(_clock);
    context->setLittleFS(ebpLittleFS);
    context->setSD(ebpSD);
#ifndef OSTAD_NETWORK_DISABLE
    context->setNetwork(network);
    context->setSecurity(security);
#endif
#ifndef OSTAD_MODULES_DISABLE
    context->setModules(modules);
#endif
    context->setSystemMonitor(systemMonitor);
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
    context->setDeviceManager(_deviceManager);
#endif
    ebpLittleFS->createDirectory("/db/");
    
    configs->initialize();
    _clock->initialize();
    logger->initialize();
#ifndef OSTAD_MODULES_DISABLE
    modules->initialize();
#endif
    
#ifndef OSTAD_NETWORK_DISABLE
    network->initialize();
    _clock->syncTimeWithServer();
    security->initialize();
#endif
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
    _deviceManager->initialize();
#endif
    // logger->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Seeding Database ...");
    // dbSeeder = new DatabaseSeeder(context);
    // dbSeeder->seed();
    // logger->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Database Seed.");

    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "OStad is Loaded.");

}    

void OStad_dev::begin()
{
#ifndef OSTAD_NETWORK_DISABLE
    network->begin();
#endif
}

void OStad_dev::update() {
#ifndef OSTAD_MODULES_DISABLE
    modules->update();
#endif
#ifndef OSTAD_NETWORK_DISABLE
    network->update();
#endif
#ifndef OSTAD_DEVICE_MANAGER_DISABLE
    _deviceManager->update();
#endif
}

#endif // OSTAD_H