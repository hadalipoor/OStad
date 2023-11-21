#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include <string>
#include <ArduinoJson.h>
#include "IController.h"
#include "../../Config/StaticConfigs.h"
#include "../../Context.h"
#include "../../Logging/LogTitles.h"

template<typename T>
class MainController : public IController<T> {
private:
public:
    Context* context;
    String path;
    String _tableName;
    StorageType _storageType;

    MainController(Context* context, String tableName, StorageType _storageType) : context(context), _storageType(_storageType){
        _tableName = tableName;
        path = String(StaticConfigs::DATABASE_PATH + _tableName + ".db");
    }



void RemoveTable()
{
  if (!(_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->exists(path)) {
        context->getErrorHandler()->handleError(ErrorType::TableDoesNotExist);
        return;
  }
    (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->remove(path);
    context->getLogger()->DBLog(_tableName, LogTitles::REMOVE_TABLE, LogTitles::REMOVE_TABLE_FROM_DB + " - table = " + _tableName);
}


void removeColumn(const String column_name) {
    if (!context->getValidation()->isColumnNameValid(column_name)) {
        context->getErrorHandler()->handleError(ErrorType::InvalidColumnName);
        return;
    }

    std::vector<T> entities = GetAll();
    for (size_t i = 0; i < entities.size(); i++) {
        entities.at(i).removeColumn(column_name);
    }

    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "w");
    for (size_t i = 0; i < entities.size(); i++) {
        file->println(entities.at(i).toString());
    }
    file->close();
    context->getLogger()->DBLog(_tableName, LogTitles::REMOVE_COLUMN, LogTitles::REMOVE_COLUMN_FROM_DB + " - column = " + column_name + " from table " + _tableName);
}


int Add(T& entity) {

  int entity_id = -1;
    T e{};
    entity.createDate = context->getClock()->now();
    // entity.createDate = EBPDateTime(2000,1,1,0,0,0);    
    e.fromString(entity.toString());
    if (e.id == -1 || e.id == 0) {
        int maxId = 0;
        std::vector<T> entities = GetAll();
        for (size_t i = 0; i < entities.size(); i++) {
            if (entities.at(i).id > maxId) {
                maxId = entities.at(i).id;
            }
        }
        e.id = maxId + 1;
        entity_id = e.id;
        e.createDate = context->getClock()->now();
    } else {

        T existing_entity = GetById(e.id);
        if (existing_entity.id != -1) {
          context->getErrorHandler()->handleError(ErrorType::CustomError, "Entity with the same ID already exists");
          return -1;
        }
    }

    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "a");
    file->println(e.toString());
    file->close();
    
    context->getLogger()->DBLog(_tableName, LogTitles::ADD, LogTitles::ADD_RECORD_TO_DB + " - id = " + String(entity_id));
    return entity_id;
}


bool Update(T& entity) {
    // T e = entity.toEntity();
    std::vector<T> entities = GetAll();
    bool entity_found = false;
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities.at(i).id == entity.id) {
            entities.at(i) = entity;
            entity_found = true;
            break;
        }
    }

    if (!entity_found) {
        context->getErrorHandler()->handleError(ErrorType::CustomError, "Entity not found");
        return false;
    }

    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "w");
    for (size_t i = 0; i < entities.size(); i++) {
        file->println(entities.at(i).toString());
    }
    file->close();
    
    context->getLogger()->DBLog(_tableName, LogTitles::UPDATE, LogTitles::UPDATE_RECORD_IN_DB + " - id = " + String(entity.id));
    return true;
}


bool Delete(int id) {
    std::vector<T> entities = GetAll();
    bool entity_found = false;
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities.at(i).id == id) {
            entities.erase(entities.begin() + i);
            entity_found = true;
            break;
        }
    }

    if (!entity_found) {
        context->getErrorHandler()->handleError(ErrorType::CustomError, "Entity not found");
        return false;
    }

    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "w");
    for (size_t i = 0; i < entities.size(); i++) {
        file->println(entities.at(i).toString());
    }
    file->close();
    context->getLogger()->DBLog(_tableName, LogTitles::DELETE, LogTitles::DELETE_RECORD_FROM_DB + " - id = " + String(id));
    return true;
}


