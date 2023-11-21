#ifndef TEMPERATURELOGENTITY_H
#define TEMPERATURELOGENTITY_H

#include <OStad.h>

class TemperatureLogEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_TEMPERATUREREADING;
    static const String COLUMN_COOLERSTATE;
    static const String COLUMN_HEATERSTATE;
    

    int GreenhouseId;
    int TemperatureReading;
    String CoolerState;
    String HeaterState;
    

    TemperatureLogEntity()  : Entity(){}

    TemperatureLogEntity(int id, int _GreenhouseId, int _TemperatureReading, String _CoolerState, String _HeaterState) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        TemperatureReading = _TemperatureReading;
        CoolerState = _CoolerState;
        HeaterState = _HeaterState;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_TEMPERATUREREADING, String(TemperatureReading), "int");
        addColumn(COLUMN_COOLERSTATE, String(CoolerState), "String");
        addColumn(COLUMN_HEATERSTATE, String(HeaterState), "String");
        
    }

    TemperatureLogEntity(int _GreenhouseId, int _TemperatureReading, String _CoolerState, String _HeaterState) : 
        TemperatureLogEntity(0, _GreenhouseId, _TemperatureReading, _CoolerState, _HeaterState)  {}

    static TemperatureLogEntity fromEntity(Entity entity)
    {
        TemperatureLogEntity temperaturelogentity = TemperatureLogEntity();
        temperaturelogentity.fromString(entity.toString());
        return temperaturelogentity;
    }

    // Setters and Getters for each field
};

const String TemperatureLogEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String TemperatureLogEntity::COLUMN_TEMPERATUREREADING = "TemperatureReading";
const String TemperatureLogEntity::COLUMN_COOLERSTATE = "CoolerState";
const String TemperatureLogEntity::COLUMN_HEATERSTATE = "HeaterState";


#endif // TEMPERATURELOGENTITY_H