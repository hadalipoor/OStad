#ifndef DOORLOGENTITY_H
#define DOORLOGENTITY_H

#include <OStad.h>

class DoorLogEntity : public Entity {
public:
    static const String COLUMN_UID;
    static const String COLUMN_GUESTID;
    static const String COLUMN_DOOROPENED;
    static const String COLUMN_TAGREADTIME;
    

    int UId;
    int GuestId;
    int DoorOpened;
    EBPDateTime TagReadTime;
    

    DoorLogEntity()  : Entity(){}

    DoorLogEntity(int id, int _UId, int _GuestId, int _DoorOpened, EBPDateTime _TagReadTime) : Entity() {
        this->id = id;
        UId = _UId;
        GuestId = _GuestId;
        DoorOpened = _DoorOpened;
        TagReadTime = _TagReadTime;
        

        addColumn(COLUMN_UID, String(UId), "int");
        addColumn(COLUMN_GUESTID, String(GuestId), "int");
        addColumn(COLUMN_DOOROPENED, String(DoorOpened), "int");
        addColumn(COLUMN_TAGREADTIME, TagReadTime.toDateTimeString(), "EBPDateTime");
        
    }

    DoorLogEntity(int _UId, int _GuestId, int _DoorOpened, EBPDateTime _TagReadTime) : 
        DoorLogEntity(0, _UId, _GuestId, _DoorOpened, _TagReadTime)  {}

    static DoorLogEntity fromEntity(Entity entity)
    {
        DoorLogEntity doorlogentity = DoorLogEntity();
        doorlogentity.fromString(entity.toString());
        return doorlogentity;
    }

    // Setters and Getters for each field
};

const String DoorLogEntity::COLUMN_UID = "UId";
const String DoorLogEntity::COLUMN_GUESTID = "GuestId";
const String DoorLogEntity::COLUMN_DOOROPENED = "DoorOpened";
const String DoorLogEntity::COLUMN_TAGREADTIME = "TagReadTime";


#endif // DOORLOGENTITY_H