#ifndef GREENHOUSEENTITY_H
#define GREENHOUSEENTITY_H

#include <OStad.h>

class GreenhouseEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_CONDITIONID;
    

    String Name;
    int ConditionId;
    

    GreenhouseEntity()  : Entity(){}

    GreenhouseEntity(int id, String _Name, int _ConditionId) : Entity() {
        this->id = id;
        Name = _Name;
        ConditionId = _ConditionId;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_CONDITIONID, String(ConditionId), "int");
        
    }

    GreenhouseEntity(String _Name, int _ConditionId) : 
        GreenhouseEntity(0, _Name, _ConditionId)  {}

    static GreenhouseEntity fromEntity(Entity entity)
    {
        GreenhouseEntity greenhouseentity = GreenhouseEntity();
        greenhouseentity.fromString(entity.toString());
        return greenhouseentity;
    }

    // Setters and Getters for each field
};

const String GreenhouseEntity::COLUMN_NAME = "Name";
const String GreenhouseEntity::COLUMN_CONDITIONID = "ConditionId";


#endif // GREENHOUSEENTITY_H