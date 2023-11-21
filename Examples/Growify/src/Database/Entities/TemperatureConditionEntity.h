#ifndef TEMPERATURECONDITIONENTITY_H
#define TEMPERATURECONDITIONENTITY_H

#include <OStad.h>

class TemperatureConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MINTEMPERATURE;
    static const String COLUMN_MAXTEMPERATURE;
    static const String COLUMN_LOWTEMPALERTTHRESHOLD;
    static const String COLUMN_HIGHTEMPALERTTHRESHOLD;
    

    String Name;
    int MinTemperature;
    int MaxTemperature;
    int LowTempAlertThreshold;
    int HighTempAlertThreshold;
    

    TemperatureConditionEntity()  : Entity(){}

    TemperatureConditionEntity(int id, String _Name, int _MinTemperature, int _MaxTemperature, int _LowTempAlertThreshold, int _HighTempAlertThreshold) : Entity() {
        this->id = id;
        Name = _Name;
        MinTemperature = _MinTemperature;
        MaxTemperature = _MaxTemperature;
        LowTempAlertThreshold = _LowTempAlertThreshold;
        HighTempAlertThreshold = _HighTempAlertThreshold;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_MINTEMPERATURE, String(MinTemperature), "int");
        addColumn(COLUMN_MAXTEMPERATURE, String(MaxTemperature), "int");
        addColumn(COLUMN_LOWTEMPALERTTHRESHOLD, String(LowTempAlertThreshold), "int");
        addColumn(COLUMN_HIGHTEMPALERTTHRESHOLD, String(HighTempAlertThreshold), "int");
        
    }

    TemperatureConditionEntity(String _Name, int _MinTemperature, int _MaxTemperature, int _LowTempAlertThreshold, int _HighTempAlertThreshold) : 
        TemperatureConditionEntity(0, _Name, _MinTemperature, _MaxTemperature, _LowTempAlertThreshold, _HighTempAlertThreshold)  {}

    static TemperatureConditionEntity fromEntity(Entity entity)
    {
        TemperatureConditionEntity temperatureconditionentity = TemperatureConditionEntity();
        temperatureconditionentity.fromString(entity.toString());
        return temperatureconditionentity;
    }

    // Setters and Getters for each field
};

const String TemperatureConditionEntity::COLUMN_NAME = "Name";
const String TemperatureConditionEntity::COLUMN_MINTEMPERATURE = "MinTemperature";
const String TemperatureConditionEntity::COLUMN_MAXTEMPERATURE = "MaxTemperature";
const String TemperatureConditionEntity::COLUMN_LOWTEMPALERTTHRESHOLD = "LowTempAlertThreshold";
const String TemperatureConditionEntity::COLUMN_HIGHTEMPALERTTHRESHOLD = "HighTempAlertThreshold";


#endif // TEMPERATURECONDITIONENTITY_H