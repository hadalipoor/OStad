#ifndef ACCOUNTLOCKOUTENTITY_H
#define ACCOUNTLOCKOUTENTITY_H

#include "../Entity.h"

class AccountLockoutEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_LOCKOUTSTARTTIME;
    static const String COLUMN_LOCKOUTENDTIME;

private:
    int userId;
    EBPDateTime lockoutStartTime;
    EBPDateTime lockoutEndTime;

public:
    AccountLockoutEntity() : Entity(), userId(0), lockoutStartTime(EBPDateTime()), lockoutEndTime(EBPDateTime()) {}

    AccountLockoutEntity(int id, int _UserId, EBPDateTime _LockoutStartTime, EBPDateTime _LockoutEndTime) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->lockoutStartTime = _LockoutStartTime;
        this->lockoutEndTime = _LockoutEndTime;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_LOCKOUTSTARTTIME, this->lockoutStartTime.toDateTimeString());
        SetValue(COLUMN_LOCKOUTENDTIME, this->lockoutEndTime.toDateTimeString());
    }

    AccountLockoutEntity(int _UserId, EBPDateTime _LockoutStartTime, EBPDateTime _LockoutEndTime) : 
        AccountLockoutEntity(0, _UserId, _LockoutStartTime, _LockoutEndTime) {}

    static AccountLockoutEntity fromEntity(Entity entity) {
        AccountLockoutEntity accountlockoutentity = AccountLockoutEntity();
        accountlockoutentity.fromString(entity.toString());
        return accountlockoutentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    EBPDateTime getLockoutStartTime() {
        lockoutStartTime.fromString(GetValue(COLUMN_LOCKOUTSTARTTIME));
        return lockoutStartTime;
    }

    EBPDateTime getLockoutEndTime() {
        lockoutEndTime.fromString(GetValue(COLUMN_LOCKOUTENDTIME));
        return lockoutEndTime;
    }

    // Setters
    void setUserId(int value) {
        userId = value;
        SetValue(COLUMN_USERID, String(userId));
    }

    void setLockoutStartTime(EBPDateTime value) {
        lockoutStartTime = value;
        SetValue(COLUMN_LOCKOUTSTARTTIME, lockoutStartTime.toDateTimeString());
    }

    void setLockoutEndTime(EBPDateTime value) {
        lockoutEndTime = value;
        SetValue(COLUMN_LOCKOUTENDTIME, lockoutEndTime.toDateTimeString());
    }
};

const String AccountLockoutEntity::COLUMN_USERID = "UserId";
const String AccountLockoutEntity::COLUMN_LOCKOUTSTARTTIME = "LockoutStartTime";
const String AccountLockoutEntity::COLUMN_LOCKOUTENDTIME = "LockoutEndTime";

#endif // ACCOUNTLOCKOUTENTITY_H
