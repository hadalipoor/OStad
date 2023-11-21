#ifndef SOILMOISTURELOGENTITY_H
#define SOILMOISTURELOGENTITY_H

#include <OStad.h>

class SoilMoistureLogEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_SOILMOISTUREREADING;
    static const String COLUMN_WATERPUMPSTATE;
    

    int GreenhouseId;
    int SoilMoistureReading;
    String WaterPumpState;
    

    SoilMoistureLogEntity()  : Entity(){}

    SoilMoistureLogEntity(int id, int _GreenhouseId, int _SoilMoistureReading, String _WaterPumpState) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        SoilMoistureReading = _SoilMoistureReading;
        WaterPumpState = _WaterPumpState;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_SOILMOISTUREREADING, String(SoilMoistureReading), "int");
        addColumn(COLUMN_WATERPUMPSTATE, String(WaterPumpState), "String");
        
    }

    SoilMoistureLogEntity(int _GreenhouseId, int _SoilMoistureReading, String _WaterPumpState) : 
        SoilMoistureLogEntity(0, _GreenhouseId, _SoilMoistureReading, _WaterPumpState)  {}

    static SoilMoistureLogEntity fromEntity(Entity entity)
    {
        SoilMoistureLogEntity soilmoisturelogentity = SoilMoistureLogEntity();
        soilmoisturelogentity.fromString(entity.toString());
        return soilmoisturelogentity;
    }

    // Setters and Getters for each field
};

const String SoilMoistureLogEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String SoilMoistureLogEntity::COLUMN_SOILMOISTUREREADING = "SoilMoistureReading";
const String SoilMoistureLogEntity::COLUMN_WATERPUMPSTATE = "WaterPumpState";


#endif // SOILMOISTURELOGENTITY_H