#ifndef HUMIDITYCONDITIONENTITY_H
#define HUMIDITYCONDITIONENTITY_H

#include <OStad.h>

class HumidityConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MINHUMIDITY;
    static const String COLUMN_MAXHUMIDITY;
    static const String COLUMN_LOWHUMIDITYALERTTHRESHOLD;
    static const String COLUMN_HIGHHUMIDITYALERTTHRESHOLD;
    

    String Name;
    int MinHumidity;
    int MaxHumidity;
    int LowHumidityAlertThreshold;
    int HighHumidityAlertThreshold;
    

    HumidityConditionEntity()  : Entity(){}

    HumidityConditionEntity(int id, String _Name, int _MinHumidity, int _MaxHumidity, int _LowHumidityAlertThreshold, int _HighHumidityAlertThreshold) : Entity() {
        this->id = id;
        Name = _Name;
        MinHumidity = _MinHumidity;
        MaxHumidity = _MaxHumidity;
        LowHumidityAlertThreshold = _LowHumidityAlertThreshold;
        HighHumidityAlertThreshold = _HighHumidityAlertThreshold;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_MINHUMIDITY, String(MinHumidity), "int");
        addColumn(COLUMN_MAXHUMIDITY, String(MaxHumidity), "int");
        addColumn(COLUMN_LOWHUMIDITYALERTTHRESHOLD, String(LowHumidityAlertThreshold), "int");
        addColumn(COLUMN_HIGHHUMIDITYALERTTHRESHOLD, String(HighHumidityAlertThreshold), "int");
        
    }

    HumidityConditionEntity(String _Name, int _MinHumidity, int _MaxHumidity, int _LowHumidityAlertThreshold, int _HighHumidityAlertThreshold) : 
        HumidityConditionEntity(0, _Name, _MinHumidity, _MaxHumidity, _LowHumidityAlertThreshold, _HighHumidityAlertThreshold)  {}

    static HumidityConditionEntity fromEntity(Entity entity)
    {
        HumidityConditionEntity humidityconditionentity = HumidityConditionEntity();
        humidityconditionentity.fromString(entity.toString());
        return humidityconditionentity;
    }

    // Setters and Getters for each field
};

const String HumidityConditionEntity::COLUMN_NAME = "Name";
const String HumidityConditionEntity::COLUMN_MINHUMIDITY = "MinHumidity";
const String HumidityConditionEntity::COLUMN_MAXHUMIDITY = "MaxHumidity";
const String HumidityConditionEntity::COLUMN_LOWHUMIDITYALERTTHRESHOLD = "LowHumidityAlertThreshold";
const String HumidityConditionEntity::COLUMN_HIGHHUMIDITYALERTTHRESHOLD = "HighHumidityAlertThreshold";


#endif // HUMIDITYCONDITIONENTITY_H