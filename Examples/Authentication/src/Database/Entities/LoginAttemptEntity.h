#ifndef LOGINATTEMPTENTITY_H
#define LOGINATTEMPTENTITY_H

#include <OStad.h>

class LoginAttemptEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_TIMESTAMP;
    

    int UserId;
    EBPDateTime Timestamp;
    

    LoginAttemptEntity()  : Entity(){}

    LoginAttemptEntity(int id, int _UserId, EBPDateTime _Timestamp) : Entity() {
        this->id = id;
        UserId = _UserId;
        Timestamp = _Timestamp;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_TIMESTAMP, Timestamp.toDateTimeString(), "EBPDateTime");
        
    }

    LoginAttemptEntity(int _UserId, EBPDateTime _Timestamp) : 
        LoginAttemptEntity(0, _UserId, _Timestamp)  {}

    static LoginAttemptEntity fromEntity(Entity entity)
    {
        LoginAttemptEntity loginattemptentity = LoginAttemptEntity();
        loginattemptentity.fromString(entity.toString());
        return loginattemptentity;
    }

    // Setters and Getters for each field
};

const String LoginAttemptEntity::COLUMN_USERID = "UserId";
const String LoginAttemptEntity::COLUMN_TIMESTAMP = "Timestamp";


#endif // LOGINATTEMPTENTITY_H