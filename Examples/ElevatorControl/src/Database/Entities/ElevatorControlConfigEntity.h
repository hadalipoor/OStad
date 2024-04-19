
#ifndef ELEVATORCONTROLENTITY_H
#define ELEVATORCONTROLENTITY_H

#include <OStad.h>

class ElevatorControlConfigEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;

    String key;
    String value;

    ElevatorControlConfigEntity() : Entity() {}

    ElevatorControlConfigEntity(int id, const String &_key, const String &_value) : Entity() {
        this->id = id;
        key = _key;
        value = _value;
        addColumn(COLUMN_KEY, key, "string");
        addColumn(COLUMN_VALUE, value, "string");
    }

    ElevatorControlConfigEntity(const String &_key, const String &_value) : ElevatorControlConfigEntity(0, _key, _value) {}

    static ElevatorControlConfigEntity fromEntity(Entity entity)
    {
        ElevatorControlConfigEntity systemConfigEntity = ElevatorControlConfigEntity();
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

const String ElevatorControlConfigEntity::COLUMN_KEY = "key";
const String ElevatorControlConfigEntity::COLUMN_VALUE = "value";

#endif // ELEVATORCONTROLENTITY_H

