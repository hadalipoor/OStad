#ifndef RFIDENTITY_H
#define RFIDENTITY_H

#include "..\Entity.h"

class RFIDEntity : public Entity {
public:
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_MODULE_PIN2;

private:
    int moduleId;
    int pin2;

public:
    RFIDEntity() : Entity(), moduleId(0), pin2(0) {}

    RFIDEntity(int id, int moduleId, int pin2) : Entity() {
        this->id = id;
        this->moduleId = moduleId;
        this->pin2 = pin2;
        SetValue(COLUMN_MODULE_ID, String(this->moduleId));
        SetValue(COLUMN_MODULE_PIN2, String(this->pin2));
    }

    RFIDEntity(int moduleId, int pin2) : 
        RFIDEntity(0, moduleId, pin2) {}

    static RFIDEntity fromEntity(Entity entity) {
        RFIDEntity rfidEntity = RFIDEntity();
        rfidEntity.fromString(entity.toString());
        return rfidEntity;
    }

    // Getters
    int getModuleId() {
        moduleId = GetValue(COLUMN_MODULE_ID).toInt();
        return moduleId;
    }

    int getPin2() {
        pin2 = GetValue(COLUMN_MODULE_PIN2).toInt();
        return pin2;
    }

    // Setters
    void setModuleId(int value) {
        moduleId = value;
        SetValue(COLUMN_MODULE_ID, String(moduleId));
    }

    void setPin2(int value) {
        pin2 = value;
        SetValue(COLUMN_MODULE_PIN2, String(pin2));
    }

};

const String RFIDEntity::COLUMN_MODULE_ID = "ModuleId";
const String RFIDEntity::COLUMN_MODULE_PIN2 = "Pin2";

#endif // RFIDENTITY_H
