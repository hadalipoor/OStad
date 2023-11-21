#ifndef CONDITIONENTITY_H
#define CONDITIONENTITY_H

#include <OStad.h>

class ConditionEntity : public Entity {
public:
    static const String COLUMN_TEMPERATURECONDITIONID;
    static const String COLUMN_HUMIDITYCONDITIONID;
    static const String COLUMN_LIGHTCONDITIONID;
    static const String COLUMN_SOILMOISTURECONDITIONID;
    

    int TemperatureConditionId;
    int HumidityConditionId;
    int LightConditionId;
    int SoilMoistureConditionId;
    

    ConditionEntity()  : Entity(){}

    ConditionEntity(int id, int _TemperatureConditionId, int _HumidityConditionId, int _LightConditionId, int _SoilMoistureConditionId) : Entity() {
        this->id = id;
        TemperatureConditionId = _TemperatureConditionId;
        HumidityConditionId = _HumidityConditionId;
        LightConditionId = _LightConditionId;
        SoilMoistureConditionId = _SoilMoistureConditionId;
        

        addColumn(COLUMN_TEMPERATURECONDITIONID, String(TemperatureConditionId), "int");
        addColumn(COLUMN_HUMIDITYCONDITIONID, String(HumidityConditionId), "int");
        addColumn(COLUMN_LIGHTCONDITIONID, String(LightConditionId), "int");
        addColumn(COLUMN_SOILMOISTURECONDITIONID, String(SoilMoistureConditionId), "int");
        
    }

    ConditionEntity(int _TemperatureConditionId, int _HumidityConditionId, int _LightConditionId, int _SoilMoistureConditionId) : 
        ConditionEntity(0, _TemperatureConditionId, _HumidityConditionId, _LightConditionId, _SoilMoistureConditionId)  {}

    static ConditionEntity fromEntity(Entity entity)
    {
        ConditionEntity conditionentity = ConditionEntity();
        conditionentity.fromString(entity.toString());
        return conditionentity;
    }

    // Setters and Getters for each field
};

const String ConditionEntity::COLUMN_TEMPERATURECONDITIONID = "TemperatureConditionId";
const String ConditionEntity::COLUMN_HUMIDITYCONDITIONID = "HumidityConditionId";
const String ConditionEntity::COLUMN_LIGHTCONDITIONID = "LightConditionId";
const String ConditionEntity::COLUMN_SOILMOISTURECONDITIONID = "SoilMoistureConditionId";


#endif // CONDITIONENTITY_H