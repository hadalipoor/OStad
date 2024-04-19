#ifndef REQUESTLOGENTITY_H
#define REQUESTLOGENTITY_H

#include <OStad.h>

class RequestLogEntity : public Entity {
public:
    static const String COLUMN_REQUESTFLOOR;
    static const String COLUMN_DIRECTION;
    static const String COLUMN_REQUESTTIME;
    

    int RequestFloor;
    String Direction;
    String RequestTime;
    

    RequestLogEntity()  : Entity(){}

    RequestLogEntity(int id, int _RequestFloor, String _Direction, String _RequestTime) : Entity() {
        this->id = id;
        RequestFloor = _RequestFloor;
        Direction = _Direction;
        RequestTime = _RequestTime;
        

        addColumn(COLUMN_REQUESTFLOOR, String(RequestFloor), "int");
        addColumn(COLUMN_DIRECTION, String(Direction), "String");
        addColumn(COLUMN_REQUESTTIME, String(RequestTime), "String");
        
    }

    RequestLogEntity(int _RequestFloor, String _Direction, String _RequestTime) : 
        RequestLogEntity(0, _RequestFloor, _Direction, _RequestTime)  {}

    static RequestLogEntity fromEntity(Entity entity)
    {
        RequestLogEntity requestlogentity = RequestLogEntity();
        requestlogentity.fromString(entity.toString());
        return requestlogentity;
    }

    // Setters and Getters for each field
};

const String RequestLogEntity::COLUMN_REQUESTFLOOR = "RequestFloor";
const String RequestLogEntity::COLUMN_DIRECTION = "Direction";
const String RequestLogEntity::COLUMN_REQUESTTIME = "RequestTime";


#endif // REQUESTLOGENTITY_H