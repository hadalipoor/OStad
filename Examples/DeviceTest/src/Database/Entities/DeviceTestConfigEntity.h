
#ifndef DEVICETESTENTITY_H
#define DEVICETESTENTITY_H

#include <OStad.h>

class DeviceTestConfigEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;

    String key;
    String value;

    DeviceTestConfigEntity() : Entity() {}

    DeviceTestConfigEntity(int id, const String &_key, const String &_value) : Entity() {
        this->id = id;
        key = _key;
        value = _value;
        addColumn(COLUMN_KEY, key, "string");
        addColumn(COLUMN_VALUE, value, "string");
    }

    DeviceTestConfigEntity(const String &_key, const String &_value) : DeviceTestConfigEntity(0, _key, _value) {}

    static DeviceTestConfigEntity fromEntity(Entity entity)
    {
        DeviceTestConfigEntity systemConfigEntity = DeviceTestConfigEntity();
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

const String DeviceTestConfigEntity::COLUMN_KEY = "key";
const String DeviceTestConfigEntity::COLUMN_VALUE = "value";

#endif // DEVICETESTENTITY_H

