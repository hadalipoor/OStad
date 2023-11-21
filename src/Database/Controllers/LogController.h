// path: .\src\Basic\Database\Controllers\LogController.h

#ifndef BASELOGCONTROLLER_H
#define BASELOGCONTROLLER_H

#include "../Entities/LogEntitiy.h"
#include "MainController.h"
#include <Arduino.h>
#include <vector>


class LogController : public MainController<LogEntity>{
protected:
    Context* context;
public:
    LogController(Context* context, StorageType _storageType) : MainController(context, "logs", _storageType), context(context) {}
    void AddLog(LogLevel logLevel, String logTitle, String logMessage);
    std::vector<LogEntity> GetAllLogs();
};

void LogController::AddLog(LogLevel logLevel, String logTitle, String logMessage) {
    LogEntity logEntity = LogEntity();
    logEntity.logLevel = logLevel;
    logEntity.logTitle = logTitle;
    logEntity.message = logMessage;
    Add(logEntity);
}

std::vector<LogEntity> LogController::GetAllLogs() {
    std::vector<LogEntity> logs = GetAll();    
    return logs;
}

#endif // BASELOGCONTROLLER_H
