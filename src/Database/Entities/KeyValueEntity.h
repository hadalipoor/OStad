#ifndef SYSTEMCONFIGENTITY_H
#define SYSTEMCONFIGENTITY_H

#include "Entity.h"

class KeyValueEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;

    String key;
    String value;

    KeyValueEntity() : Entity() {}

    KeyValueEntity(int id, const String &_key, const String &_value) : Entity() {
        this->id = id;
        key = _key;
        value = _value;
        addColumn(COLUMN_KEY, key, "string");
        addColumn(COLUMN_VALUE, value, "string");
    }

    KeyValueEntity(const String &_key, const String &_value) : KeyValueEntity(0, _key, _value) {}

    static KeyValueEntity fromEntity(Entity entity)
    {
        KeyValueEntity systemConfigEntity = KeyValueEntity();
        systemConfigEntity.fromString(entity.toString());
        return systemConfigEntity;
    }

    void setKey(const String &_key) {
        key = _key;
        SetValue(COLUMN_KEY, _key);
    }

    String getKey() {
        return GetValue(COLUMN_KEY);
    }

    void setValue(const String &_value) {
        value = _value;
        SetValue(COLUMN_VALUE, _value);
    }

    String getValue() {
        return GetValue(COLUMN_VALUE);
    }
};

const String KeyValueEntity::COLUMN_KEY = "key";
const String KeyValueEntity::COLUMN_VALUE = "value";

#endif // SYSTEMCONFIGENTITY_H
