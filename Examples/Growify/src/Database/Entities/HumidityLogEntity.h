#ifndef HUMIDITYLOGENTITY_H
#define HUMIDITYLOGENTITY_H

#include <OStad.h>

class HumidityLogEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_HUMIDITYREADING;
    static const String COLUMN_DRYERSTATE;
    static const String COLUMN_HUMIDIFIERSTATE;
    

    int GreenhouseId;
    int HumidityReading;
    String DryerState;
    String HumidifierState;
    

    HumidityLogEntity()  : Entity(){}

    HumidityLogEntity(int id, int _GreenhouseId, int _HumidityReading, String _DryerState, String _HumidifierState) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        HumidityReading = _HumidityReading;
        DryerState = _DryerState;
        HumidifierState = _HumidifierState;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_HUMIDITYREADING, String(HumidityReading), "int");
        addColumn(COLUMN_DRYERSTATE, String(DryerState), "String");
        addColumn(COLUMN_HUMIDIFIERSTATE, String(HumidifierState), "String");
        
    }

    HumidityLogEntity(int _GreenhouseId, int _HumidityReading, String _DryerState, String _HumidifierState) : 
        HumidityLogEntity(0, _GreenhouseId, _HumidityReading, _DryerState, _HumidifierState)  {}

    static HumidityLogEntity fromEntity(Entity entity)
    {
        HumidityLogEntity humiditylogentity = HumidityLogEntity();
        humiditylogentity.fromString(entity.toString());
        return humiditylogentity;
    }

    // Setters and Getters for each field
};

const String HumidityLogEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String HumidityLogEntity::COLUMN_HUMIDITYREADING = "HumidityReading";
const String HumidityLogEntity::COLUMN_DRYERSTATE = "DryerState";
const String HumidityLogEntity::COLUMN_HUMIDIFIERSTATE = "HumidifierState";


#endif // HUMIDITYLOGENTITY_H