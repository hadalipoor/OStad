#ifndef RELAYENTITY_H
#define RELAYENTITY_H

#include "..\Entity.h"

class RelayEntity : public Entity {
public:
    static const String COLUMN_NORMALLY_OPEN;
    static const String COLUMN_PIN_NUMBER;
    static const String COLUMN_MODULE_ID;

private:
    int moduleId;
    int pinNumber;
    bool normallyOpen;

public:
    RelayEntity() : Entity(), moduleId(0), pinNumber(0), normallyOpen(false) {}

    RelayEntity(int id, int pinNumber, int moduleId, bool normallyOpen) : Entity() {
        this->id = id;
        this->moduleId = moduleId;
        this->pinNumber = pinNumber;
        this->normallyOpen = normallyOpen;
        SetValue(COLUMN_MODULE_ID, String(this->moduleId));
        SetValue(COLUMN_PIN_NUMBER, String(this->pinNumber));
        SetValue(COLUMN_NORMALLY_OPEN, String(this->normallyOpen));
    }

    RelayEntity(int moduleId, int pinNumber, bool normallyOpen) : 
        RelayEntity(0, pinNumber, moduleId, normallyOpen) {}

    static RelayEntity fromEntity(Entity entity) {
        RelayEntity relayEntity = RelayEntity();
        relayEntity.fromString(entity.toString());
        return relayEntity;
    }

    // Getters
    int getModuleId() {
        moduleId = GetValue(COLUMN_MODULE_ID).toInt();
        return moduleId;
    }

    int getPinNumber() {
        pinNumber = GetValue(COLUMN_PIN_NUMBER).toInt();
        return pinNumber;
    }

    bool getNormallyOpen() {
        normallyOpen = GetValue(COLUMN_NORMALLY_OPEN) == "true";
        return normallyOpen;
    }

    // Setters
    void setModuleId(int value) {
        moduleId = value;
        SetValue(COLUMN_MODULE_ID, String(moduleId));
    }

    void setPinNumber(int value) {
        pinNumber = value;
        SetValue(COLUMN_PIN_NUMBER, String(pinNumber));
    }

    void setNormallyOpen(bool value) {
        normallyOpen = value;
        SetValue(COLUMN_NORMALLY_OPEN, String(normallyOpen));
    }

};

const String RelayEntity::COLUMN_MODULE_ID = "ModuleId";
const String RelayEntity::COLUMN_PIN_NUMBER = "PinNumber";
const String RelayEntity::COLUMN_NORMALLY_OPEN = "NormallyOpen";

#endif // RELAYENTITY_H
