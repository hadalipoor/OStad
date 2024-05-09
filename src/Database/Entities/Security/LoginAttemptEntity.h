#ifndef LOGINATTEMPTENTITY_H
#define LOGINATTEMPTENTITY_H

#include "../Entity.h"

class LoginAttemptEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_TIMESTAMP;

private:
    int userId;
    EBPDateTime timestamp;

public:
    LoginAttemptEntity() : Entity(), userId(0), timestamp(EBPDateTime()) {}

    LoginAttemptEntity(int id, int _UserId, EBPDateTime _Timestamp) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->timestamp = _Timestamp;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_TIMESTAMP, this->timestamp.toDateTimeString());
    }

    LoginAttemptEntity(int _UserId, EBPDateTime _Timestamp) : 
        LoginAttemptEntity(0, _UserId, _Timestamp) {}

    static LoginAttemptEntity fromEntity(Entity entity) {
        LoginAttemptEntity loginattemptentity = LoginAttemptEntity();
        loginattemptentity.fromString(entity.toString());
        return loginattemptentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    EBPDateTime getTimestamp() {
        timestamp.fromString(GetValue(COLUMN_TIMESTAMP));
        return timestamp;
    }

    // Setters
    void setUserId(int value) {
        userId = value;
        SetValue(COLUMN_USERID, String(userId));
    }

    void setTimestamp(EBPDateTime value) {
        timestamp = value;
        SetValue(COLUMN_TIMESTAMP, timestamp.toDateTimeString());
    }
};

const String LoginAttemptEntity::COLUMN_USERID = "UserId";
const String LoginAttemptEntity::COLUMN_TIMESTAMP = "Timestamp";

#endif // LOGINATTEMPTENTITY_H
