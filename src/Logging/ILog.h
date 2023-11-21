#ifndef ILOG_H
#define ILOG_H

#include <Arduino.h>
#include "../Database/Entities/LogEntitiy.h"

class ILog {
public:
    virtual ~ILog() {}

    virtual void log(LogLevel level, const String &title, const String &message) = 0;
    virtual void log(const String &title, const String &message) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
    virtual void SerialPrint(String message) = 0;
    virtual void attachOutput(Stream *output) = 0; // For flexibility in output destinations
    virtual void update() = 0; // For log rotation management
    virtual void initialize() = 0; // For log initialization
    virtual void DBLog(const String &table,String dbAction, const String &message) = 0;

    // Callbacks for different log levels
    virtual void onDebug(void (*func)(const String &, const String &)) = 0;
    virtual void onInfo(void (*func)(const String &, const String &)) = 0;
    virtual void onWarning(void (*func)(const String &, const String &)) = 0;
    virtual void onError(void (*func)(const String &, const String &)) = 0;
};

#endif // ILOG_H