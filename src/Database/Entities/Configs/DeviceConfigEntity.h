
#ifndef DEVICECONFIGENTITY_H
#define DEVICECONFIGENTITY_H

#include "../Entity.h"

class DeviceConfigEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;

    String key;
    String value;

    DeviceConfigEntity() : Entity() {}

    DeviceConfigEntity(int id, const String &_key, const String &_value) : Entity() {
        this->id = id;
        key = _key;
        value = _value;
        addColumn(COLUMN_KEY, key, "string");
        addColumn(COLUMN_VALUE, value, "string");
        
        SetValue(COLUMN_KEY, key);
        SetValue(COLUMN_VALUE, value);
    }

    DeviceConfigEntity(const String &_key, const String &_value) : DeviceConfigEntity(0, _key, _value) {}

    static DeviceConfigEntity fromEntity(Entity entity)
    {
        DeviceConfigEntity systemConfigEntity = DeviceConfigEntity();
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

const String DeviceConfigEntity::COLUMN_KEY = "key";
const String DeviceConfigEntity::COLUMN_VALUE = "value";

#endif // DEVICETESTENTITY_H

