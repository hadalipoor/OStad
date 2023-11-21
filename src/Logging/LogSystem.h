// // path: .\src\Basic\Logging\Log.h

// #ifndef LOG_H
// #define LOG_H

// #include "../Context.h"
// #include "../Database/Controllers/LogController.h"
// #include "ILog.h"
// #include <memory>

// // #include "../Events/EventSystem.h"

// class SystemLog : public ILog {

// public:
//     Context* context;
//     LogController* logController;
//     // static EventSystem eventSystem;
    
//     SystemLog(Context* cntxt):context(cntxt)
//     {
//         logController = new LogController(context, storageType);
//     }

//     void infoDB(const String &table,String dbAction, const String &message) override;
//     void info(const String &title, const String &message) override;
//     void warning(const String &title, const String &message) override;
//     void error(const String &title, const String &message) override;

//     void onInfo(void (*func)(const String &)) override;
//     void onWarning(void (*func)(const String &)) override;
//     void onError(void (*func)(const String &)) override;
//     String value = "";
// };

// // EventSystem Log::eventSystem;

// void SystemLog::infoDB(const String &table,String dbActionStr, const String &message)
// {
//     if (table != logController->_tableName)
//     {
//         info(LogTitles::DB_CHANGE , dbActionStr + "::" + message + " at " + table);
//     }    
// }
// void SystemLog::info(const String &title, const String &message) {
//     if(context->getConfig()->getSystemConfig()->get(title+LogTitles::_INFO_CHANGE) == "true")
//     {
//         LogEntity *logEntity = new LogEntity(LogLevel::INFO, title, message);
//         logController->Add(*logEntity);
//     }
//     Serial.println(title + " - " + message);
//     // eventSystem.emit("info", message);
// }

// void SystemLog::warning(const String &title, const String &message) {
//     // LogEntity logEntity;
//     // logEntity.logLevel = LogEntity::Warning;
//     // logEntity.message = message;
//     // logEntity.timestamp = String(millis());
    
//     // if(context.getConfig()->get(title+"_warning_save") == "true")
//     // {
//     //     logController->Add(logEntity);
//     // }
//     // eventSystem.emit("warning", message);
// }

// void SystemLog::error(const String &title, const String &message) {
//     // LogEntity logEntity;
//     // logEntity.logLevel = LogEntity::Error;
//     // logEntity.message = message;
//     // logEntity.timestamp = String(millis());
    
//     // if(context.getConfig()->get(title+"_error_save") == "true")
//     // {
//     //     logController->Add(logEntity);
//     // }
//     // eventSystem.emit("error", message);
//     Serial.print("Error - ");Serial.print(title);Serial.print(" - ");Serial.print(message);Serial.print(" - ");Serial.print(context->getClock()->now().toTimeString());
// }

// void SystemLog::onInfo(void (*func)(const String &)) {
//     // eventSystem.on("info", func);
// }

// void SystemLog::onWarning(void (*func)(const String &)) {
//     // eventSystem.on("warning", func);
// }

// void SystemLog::onError(void (*func)(const String &)) {
//     // eventSystem.on("error", func);
// }

// #endif // LOG_H
