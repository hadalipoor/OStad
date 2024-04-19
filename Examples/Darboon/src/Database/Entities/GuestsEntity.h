#ifndef GUESTSENTITY_H
#define GUESTSENTITY_H

#include <OStad.h>

class GuestsEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_DESCRIPTION;
    static const String COLUMN_UID;
    static const String COLUMN_ACTIVE;
    static const String COLUMN_STARTACTIVETIME;
    static const String COLUMN_ENDACTIVETIME;
    

    String Name;
    String Description;
    String UId;
    int Active;
    EBPDateTime StartActiveTime;
    EBPDateTime EndActiveTime;
    

    GuestsEntity()  : Entity(){}

    GuestsEntity(int id, String _Name, String _Description, String _UId, int _Active, EBPDateTime _StartActiveTime, EBPDateTime _EndActiveTime) : Entity() {
        this->id = id;
        Name = _Name;
        Description = _Description;
        UId = _UId;
        Active = _Active;
        StartActiveTime = _StartActiveTime;
        EndActiveTime = _EndActiveTime;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_DESCRIPTION, String(Description), "String");
        addColumn(COLUMN_UID, String(UId), "String");
        addColumn(COLUMN_ACTIVE, String(Active), "int");
        addColumn(COLUMN_STARTACTIVETIME, StartActiveTime.toDateTimeString(), "EBPDateTime");
        addColumn(COLUMN_ENDACTIVETIME, EndActiveTime.toDateTimeString(), "EBPDateTime");
        
    }

    GuestsEntity(String _Name, String _Description, String _UId, int _Active, EBPDateTime _StartActiveTime, EBPDateTime _EndActiveTime) : 
        GuestsEntity(0, _Name, _Description, _UId, _Active, _StartActiveTime, _EndActiveTime)  {}

    static GuestsEntity fromEntity(Entity entity)
    {
        GuestsEntity guestsentity = GuestsEntity();
        guestsentity.fromString(entity.toString());
        return guestsentity;
    }

    // Setters and Getters for each field
};

const String GuestsEntity::COLUMN_NAME = "Name";
const String GuestsEntity::COLUMN_DESCRIPTION = "Description";
const String GuestsEntity::COLUMN_UID = "UId";
const String GuestsEntity::COLUMN_ACTIVE = "Active";
const String GuestsEntity::COLUMN_STARTACTIVETIME = "StartActiveTime";
const String GuestsEntity::COLUMN_ENDACTIVETIME = "EndActiveTime";


#endif // GUESTSENTITY_H