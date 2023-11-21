#ifndef OSTAD_H
#define OSTAD_H

#include <Arduino.h>
#include <PCF8574.h>
#include "Context.h"
#include "Config/Configs.h"
#include "Logging/Log.h"
#include "ErrorHandler/ErrorHandler.h"
#include "Validation/Validation.h"
#ifdef OSTAD_NETWORK_ENABLE
#include "NetworkManager/Network.h"
#include "Security/Security.h"
#endif
#include "Clock/Clock.h"
#include "FileManager/EBPFile.h"
#include "ModuleManager/Modules.h"
#include "SystemMonitor/SystemMonitor.h"
#include "DatabaseSeeder.h"

class OStad
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
    Modules* modules;
    SystemMonitor* systemMonitor;
#ifdef OSTAD_NETWORK_ENABLE
    Network* network;
    Security* security;
    CertificateData _certificateData;
#endif
    void initialize();


public:
    OStad(StorageType storageType);
#ifdef OSTAD_NETWORK_ENABLE
    OStad(StorageType storageType, CertificateData certificateDate);
#endif
    ~OStad();

    void update();
    void begin();
    Context* getContext();
    DatabaseSeeder* dbSeeder;
};

#ifdef OSTAD_NETWORK_ENABLE
OStad::OStad(StorageType _storageType ,CertificateData certificateData) :  _certificateData(certificateData)
{
    _https_enabled = true;
    storageType = _storageType;
    initialize();
}
#endif

OStad::OStad(StorageType _storageType)
{
    storageType = _storageType;
    initialize();
}

OStad::~OStad()
{
}

Context* OStad::getContext()
{
    return context;
}

void OStad::initialize() {
    context = new Context();
    errorHandler = new ErrorHandler();
    validation = new Validation();
    configs = new Configs(context);
    logger = new Log(context);
    _clock = new Clock(context);
    ebpLittleFS = new EBPFile(context, StorageType::SPIFFS_TYPE);
    ebpSD = new EBPFile(context, StorageType::SD_TYPE);
#ifdef OSTAD_NETWORK_ENABLE
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
    modules = new Modules(context);
    systemMonitor = new SystemMonitor();
    

    context->setConfig(configs);
    context->setLogger(logger);
    context->setErrorHandler(errorHandler);
    context->setValidation(validation);
    context->setClock(_clock);
    context->setLittleFS(ebpLittleFS);
    context->setSD(ebpSD);
#ifdef OSTAD_NETWORK_ENABLE
    context->setNetwork(network);
    context->setSecurity(security);
#endif
    context->setModules(modules);
    context->setSystemMonitor(systemMonitor);
    
    ebpLittleFS->createDirectory("/db/");
    
    configs->initialize();
    _clock->initialize();
    logger->initialize();
    modules->initialize();
    
#ifdef OSTAD_NETWORK_ENABLE
    network->initialize();
    _clock->syncTimeWithServer();
    security->initialize();
#endif
    
    // logger->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Seeding Database ...");
    // dbSeeder = new DatabaseSeeder(context);
    // dbSeeder->seed();
    // logger->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Database Seed.");

    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "OStad is Loaded.");

}    

void OStad::begin()
{
#ifdef OSTAD_NETWORK_ENABLE
    network->begin();
#endif
}

void OStad::update() {
#ifdef OSTAD_NETWORK_ENABLE
    network->update();
#endif
}

#endif // OSTAD_H