T GetById(int id) {
    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "r");
    if (!file) {
        context->getErrorHandler()->handleError(ErrorType::FileOpenError);
        return T::fromEntity(T::Invalid());
    }

    String line;
    while (file->available()) {
        line = file->readStringUntil('\n');
        T entity{};
        entity.fromString(line);
        if (entity.id == id) {
            file->close();
            return T::fromEntity(entity);
        }
    }
    file->close();
    return T::fromEntity(T::Invalid());
}

std::vector<T> GetAll() {
    std::vector<T> entities;
  if(_storageType == StorageType::SPIFFS_TYPE)
  {
    
    if(context->getLittleFS()->exists(path))
    {
    }
    
  }
    if(!(_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->exists(path))
    {
      return entities;
    }
    IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "r");
    if (!file) {
        context->getErrorHandler()->handleError(ErrorType::FileOpenError);
        return entities;
    }

    String line;
    while (file->available()) {
        line = file->readStringUntil('\n');
        T entity{};
        entity.fromString(line);
        entities.push_back(entity);
    }
    file->close();
    return entities;
}


String GetAllJson() {
    std::vector<T> entities = GetAll();
    String result = "[";
    for (size_t i = 0; i < entities.size(); i++) {
        result += entities.at(i).toJson();
        if (i < entities.size() - 1) {
            result += ",";
        }
    }
    result += "]";
    return result;
}


String GetJson(String query) {
    std::vector<T> entities = Get(query);
    String result = "[";
    for (size_t i = 0; i < entities.size(); i++) {
        result += entities.at(i).toJson();
        if (i < entities.size() - 1) {
            result += ",";
        }
    }
    result += "]";
    return result;
}

std::vector<T> Get(const char* format, ...) {
    std::vector<T> entities;

    // Buffer to store the formatted string
    char query[512]; // Adjust the size as needed

    // Start variadic argument processing
    va_list args;
    va_start(args, format);
    // Create formatted string
    vsnprintf(query, sizeof(query), format, args);
    // End variadic argument processing
    va_end(args);
    return Get(String(query));
}

std::vector<T> Get(const String query) {

  std::vector<T> entities;
  if (_storageType == StorageType::SPIFFS_TYPE)
  {
    if(!LittleFS.exists(path))
    {
      return entities;
    }
  }else{
    if (!SD.exists(path))
    {
      return entities;
    }
    
  }
  
  
  IEBPFile* file = (_storageType == StorageType::SPIFFS_TYPE ? context->getLittleFS() : context->getSD())->open(path, "r");
  if (!file) {
    context->getErrorHandler()->handleError(ErrorType::FileOpenError);
    return entities;
  }
  while (file->available()) {
    String str = file->readStringUntil('\n');
    T entity{};
    entity.fromString(str);
    bool matches = true;
    int pos = 0;
    while (pos < query.length()) {
      int and_pos = query.indexOf(" AND ", pos);
      if (and_pos == -1) {
        and_pos = query.length();
      }
      String condition = query.substring(pos, and_pos);
      int operator_pos = -1;
      if (condition.indexOf('=') != -1) {
        operator_pos = condition.indexOf('=');
      } else if (condition.indexOf('>') != -1) {
        operator_pos = condition.indexOf('>');
      } else if (condition.indexOf('<') != -1) {
        operator_pos = condition.indexOf('<');
      }

      if (operator_pos == -1) {
        context->getErrorHandler()->handleError(ErrorType::InvalidQuery);
        matches = false;
        break;
      }

      String column_name = condition.substring(0, operator_pos);
      if (!context->getValidation()->isColumnNameValid(column_name)) {
        context->getErrorHandler()->handleError(ErrorType::InvalidQuery);
        matches = false;
        break;
      }

      String value = condition.substring(operator_pos + 1);
      String entity_value = entity.GetValue(column_name);
      if (condition[operator_pos] == '=') {
        if (entity_value != value) {
          matches = false;
          break;
        }
      } else if (condition[operator_pos] == '>') {
        if (entity_value <= value) {
          matches = false;
          break;
        }
      } else if (condition[operator_pos] == '<') {
        if (entity_value >= value) {
          matches = false;
          break;
        }
      }
      pos = and_pos + 5;
    }

    if (matches) {
      entities.push_back(entity);
    }
  }
  file->close();
  return entities;
}
};
#endif
