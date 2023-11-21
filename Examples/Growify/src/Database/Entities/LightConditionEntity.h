#ifndef LIGHTCONDITIONENTITY_H
#define LIGHTCONDITIONENTITY_H

#include <OStad.h>

class LightConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MINLIGHTINTENSITY;
    static const String COLUMN_MAXLIGHTINTENSITY;
    static const String COLUMN_LOWLIGHTINTENSITYALERTTHRESHOLD;
    static const String COLUMN_HIGHLIGHTINTENSITYALERTTHRESHOLD;
    

    String Name;
    int MinLightIntensity;
    int MaxLightIntensity;
    int LowLightIntensityAlertThreshold;
    int HighLightIntensityAlertThreshold;
    

    LightConditionEntity()  : Entity(){}

    LightConditionEntity(int id, String _Name, int _MinLightIntensity, int _MaxLightIntensity, int _LowLightIntensityAlertThreshold, int _HighLightIntensityAlertThreshold) : Entity() {
        this->id = id;
        Name = _Name;
        MinLightIntensity = _MinLightIntensity;
        MaxLightIntensity = _MaxLightIntensity;
        LowLightIntensityAlertThreshold = _LowLightIntensityAlertThreshold;
        HighLightIntensityAlertThreshold = _HighLightIntensityAlertThreshold;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_MINLIGHTINTENSITY, String(MinLightIntensity), "int");
        addColumn(COLUMN_MAXLIGHTINTENSITY, String(MaxLightIntensity), "int");
        addColumn(COLUMN_LOWLIGHTINTENSITYALERTTHRESHOLD, String(LowLightIntensityAlertThreshold), "int");
        addColumn(COLUMN_HIGHLIGHTINTENSITYALERTTHRESHOLD, String(HighLightIntensityAlertThreshold), "int");
        
    }

    LightConditionEntity(String _Name, int _MinLightIntensity, int _MaxLightIntensity, int _LowLightIntensityAlertThreshold, int _HighLightIntensityAlertThreshold) : 
        LightConditionEntity(0, _Name, _MinLightIntensity, _MaxLightIntensity, _LowLightIntensityAlertThreshold, _HighLightIntensityAlertThreshold)  {}

    static LightConditionEntity fromEntity(Entity entity)
    {
        LightConditionEntity lightconditionentity = LightConditionEntity();
        lightconditionentity.fromString(entity.toString());
        return lightconditionentity;
    }

    // Setters and Getters for each field
};

const String LightConditionEntity::COLUMN_NAME = "Name";
const String LightConditionEntity::COLUMN_MINLIGHTINTENSITY = "MinLightIntensity";
const String LightConditionEntity::COLUMN_MAXLIGHTINTENSITY = "MaxLightIntensity";
const String LightConditionEntity::COLUMN_LOWLIGHTINTENSITYALERTTHRESHOLD = "LowLightIntensityAlertThreshold";
const String LightConditionEntity::COLUMN_HIGHLIGHTINTENSITYALERTTHRESHOLD = "HighLightIntensityAlertThreshold";


#endif // LIGHTCONDITIONENTITY_H