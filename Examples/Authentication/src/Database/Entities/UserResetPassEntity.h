#ifndef USERRESETPASSENTITY_H
#define USERRESETPASSENTITY_H

#include <OStad.h>

class UserResetPassEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_RESETTOKEN;
    static const String COLUMN_EXPIRYTIME;
    

    int UserId;
    String ResetToken;
    EBPDateTime ExpiryTime;
    

    UserResetPassEntity()  : Entity(){}

    UserResetPassEntity(int id, int _UserId, String _ResetToken, EBPDateTime _ExpiryTime) : Entity() {
        this->id = id;
        UserId = _UserId;
        ResetToken = _ResetToken;
        ExpiryTime = _ExpiryTime;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_RESETTOKEN, String(ResetToken), "String");
        addColumn(COLUMN_EXPIRYTIME, ExpiryTime.toDateTimeString(), "EBPDateTime");
        
    }

    UserResetPassEntity(int _UserId, String _ResetToken, EBPDateTime _ExpiryTime) : 
        UserResetPassEntity(0, _UserId, _ResetToken, _ExpiryTime)  {}

    static UserResetPassEntity fromEntity(Entity entity)
    {
        UserResetPassEntity userresetpassentity = UserResetPassEntity();
        userresetpassentity.fromString(entity.toString());
        return userresetpassentity;
    }

    // Setters and Getters for each field
};

const String UserResetPassEntity::COLUMN_USERID = "UserId";
const String UserResetPassEntity::COLUMN_RESETTOKEN = "ResetToken";
const String UserResetPassEntity::COLUMN_EXPIRYTIME = "ExpiryTime";


#endif // USERRESETPASSENTITY_H