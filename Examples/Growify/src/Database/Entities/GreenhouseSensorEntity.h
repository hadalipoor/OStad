#ifndef GREENHOUSESENSORENTITY_H
#define GREENHOUSESENSORENTITY_H

#include <OStad.h>

class GreenhouseSensorEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_SENSORMODULEID;
    static const String COLUMN_ROLE;
    

    int GreenhouseId;
    int SensorModuleId;
    String Role;
    

    GreenhouseSensorEntity()  : Entity(){}

    GreenhouseSensorEntity(int id, int _GreenhouseId, int _SensorModuleId, String _Role) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        SensorModuleId = _SensorModuleId;
        Role = _Role;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_SENSORMODULEID, String(SensorModuleId), "int");
        addColumn(COLUMN_ROLE, String(Role), "String");
        
    }

    GreenhouseSensorEntity(int _GreenhouseId, int _SensorModuleId, String _Role) : 
        GreenhouseSensorEntity(0, _GreenhouseId, _SensorModuleId, _Role)  {}

    static GreenhouseSensorEntity fromEntity(Entity entity)
    {
        GreenhouseSensorEntity greenhousesensorentity = GreenhouseSensorEntity();
        greenhousesensorentity.fromString(entity.toString());
        return greenhousesensorentity;
    }

    // Setters and Getters for each field
};

const String GreenhouseSensorEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String GreenhouseSensorEntity::COLUMN_SENSORMODULEID = "SensorModuleId";
const String GreenhouseSensorEntity::COLUMN_ROLE = "Role";


#endif // GREENHOUSESENSORENTITY_H