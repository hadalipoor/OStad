#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <ArduinoJson.h>
#include "../../Clock/EBPDateTime.h"

struct Column {
  String name;
  String type;
  String value;
};

class Entity {
  public:
    int id = -1;
    bool isValid = true;
    EBPDateTime createDate;
    
    Entity() 
    {
      createDate = EBPDateTime(2000,1,1,0,0,0);
    }
    
    Entity(String &str) :Entity(){
      fromString(str);
    }
    static Entity Invalid() {
      Entity invalidEntity;
      invalidEntity.isValid = false;
      return invalidEntity;
    }
    std::vector<Column> _columns;
    String GetValue(String column_name);
    void SetValue(String column_name, String value);
    String toString();
    String toJson();
    void fromString(String str);
    void addColumn(String column_name, String value, String type);
    void removeColumn(String column_name);
    Entity toEntity() const;

};


Entity Entity::toEntity() const 
{
  Entity newEntity;
  newEntity.id = this->id;
  newEntity.isValid = this->isValid;
  newEntity._columns = this->_columns;
  newEntity.createDate = this->createDate;
  return newEntity;
}

void Entity::removeColumn(String column_name) {
  for (int i = 0; i < _columns.size(); i++) {
    if (_columns[i].name == column_name) {
      _columns.erase(_columns.begin() + i);
      return;
    }
  }
}

String Entity::GetValue(String column_name) {
  for (int i = 0; i < _columns.size(); i++) {
    if (_columns[i].name == column_name) {
      return _columns[i].value;
    }
  }
  return "";
}

void Entity::SetValue(String column_name, String value) {
  for (int i = 0; i < _columns.size(); i++) {
    if (_columns[i].name == column_name) {
      _columns[i].value = value;
      return;
    }
  }
  _columns.push_back({column_name, "string", value});
}

String Entity::toString() {

  String str = String(id) + ",";
  for (int i = 0; i < _columns.size(); i++) {
    str += _columns[i].name + "=" + _columns[i].value + ",";
  }
  str += createDate.toDateTimeString();
  return str;
}


void Entity::fromString(String str) {
  int index = str.indexOf(",");
  id = str.substring(0, index).toInt();
  str = str.substring(index + 1);
  while (str.length() > 0) {
      index = str.indexOf("=");
      String name = str.substring(0, index);
      str = str.substring(index + 1);
      index = str.indexOf(",");
      if (index < 0) {
          index = str.length();
      }
      String value = str.substring(0, index);
      name.trim();
      if(name.length() > 0) {
          if(str.indexOf(",") < 0 && str.indexOf("=") < 0) { // This is the last element and no more columns exist
              createDate.fromString(value);
          }
          else {
              SetValue(name, value);
          }
      }
      str = str.substring(index + 1);
  }
}


void Entity::addColumn(String column_name, String value, String type) {
  // if (!Validation::isColumnNameValid(column_name)) {
  //   ErrorHandler::handleError(ErrorHandler::CustomError, "Invalid column name: " + column_name);
  //   return;
  // }

  for (int i = 0; i < _columns.size(); i++) {
    if (_columns[i].name == column_name) {
      // ErrorHandler::handleError(ErrorHandler::CustomError, "Column name already exists: " + column_name);
      return;
    }
  }
  _columns.push_back({column_name, type, value});
}

String Entity::toJson() {
  DynamicJsonDocument doc(512);
  doc["id"] = id;
  for (int i = 0; i < _columns.size(); i++) {
    doc[_columns[i].name] = _columns[i].value;
  }
  doc["create_date"] = createDate.toDateTimeString();
  String json;
  serializeJson(doc, json);
  doc.clear();
  return json;
}

#endif
