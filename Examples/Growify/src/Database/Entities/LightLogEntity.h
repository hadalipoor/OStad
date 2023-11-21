#ifndef LIGHTLOGENTITY_H
#define LIGHTLOGENTITY_H

#include <OStad.h>

class LightLogEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_LIGHTINTENSITYREADING;
    static const String COLUMN_LIGHTSTATE;
    

    int GreenhouseId;
    int LightIntensityReading;
    String LightState;
    

    LightLogEntity()  : Entity(){}

    LightLogEntity(int id, int _GreenhouseId, int _LightIntensityReading, String _LightState) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        LightIntensityReading = _LightIntensityReading;
        LightState = _LightState;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_LIGHTINTENSITYREADING, String(LightIntensityReading), "int");
        addColumn(COLUMN_LIGHTSTATE, String(LightState), "String");
        
    }

    LightLogEntity(int _GreenhouseId, int _LightIntensityReading, String _LightState) : 
        LightLogEntity(0, _GreenhouseId, _LightIntensityReading, _LightState)  {}

    static LightLogEntity fromEntity(Entity entity)
    {
        LightLogEntity lightlogentity = LightLogEntity();
        lightlogentity.fromString(entity.toString());
        return lightlogentity;
    }

    // Setters and Getters for each field
};

const String LightLogEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String LightLogEntity::COLUMN_LIGHTINTENSITYREADING = "LightIntensityReading";
const String LightLogEntity::COLUMN_LIGHTSTATE = "LightState";


#endif // LIGHTLOGENTITY_H