#ifndef IENTITY_H
#define IENTITY_H

#include <vector>
#include <ArduinoJson.h>
#include "../../Clock/EBPDateTime.h"

struct Column {
  String name;
  String type;
  String value;
};

class IEntity {
  public:
    virtual String GetValue(String column_name);
    virtual void SetValue(String column_name, String value);
    virtual String toString();
    virtual String toJson();
    virtual void fromString(String str);
    virtual void addColumn(String column_name, String value, String type);
    virtual void removeColumn(String column_name);
    virtual IEntity toEntity() const;
};

#endif //IENTITY_H