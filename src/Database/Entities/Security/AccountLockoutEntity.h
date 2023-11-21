#ifndef ACCOUNTLOCKOUTENTITY_H
#define ACCOUNTLOCKOUTENTITY_H

#include "../Entity.h"

class AccountLockoutEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_LOCKOUTSTARTTIME;
    static const String COLUMN_LOCKOUTENDTIME;
    

    int UserId;
    EBPDateTime LockoutStartTime;
    EBPDateTime LockoutEndTime;
    

    AccountLockoutEntity()  : Entity(){}

    AccountLockoutEntity(int id, int _UserId, EBPDateTime _LockoutStartTime, EBPDateTime _LockoutEndTime) : Entity() {
        this->id = id;
        UserId = _UserId;
        LockoutStartTime = _LockoutStartTime;
        LockoutEndTime = _LockoutEndTime;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_LOCKOUTSTARTTIME, LockoutStartTime.toDateTimeString(), "EBPDateTime");
        addColumn(COLUMN_LOCKOUTENDTIME, LockoutEndTime.toDateTimeString(), "EBPDateTime");
        
    }

    AccountLockoutEntity(int _UserId, EBPDateTime _LockoutStartTime, EBPDateTime _LockoutEndTime) : 
        AccountLockoutEntity(0, _UserId, _LockoutStartTime, _LockoutEndTime)  {}

    static AccountLockoutEntity fromEntity(Entity entity)
    {
        AccountLockoutEntity accountlockoutentity = AccountLockoutEntity();
        accountlockoutentity.fromString(entity.toString());
        return accountlockoutentity;
    }

    // Setters and Getters for each field
};

const String AccountLockoutEntity::COLUMN_USERID = "UserId";
const String AccountLockoutEntity::COLUMN_LOCKOUTSTARTTIME = "LockoutStartTime";
const String AccountLockoutEntity::COLUMN_LOCKOUTENDTIME = "LockoutEndTime";


#endif // ACCOUNTLOCKOUTENTITY_H