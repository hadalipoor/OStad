#ifndef ELEVATORLOGENTITY_H
#define ELEVATORLOGENTITY_H

#include <OStad.h>

class ElevatorLogEntity : public Entity {
public:
    static const String COLUMN_ACTION;
    static const String COLUMN_ACTIONTIME;
    

    String Action;
    String ActionTime;
    

    ElevatorLogEntity()  : Entity(){}

    ElevatorLogEntity(int id, String _Action, String _ActionTime) : Entity() {
        this->id = id;
        Action = _Action;
        ActionTime = _ActionTime;
        

        addColumn(COLUMN_ACTION, String(Action), "String");
        addColumn(COLUMN_ACTIONTIME, String(ActionTime), "String");
        
    }

    ElevatorLogEntity(String _Action, String _ActionTime) : 
        ElevatorLogEntity(0, _Action, _ActionTime)  {}

    static ElevatorLogEntity fromEntity(Entity entity)
    {
        ElevatorLogEntity elevatorlogentity = ElevatorLogEntity();
        elevatorlogentity.fromString(entity.toString());
        return elevatorlogentity;
    }

    // Setters and Getters for each field
};

const String ElevatorLogEntity::COLUMN_ACTION = "Action";
const String ElevatorLogEntity::COLUMN_ACTIONTIME = "ActionTime";


#endif // ELEVATORLOGENTITY_H