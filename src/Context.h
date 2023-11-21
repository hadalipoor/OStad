/**
 * @file Context.h
 * @brief Context class definition and its associated functionalities.
 * 
 * This file contains the Context class which is used for managing various components
 * like configurations, logging, error handling, validation, and more.
 * 
 * @author hadalipoor@gmail.com
 */

#ifndef CONTEXT_H
#define CONTEXT_H

#include "Config/IConfigs.h"
#include "Security/ISecurity.h"
#include "Database/Controllers/IController.h"
#include "Logging/ILog.h"
#include "ErrorHandler/IErrorHandler.h"
#include "Validation/IValidation.h"
#include "Clock/IClock.h"
#include "FileManager/IEBPFile.h"
#include "NetworkManager/INetwork.h"
#include "ModuleManager/IModules.h"
#include "SystemMonitor/ISystemMonitor.h"

/**
 * @brief Static variable to store storage type.
 */
static StorageType storageType;

/**
 * @brief Static variable to enable/disable HTTPS support.
 */
static bool _https_enabled = false;

/**
 * @class Context
 * @brief The Context class provides a way to access different system modules.
 * 
 * It acts as a central point to manage configurations, logger, error handlers, validations,
 * clock, file system, network, modules, system monitoring, and security.
 */
class Context {
public:
    /**
     * @brief Constructor for Context.
     */
    Context() {}

    /**
     * @brief Get the Config object.
     * 
     * @return IConfigs* Pointer to the configuration interface.
     */
    IConfigs* getConfig() { return _config; }

    /**
     * @brief Set the Config object.
     * 
     * @param config Pointer to the configuration interface.
     */
    void setConfig(IConfigs* config) { _config = config; }
    
    /**
     * @brief Get the Logger object.
     * 
     * @return ILog* Pointer to the logging interface.
     */
    ILog* getLogger() { return logger; }

    /**
     * @brief Set the Logger object.
     * 
     * @param log Pointer to the logging interface.
     */
    void setLogger(ILog* log) { logger = log; }

    /**
     * @brief Get the Error Handler object.
     * 
     * @return IErrorHandler* Pointer to the error handler interface.
     */
    IErrorHandler* getErrorHandler() { return errorHandler; }

    /**
     * @brief Set the Error Handler object.
     * 
     * @param handler Pointer to the error handler interface.
     */
    void setErrorHandler(IErrorHandler* handler) { errorHandler = handler; }

    /**
     * @brief Get the Validation object.
     * 
     * @return IValidation* Pointer to the validation interface.
     */
    IValidation* getValidation() { return validation; }

    /**
     * @brief Set the Validation object.
     * 
     * @param val Pointer to the validation interface.
     */
    void setValidation(IValidation* val) { validation = val; }

    /**
     * @brief Get the Clock object.
     * 
     * @return IClock* Pointer to the clock interface.
     */
    IClock* getClock() { return _clock; }

    /**
     * @brief Set the Clock object.
     * 
     * @param clk Pointer to the clock interface.
     */
    void setClock(IClock* clk) { _clock = clk; }

    /**
     * @brief Get the LittleFS object.
     * 
     * @return IEBPFile* Pointer to the LittleFS file system interface.
     */
    IEBPFile* getLittleFS() { return ebpLittleFS; }

    /**
     * @brief Set the LittleFS object.
     * 
     * @param ebpsp Pointer to the LittleFS file system interface.
     */
    void setLittleFS(IEBPFile* ebpsp) { ebpLittleFS = ebpsp; }
    
    /**
     * @brief Get the SD File System object.
     * 
     * @return IEBPFile* Pointer to the SD file system interface.
     */
    IEBPFile* getSD() { return ebpSD; }

    /**
     * @brief Set the SD File System object.
     * 
     * @param ebpsd Pointer to the SD file system interface.
     */
    void setSD(IEBPFile* ebpsd) { ebpSD = ebpsd; }

    /**
     * @brief Get the Network object.
     * 
     * @return INetwork* Pointer to the network interface.
     */
    INetwork* getNetwork(){ return _network; }

    /**
     * @brief Set the Network object.
     * 
     * @param network Pointer to the network interface.
     */
    void setNetwork(INetwork* network) { _network = network; }

    /**
     * @brief Get the Modules object.
     * 
     * @return IModules* Pointer to the modules interface.
     */
    IModules* getModules(){ return _modules; }

    /**
     * @brief Set the Modules object.
     * 
     * @param modules Pointer to the modules interface.
     */
    void setModules(IModules* modules) { _modules = modules; }

    /**
     * @brief Get the System Monitor object.
     * 
     * @return ISystemMonitor* Pointer to the system monitor interface.
     */
    ISystemMonitor* getSystemMonitor(){ return _systemMonitor; }

    /**
     * @brief Set the System Monitor object.
     * 
     * @param systemMonitor Pointer to the system monitor interface.
     */
    void setSystemMonitor(ISystemMonitor* systemMonitor) { _systemMonitor = systemMonitor; }

    /**
     * @brief Get the Security object.
     * 
     * @return ISecurity* Pointer to the security interface.
     */
    ISecurity* getSecurity(){ return _security; }

    /**
     * @brief Set the Security object.
     * 
     * @param security Pointer to the security interface.
     */
    void setSecurity(ISecurity* security) { _security = security; }

private:
    IConfigs* _config;
    ILog* logger;
    IErrorHandler* errorHandler;
    IValidation* validation;
    IClock* _clock;
    IEBPFile* ebpLittleFS;
    IEBPFile* ebpSD;
    INetwork* _network;
    IModules* _modules;
    ISecurity* _security;
    ISystemMonitor* _systemMonitor;
};

#endif // CONTEXT_H
