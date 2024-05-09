#ifndef SOILMOISTUREENTITY_H
#define SOILMOISTUREENTITY_H

#include "..\Entity.h"

class SoilMoistureEntity : public Entity {
public:
    static const String COLUMN_DRY_TRESHOLD;
    static const String COLUMN_WET_TRESHOLD;
    static const String COLUMN_TYPE;

private:
    int dryTreshold;
    int wetTreshold;
    String type;

public:
    SoilMoistureEntity() : Entity(), dryTreshold(0), wetTreshold(0), type("") {}

    SoilMoistureEntity(int id, int dryTreshold, int wetTreshold, const String &_Type) : Entity() {
        this->id = id;
        this->dryTreshold = dryTreshold;
        this->wetTreshold = wetTreshold;
        this->type = _Type;
        SetValue(COLUMN_DRY_TRESHOLD, String(this->dryTreshold));
        SetValue(COLUMN_WET_TRESHOLD, String(this->wetTreshold));
        SetValue(COLUMN_TYPE, this->type);
    }

    SoilMoistureEntity(int dryTreshold, int wetTreshold, const String &_Type) : 
        SoilMoistureEntity(0, dryTreshold, wetTreshold, _Type) {}

    static SoilMoistureEntity fromEntity(Entity entity) {
        SoilMoistureEntity soilMoistureEntity = SoilMoistureEntity();
        soilMoistureEntity.fromString(entity.toString());
        return soilMoistureEntity;
    }

    // Getters
    int getDryTreshold() {
        dryTreshold = GetValue(COLUMN_DRY_TRESHOLD).toInt();
        return dryTreshold;
    }

    int getWetTreshold() {
        wetTreshold = GetValue(COLUMN_WET_TRESHOLD).toInt();
        return wetTreshold;
    }

    String getType() {
        type = GetValue(COLUMN_TYPE);
        return type;
    }

    // Setters
    void setDryTreshold(int value) {
        dryTreshold = value;
        SetValue(COLUMN_DRY_TRESHOLD, String(dryTreshold));
    }

    void setWetTreshold(int value) {
        wetTreshold = value;
        SetValue(COLUMN_WET_TRESHOLD, String(wetTreshold));
    }

    void setType(const String &value) {
        type = value;
        SetValue(COLUMN_TYPE, type);
    }

};

const String SoilMoistureEntity::COLUMN_DRY_TRESHOLD = "DryTreshold";
const String SoilMoistureEntity::COLUMN_WET_TRESHOLD = "WetTreshold";
const String SoilMoistureEntity::COLUMN_TYPE = "Type";

#endif // SOILMOISTUREENTITY_H
