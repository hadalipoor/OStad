#ifndef SOILMOISTUREENTITY_H
#define SOILMOISTUREENTITY_H

#include "..\Entity.h"

class SoilMoistureEntity : public Entity {
public:
    static const String COLUMN_DRY_TRESHOLD;
    static const String COLUMN_WET_TRESHOLD;
    static const String COLUMN_TYPE;

    int DryTreshold;
    int WetTreshold;
    String Type;

    SoilMoistureEntity() : Entity() {}

    SoilMoistureEntity(int id, int dryTreshold, int wetTreshold, const String &_Type) : Entity() {
        this->id = id;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        Type = _Type;
        addColumn(COLUMN_DRY_TRESHOLD, String(DryTreshold), "int");
        addColumn(COLUMN_WET_TRESHOLD, String(WetTreshold), "int");
        addColumn(COLUMN_TYPE, Type, "string");
    }

    SoilMoistureEntity(int dryTreshold, int wetTreshold, const String &_Type) : 
        SoilMoistureEntity(0, dryTreshold, wetTreshold, _Type) {}

    static SoilMoistureEntity fromEntity(Entity entity)
    {
        SoilMoistureEntity soilMoistureEntity = SoilMoistureEntity();
        soilMoistureEntity.fromString(entity.toString());
        return soilMoistureEntity;
    }

    // Setters and Getters for each field
};

const String SoilMoistureEntity::COLUMN_DRY_TRESHOLD = "DryTreshold";
const String SoilMoistureEntity::COLUMN_WET_TRESHOLD = "WetTreshold";
const String SoilMoistureEntity::COLUMN_TYPE = "Type";

#endif // SOILMOISTUREENTITY_H
