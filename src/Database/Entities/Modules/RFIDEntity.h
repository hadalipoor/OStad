#ifndef RFIDENTITY_H
#define RFIDENTITY_H

#include "..\Entity.h"

class RFIDEntity : public Entity {
public:
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_MODULE_PIN2;

    int ModuleId;
    int Pin2;

    RFIDEntity() : Entity() {}

    RFIDEntity(int id, int moduleId, int pin2) : Entity() {
        this->id = id;
        ModuleId = moduleId;
        Pin2 = pin2;
        addColumn(COLUMN_MODULE_ID, String(ModuleId), "int");
        addColumn(COLUMN_MODULE_PIN2, String(Pin2), "int");
    }

    RFIDEntity(int moduleId, int pin2) : 
        RFIDEntity(0, moduleId, pin2) {}

    static RFIDEntity fromEntity(Entity entity)
    {
        RFIDEntity relayEntity = RFIDEntity();
        relayEntity.fromString(entity.toString());
        return relayEntity;
    }

    // Setters and Getters for each field
};

const String RFIDEntity::COLUMN_MODULE_ID = "ModuleId";
const String RFIDEntity::COLUMN_MODULE_PIN2 = "Pin2";

#endif // RFIDENTITY_H
