#ifndef GREENHOUSECONTROLENTITY_H
#define GREENHOUSECONTROLENTITY_H

#include <OStad.h>

class GreenhouseControlEntity : public Entity {
public:
    static const String COLUMN_GREENHOUSEID;
    static const String COLUMN_CONTROLMODULEID;
    static const String COLUMN_ROLE;
    

    int GreenhouseId;
    int ControlModuleId;
    String Role;
    

    GreenhouseControlEntity()  : Entity(){}

    GreenhouseControlEntity(int id, int _GreenhouseId, int _ControlModuleId, String _Role) : Entity() {
        this->id = id;
        GreenhouseId = _GreenhouseId;
        ControlModuleId = _ControlModuleId;
        Role = _Role;
        

        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        addColumn(COLUMN_CONTROLMODULEID, String(ControlModuleId), "int");
        addColumn(COLUMN_ROLE, String(Role), "String");
        
    }

    GreenhouseControlEntity(int _GreenhouseId, int _ControlModuleId, String _Role) : 
        GreenhouseControlEntity(0, _GreenhouseId, _ControlModuleId, _Role)  {}

    static GreenhouseControlEntity fromEntity(Entity entity)
    {
        GreenhouseControlEntity greenhousecontrolentity = GreenhouseControlEntity();
        greenhousecontrolentity.fromString(entity.toString());
        return greenhousecontrolentity;
    }

    // Setters and Getters for each field
};

const String GreenhouseControlEntity::COLUMN_GREENHOUSEID = "GreenhouseId";
const String GreenhouseControlEntity::COLUMN_CONTROLMODULEID = "ControlModuleId";
const String GreenhouseControlEntity::COLUMN_ROLE = "Role";


#endif // GREENHOUSECONTROLENTITY_H