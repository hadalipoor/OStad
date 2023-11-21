#ifndef PLANTENTITY_H
#define PLANTENTITY_H

#include <OStad.h>

class PlantEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_PLANTTYPEID;
    static const String COLUMN_GREENHOUSEID;
    

    String Name;
    int PlantTypeId;
    int GreenhouseId;
    

    PlantEntity()  : Entity(){}

    PlantEntity(int id, String _Name, int _PlantTypeId, int _GreenhouseId) : Entity() {
        this->id = id;
        Name = _Name;
        PlantTypeId = _PlantTypeId;
        GreenhouseId = _GreenhouseId;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_PLANTTYPEID, String(PlantTypeId), "int");
        addColumn(COLUMN_GREENHOUSEID, String(GreenhouseId), "int");
        
    }

    PlantEntity(String _Name, int _PlantTypeId, int _GreenhouseId) : 
        PlantEntity(0, _Name, _PlantTypeId, _GreenhouseId)  {}

    static PlantEntity fromEntity(Entity entity)
    {
        PlantEntity plantentity = PlantEntity();
        plantentity.fromString(entity.toString());
        return plantentity;
    }

    // Setters and Getters for each field
};

const String PlantEntity::COLUMN_NAME = "Name";
const String PlantEntity::COLUMN_PLANTTYPEID = "PlantTypeId";
const String PlantEntity::COLUMN_GREENHOUSEID = "GreenhouseId";


#endif // PLANTENTITY_H