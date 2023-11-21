#ifndef RELAYENTITY_H
#define RELAYENTITY_H

#include "..\Entity.h"

class RelayEntity : public Entity {
public:
    static const String COLUMN_NORMALLY_OPEN;
    static const String COLUMN_MODULE_ID;

    int ModuleId;
    bool NormallyOpen;

    RelayEntity() : Entity() {}

    RelayEntity(int id, int moduleId, bool normallyOpen) : Entity() {
        this->id = id;
        ModuleId = moduleId;
        NormallyOpen = normallyOpen;
        addColumn(COLUMN_MODULE_ID, String(ModuleId), "int");
        addColumn(COLUMN_NORMALLY_OPEN, String(NormallyOpen), "bool");
    }

    RelayEntity(int moduleId, bool normallyOpen) : 
        RelayEntity(0, moduleId, normallyOpen) {}

    static RelayEntity fromEntity(Entity entity)
    {
        RelayEntity relayEntity = RelayEntity();
        relayEntity.fromString(entity.toString());
        return relayEntity;
    }

    // Setters and Getters for each field
};

const String RelayEntity::COLUMN_MODULE_ID = "ModuleId";
const String RelayEntity::COLUMN_NORMALLY_OPEN = "NormallyOpen";

#endif // RELAYENTITY_H
