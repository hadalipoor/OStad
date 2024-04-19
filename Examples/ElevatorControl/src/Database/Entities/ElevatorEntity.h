#ifndef ELEVATORENTITY_H
#define ELEVATORENTITY_H

#include <OStad.h>

class ElevatorEntity : public Entity {
public:
    static const String COLUMN_CURRENTFLOOR;
    static const String COLUMN_STATUS;
    static const String COLUMN_DIRECTION;
    static const String COLUMN_LASTMAINTENANCEDATE;
    

    int CurrentFloor;
    String Status;
    String Direction;
    String LastMaintenanceDate;
    

    ElevatorEntity()  : Entity(){}

    ElevatorEntity(int id, int _CurrentFloor, String _Status, String _Direction, String _LastMaintenanceDate) : Entity() {
        this->id = id;
        CurrentFloor = _CurrentFloor;
        Status = _Status;
        Direction = _Direction;
        LastMaintenanceDate = _LastMaintenanceDate;
        

        addColumn(COLUMN_CURRENTFLOOR, String(CurrentFloor), "int");
        addColumn(COLUMN_STATUS, String(Status), "String");
        addColumn(COLUMN_DIRECTION, String(Direction), "String");
        addColumn(COLUMN_LASTMAINTENANCEDATE, String(LastMaintenanceDate), "String");
        
    }

    ElevatorEntity(int _CurrentFloor, String _Status, String _Direction, String _LastMaintenanceDate) : 
        ElevatorEntity(0, _CurrentFloor, _Status, _Direction, _LastMaintenanceDate)  {}

    static ElevatorEntity fromEntity(Entity entity)
    {
        ElevatorEntity elevatorentity = ElevatorEntity();
        elevatorentity.fromString(entity.toString());
        return elevatorentity;
    }

    // Setters and Getters for each field
};

const String ElevatorEntity::COLUMN_CURRENTFLOOR = "CurrentFloor";
const String ElevatorEntity::COLUMN_STATUS = "Status";
const String ElevatorEntity::COLUMN_DIRECTION = "Direction";
const String ElevatorEntity::COLUMN_LASTMAINTENANCEDATE = "LastMaintenanceDate";


#endif // ELEVATORENTITY_H