#ifndef DHTENTITY_H
#define DHTENTITY_H

#include "..\Entity.h"

class DHTEntity : public Entity {
public:
    static const String COLUMN_TYPE;
    static const String COLUMN_DRY_TRESHOLD;
    static const String COLUMN_WET_TRESHOLD;
    static const String COLUMN_COOL_TRESHOLD;
    static const String COLUMN_HOT_TRESHOLD;

    String Type;
    int DryTreshold;
    int WetTreshold;
    int CoolTreshold;
    int HotTreshold;

    DHTEntity() : Entity() {}

    DHTEntity(int id, const String &_Type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold) : Entity() {
        this->id = id;
        Type = _Type;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        CoolTreshold = coolTreshold;
        HotTreshold = hotTreshold;
        addColumn(COLUMN_TYPE, Type, "string");
        addColumn(COLUMN_DRY_TRESHOLD, String(DryTreshold), "int");
        addColumn(COLUMN_WET_TRESHOLD, String(WetTreshold), "int");
        addColumn(COLUMN_COOL_TRESHOLD, String(CoolTreshold), "int");
        addColumn(COLUMN_HOT_TRESHOLD, String(HotTreshold), "int");
    }

    DHTEntity(const String &_Type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold) : 
        DHTEntity(0, _Type, dryTreshold, wetTreshold, coolTreshold, hotTreshold) {}

    static DHTEntity fromEntity(Entity entity)
    {
        DHTEntity dhtEntity = DHTEntity();
        dhtEntity.fromString(entity.toString());
        return dhtEntity;
    }

    // Setters and Getters for each field
};

const String DHTEntity::COLUMN_TYPE = "Type";
const String DHTEntity::COLUMN_DRY_TRESHOLD = "DryTreshold";
const String DHTEntity::COLUMN_WET_TRESHOLD = "WetTreshold";
const String DHTEntity::COLUMN_COOL_TRESHOLD = "CoolTreshold";
const String DHTEntity::COLUMN_HOT_TRESHOLD = "HotTreshold";

#endif // DHTENTITY_H
