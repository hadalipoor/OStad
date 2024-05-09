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

private:
    String Type;
    int DryTreshold;
    int WetTreshold;
    int CoolTreshold;
    int HotTreshold;

public:
    DHTEntity() : Entity() {}

    DHTEntity(int id, const String &_Type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold) : Entity() {
        this->id = id;
        Type = _Type;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        CoolTreshold = coolTreshold;
        HotTreshold = hotTreshold;
    }

    DHTEntity(const String &_Type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold):
        DHTEntity(0, _Type, dryTreshold, wetTreshold, coolTreshold, hotTreshold){}
    // Getters
    String getType() {
        Type = GetValue(COLUMN_TYPE);
        return Type;
    }
    int getDryTreshold() {
        DryTreshold = GetValue(COLUMN_DRY_TRESHOLD).toInt();
        return DryTreshold;
    }
    int getWetTreshold() {
        WetTreshold = GetValue(COLUMN_WET_TRESHOLD).toInt();
        return WetTreshold;
    }
    int getCoolTreshold() {
        CoolTreshold = GetValue(COLUMN_COOL_TRESHOLD).toInt();
        return CoolTreshold;
    }
    int getHotTreshold() {
        HotTreshold = GetValue(COLUMN_HOT_TRESHOLD).toInt();
        return HotTreshold;
    }

    // Setters
    void setType(const String& _Type) {
        Type = _Type;
        SetValue(COLUMN_TYPE, Type);
    }
    void setDryTreshold(int _DryTreshold) {
        DryTreshold = _DryTreshold;
        SetValue(COLUMN_DRY_TRESHOLD, String(DryTreshold));
    }
    void setWetTreshold(int _WetTreshold) {
        WetTreshold = _WetTreshold;
        SetValue(COLUMN_WET_TRESHOLD, String(WetTreshold));
    }
    void setCoolTreshold(int _CoolTreshold) {
        CoolTreshold = _CoolTreshold;
        SetValue(COLUMN_COOL_TRESHOLD, String(CoolTreshold));
    }
    void setHotTreshold(int _HotTreshold) {
        HotTreshold = _HotTreshold;
        SetValue(COLUMN_HOT_TRESHOLD, String(HotTreshold));
    }

    static DHTEntity fromEntity(Entity entity)
    {
        DHTEntity dHTEntity = DHTEntity();
        dHTEntity.fromString(entity.toString());
        return dHTEntity;
    }
};

const String DHTEntity::COLUMN_TYPE = "Type";
const String DHTEntity::COLUMN_DRY_TRESHOLD = "DryTreshold";
const String DHTEntity::COLUMN_WET_TRESHOLD = "WetTreshold";
const String DHTEntity::COLUMN_COOL_TRESHOLD = "CoolTreshold";
const String DHTEntity::COLUMN_HOT_TRESHOLD = "HotTreshold";

#endif // DHTENTITY_H
