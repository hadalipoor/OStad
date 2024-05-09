#ifndef LOGENTITY_H
#define LOGENTITY_H

#include "Entity.h"

enum LogLevel {
    DEBUG_LEVEL,
    INFO_LEVEL,
    WARNING_LEVEL,
    ERROR_LEVEL
};
class LogEntity : public Entity {
public:


    static const String COLUMN_LOG_TYPE;
    static const String COLUMN_LOG_TITLE;
    static const String COLUMN_MESSAGE;
private:
    LogLevel logLevel;
    String logTitle;
    String message;
public:
    LogEntity() : Entity() {}

    LogEntity(int id, LogLevel _logLevel, const String &_logTitle, const String &_message) : Entity() {
        this->id = id;
        logLevel = _logLevel;
        logTitle = _logTitle;
        message = _message;
        addColumn(COLUMN_LOG_TYPE, String(static_cast<int>(logLevel)), "int");
        addColumn(COLUMN_LOG_TITLE, logTitle, "string");
        addColumn(COLUMN_MESSAGE, message, "string");

        SetValue(COLUMN_LOG_TYPE, String(static_cast<int>(logLevel)));
        SetValue(COLUMN_LOG_TITLE, logTitle);
        SetValue(COLUMN_MESSAGE, message);
    }
    LogEntity(int id, String _logLevel, const String &_logTitle, const String &_message) : LogEntity(id, getLogLevelFromString(_logLevel), _logTitle, _message)
    {

    }

    LogEntity(LogLevel _logLevel, const String &_logTitle, const String &_message) : LogEntity(0, _logLevel, _logTitle, _message) {}
    LogEntity(String &_logLevel, const String &_logTitle, const String &_message) : LogEntity(0, getLogLevelFromString(_logLevel), _logTitle, _message) {}

    static LogEntity fromEntity(Entity entity)
    {
        LogEntity logEntity = LogEntity();
        logEntity.fromString(entity.toString());
        return logEntity;
    }

    void setLogType(LogLevel _logLevel) {
        logLevel = _logLevel;
        SetValue(COLUMN_LOG_TYPE, String(static_cast<int>(logLevel)));
    }

    LogLevel getLogType() {
        return logLevel;
    }

    void setLogTitle(const String &_logTitle) {
        logTitle = _logTitle;
        SetValue(COLUMN_LOG_TITLE, _logTitle);
    }

    String getLogTitle() {
        return logTitle;
    }

    void setMessage(const String &_message) {
        message = _message;
        SetValue(COLUMN_MESSAGE, _message);
    }

    String getMessage() {
        return message;
    }

    LogLevel getLogLevelFromString(String& loglevelStr) {
        if (loglevelStr == "DEBUG_LEVEL") {
            return DEBUG_LEVEL;
        } else if (loglevelStr == "INFO_LEVEL") {
            return INFO_LEVEL;
        } else if (loglevelStr == "WARNING_LEVEL") {
            return WARNING_LEVEL;
        } else if (loglevelStr == "ERROR_LEVEL") {
            return ERROR_LEVEL;
        }

        // Optionally, handle the case where the string does not match any LogLevel
        throw std::invalid_argument("Invalid log level string");
    }

};

const String LogEntity::COLUMN_LOG_TYPE = "logLevel";
const String LogEntity::COLUMN_LOG_TITLE = "logTitle";
const String LogEntity::COLUMN_MESSAGE = "message";

#endif // LOGENTITY_H
