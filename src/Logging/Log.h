#ifndef LOG_H
#define LOG_H

#include <vector>
#include "ILog.h"
#include "../Context.h"
#include "../Database/Controllers/LogController.h"

/**
 * @brief Log class implementing the ILog interface
 * 
 * This class provides an implementation for the logging system. 
 * It supports multiple log levels, log rotation, and attaching multiple output streams.
 */
class Log : public ILog {
private:
    Context* context;
    LogController* logController;
    LogLevel currentLogLevel;
    std::vector<Stream*> outputs; // Holds the output streams
    void (*debugCallback)(const String &, const String &);
    void (*infoCallback)(const String &, const String &);
    void (*warningCallback)(const String &, const String &);
    void (*errorCallback)(const String &, const String &);
    virtual void rotateLogs();

public:
    Log(Context* cntxt);

    virtual ~Log();

    // Implementing ILog interface methods
    virtual void log(LogLevel level, const String &title, const String &message) override;
    virtual void log(const String &title, const String &message) override;
    virtual void setLogLevel(LogLevel level) override;
    virtual void SerialPrint(String message) override;
    virtual void attachOutput(Stream *output) override;
    virtual void update() override;
    virtual void initialize() override;
    void DBLog(const String &table,String dbAction, const String &message) override;

    // Implementing callbacks
    virtual void onDebug(void (*func)(const String &, const String &)) override;
    virtual void onInfo(void (*func)(const String &, const String &)) override;
    virtual void onWarning(void (*func)(const String &, const String &)) override;
    virtual void onError(void (*func)(const String &, const String &)) override;
};

/**
 * @brief Construct a new Log System:: Log System object
 * 
 */
Log::Log(Context* cntxt):context(cntxt) {
    // Initialize with default settings
    currentLogLevel = LogLevel::DEBUG_LEVEL;

    logController = new LogController(context, storageType);
}

/**
 * @brief Destroy the Log System:: Log System object
 * 
 */
Log::~Log() {
    // Clean up resources if needed
}

/**
 * @brief Logs a message with the given level, title, and message.
 * 
 * @param level LogLevel for the message
 * @param title Title of the log message
 * @param message Log message content
 */
void Log::log(LogLevel level, const String &title, const String &message) {
    String logLevelString;
    
    switch (level) {
        case LogLevel::DEBUG_LEVEL:
#ifndef LOG_LEVEL_DEBUG
            return;
#endif
            logLevelString = "DEBUG_LEVEL";
            break;
        case LogLevel::INFO_LEVEL:
#ifndef LOG_LEVEL_INFO
            return;
#endif
            logLevelString = "INFO_LEVEL";
            break;
        case LogLevel::WARNING_LEVEL:
#ifndef LOG_LEVEL_WARNING
            return;
#endif
            logLevelString = "WARNING_LEVEL";
            break;
        case LogLevel::ERROR_LEVEL:
#ifndef LOG_LEVEL_ERROR
            return;
#endif
            logLevelString = "ERROR_LEVEL";
            break;
    }
    // Implement logging logic
    // Check log level and route message to appropriate output streams
    if(context->getConfig()->getSystemConfig()->get(title+LogTitles::_INFO_CHANGE) == "true")
    {
        LogEntity *logEntity = new LogEntity(level, title, message);
        // logController->Add(*logEntity);
    }
    
    ///TODO: check from config to print on serial or not
    Serial.println(context->getClock()->now().toTimeString() + " - " + logLevelString + " - " + title + " : " + message);

    switch (level) {
        case LogLevel::DEBUG_LEVEL:
            if (debugCallback != nullptr) {
                debugCallback(title, message);
            }
            break;
        case LogLevel::INFO_LEVEL:
            if (infoCallback != nullptr) {
                infoCallback(title, message);
            }
            break;
        case LogLevel::WARNING_LEVEL:
            if (warningCallback != nullptr) {
                warningCallback(title, message);
            }
            break;
        case LogLevel::ERROR_LEVEL:
            if (errorCallback != nullptr) {
                errorCallback(title, message);
            }
            break;
    }
}

/**
 * @brief Logs a message with the current log level, title, and message.
 * 
 * @param title Title of the log message
 * @param message Log message content
 */
void Log::log(const String &title, const String &message) {
    log(currentLogLevel, title, message);
}

void Log::DBLog(const String &table,String dbActionStr, const String &message)
{
    if (table != logController->_tableName)
    {
        log(LogLevel::INFO_LEVEL, LogTitles::DB_CHANGE , dbActionStr + "::" + message + " at " + table);
    }    
}

/**
 * @brief Sets the current log level of the system.
 * 
 * @param level LogLevel to be set
 */
void Log::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

void Log::SerialPrint(String message) {
    if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::SERIAL_PRINT_ENABLE) == "true")
    {
        Serial.println(message);
    }
}


/**
 * @brief Attaches an output stream for logging.
 * 
 * @param output Stream pointer to be attached
 */
void Log::attachOutput(Stream *output) {
    outputs.push_back(output);
}

/**
 * @brief Rotates logs to manage log size and retention.
 * 
 */
void Log::rotateLogs() {
    // Implement log rotation logic
}

/**
 * @brief 
 * 
 */
void Log::initialize(){
    currentLogLevel = LogLevel::DEBUG_LEVEL;

    logController = new LogController(context, storageType);
    debugCallback = nullptr;
    infoCallback = nullptr;
    warningCallback = nullptr;
    errorCallback = nullptr;
}

/**
 * @brief 
 * 
 */
void Log::update(){
    rotateLogs();
}

/**
 * @brief Registers a callback function for DEBUG_LEVEL level logs.
 * 
 * This method allows the user to set a custom callback function that will be 
 * called whenever a log with DEBUG_LEVEL level is generated. The callback function 
 * should accept two parameters: a title and a message, both as strings.
 * 
 * @param func The callback function that takes two string parameters (title, message).
 */
void Log::onDebug(void (*func)(const String &, const String &)) {
    debugCallback = func;
}

/**
 * @brief Registers a callback function for INFO_LEVEL level logs.
 * 
 * This method allows setting a custom callback for INFO_LEVEL level logs. 
 * The provided function will be invoked with the log's title and message.
 * 
 * @param func Callback function to be invoked for INFO_LEVEL level logs.
 */
void Log::onInfo(void (*func)(const String &, const String &)) {
    infoCallback = func;
}

/**
 * @brief Registers a callback function for WARNING_LEVEL level logs.
 * 
 * Enables the attachment of a custom callback function for logs of WARNING_LEVEL level.
 * The function will receive the log's title and message as arguments.
 * 
 * @param func The WARNING_LEVEL level log callback function.
 */
void Log::onWarning(void (*func)(const String &, const String &)) {
    warningCallback = func;
}

/**
 * @brief Registers a callback function for ERROR_LEVEL level logs.
 * 
 * This method is used to set a custom callback for logs of the ERROR_LEVEL level.
 * The callback will be called with the log's title and message.
 * 
 * @param func The ERROR_LEVEL level log callback function.
 */
void Log::onError(void (*func)(const String &, const String &)) {
    errorCallback = func;
}


#endif // LOG_H
