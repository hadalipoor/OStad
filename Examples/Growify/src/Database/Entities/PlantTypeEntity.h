#ifndef PLANTTYPEENTITY_H
#define PLANTTYPEENTITY_H

#include <OStad.h>

class PlantTypeEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_GREENHOUSEID;
    

    String Name;
    int GreenhouseId;
    

    PlantTypeEntity()  : Entity(){}

    PlantTypeEntity(int id, String _Name, int _GreenhouseId) : Entity() {
        this->id = id;
        Name = _Name;
        GreenhouseId = _GreenhouseId;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        
    }

    PlantTypeEntity(String _Name, int _GreenhouseId) : 
        PlantTypeEntity(0, _Name, _GreenhouseId)  {}

    static PlantTypeEntity fromEntity(Entity entity)
    {
        PlantTypeEntity planttypeentity = PlantTypeEntity();
        planttypeentity.fromString(entity.toString());
        return planttypeentity;
    }

    // Setters and Getters for each field
};

const String PlantTypeEntity::COLUMN_NAME = "Name";
const String PlantTypeEntity::COLUMN_GREENHOUSEID = "GreenhouseId";


#endif // PLANTTYPEENTITY_H