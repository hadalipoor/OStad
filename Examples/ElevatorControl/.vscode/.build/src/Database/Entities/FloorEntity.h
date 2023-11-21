#ifndef FLOORENTITY_H
#define FLOORENTITY_H

#include <OStad.h>

class FloorEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_ACCESSRESTRICTIONS;
    

    String Name;
    String AccessRestrictions;
    

    FloorEntity()  : Entity(){}

    FloorEntity(int id, String _Name, String _AccessRestrictions) : Entity() {
        this->id = id;
        Name = _Name;
        AccessRestrictions = _AccessRestrictions;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_ACCESSRESTRICTIONS, String(AccessRestrictions), "String");
        
    }

    FloorEntity(String _Name, String _AccessRestrictions) : 
        FloorEntity(0, _Name, _AccessRestrictions)  {}

    static FloorEntity fromEntity(Entity entity)
    {
        FloorEntity floorentity = FloorEntity();
        floorentity.fromString(entity.toString());
        return floorentity;
    }

    // Setters and Getters for each field
};

const String FloorEntity::COLUMN_NAME = "Name";
const String FloorEntity::COLUMN_ACCESSRESTRICTIONS = "AccessRestrictions";


#endif // FLOORENTITY_H