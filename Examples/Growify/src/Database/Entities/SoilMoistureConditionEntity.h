#ifndef SOILMOISTURECONDITIONENTITY_H
#define SOILMOISTURECONDITIONENTITY_H

#include <OStad.h>

class SoilMoistureConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MINSOILMOISTURE;
    static const String COLUMN_MAXSOILMOISTURE;
    static const String COLUMN_LOWSOILMOISTUREALERTTHRESHOLD;
    static const String COLUMN_HIGHSOILMOISTUREALERTTHRESHOLD;
    

    String Name;
    int MinSoilMoisture;
    int MaxSoilMoisture;
    int LowSoilMoistureAlertThreshold;
    int HighSoilMoistureAlertThreshold;
    

    SoilMoistureConditionEntity()  : Entity(){}

    SoilMoistureConditionEntity(int id, String _Name, int _MinSoilMoisture, int _MaxSoilMoisture, int _LowSoilMoistureAlertThreshold, int _HighSoilMoistureAlertThreshold) : Entity() {
        this->id = id;
        Name = _Name;
        MinSoilMoisture = _MinSoilMoisture;
        MaxSoilMoisture = _MaxSoilMoisture;
        LowSoilMoistureAlertThreshold = _LowSoilMoistureAlertThreshold;
        HighSoilMoistureAlertThreshold = _HighSoilMoistureAlertThreshold;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_MINSOILMOISTURE, String(MinSoilMoisture), "int");
        addColumn(COLUMN_MAXSOILMOISTURE, String(MaxSoilMoisture), "int");
        addColumn(COLUMN_LOWSOILMOISTUREALERTTHRESHOLD, String(LowSoilMoistureAlertThreshold), "int");
        addColumn(COLUMN_HIGHSOILMOISTUREALERTTHRESHOLD, String(HighSoilMoistureAlertThreshold), "int");
        
    }

    SoilMoistureConditionEntity(String _Name, int _MinSoilMoisture, int _MaxSoilMoisture, int _LowSoilMoistureAlertThreshold, int _HighSoilMoistureAlertThreshold) : 
        SoilMoistureConditionEntity(0, _Name, _MinSoilMoisture, _MaxSoilMoisture, _LowSoilMoistureAlertThreshold, _HighSoilMoistureAlertThreshold)  {}

    static SoilMoistureConditionEntity fromEntity(Entity entity)
    {
        SoilMoistureConditionEntity soilmoistureconditionentity = SoilMoistureConditionEntity();
        soilmoistureconditionentity.fromString(entity.toString());
        return soilmoistureconditionentity;
    }

    // Setters and Getters for each field
};

const String SoilMoistureConditionEntity::COLUMN_NAME = "Name";
const String SoilMoistureConditionEntity::COLUMN_MINSOILMOISTURE = "MinSoilMoisture";
const String SoilMoistureConditionEntity::COLUMN_MAXSOILMOISTURE = "MaxSoilMoisture";
const String SoilMoistureConditionEntity::COLUMN_LOWSOILMOISTUREALERTTHRESHOLD = "LowSoilMoistureAlertThreshold";
const String SoilMoistureConditionEntity::COLUMN_HIGHSOILMOISTUREALERTTHRESHOLD = "HighSoilMoistureAlertThreshold";


#endif // SOILMOISTURECONDITIONENTITY_H