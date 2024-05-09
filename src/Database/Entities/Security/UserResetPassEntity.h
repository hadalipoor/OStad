#ifndef USERRESETPASSENTITY_H
#define USERRESETPASSENTITY_H

#include "../Entity.h"

class UserResetPassEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_RESETTOKEN;
    static const String COLUMN_EXPIRYTIME;

private:
    int userId;
    String resetToken;
    EBPDateTime expiryTime;

public:
    UserResetPassEntity() : Entity(), userId(0), resetToken(""), expiryTime(EBPDateTime()) {}

    UserResetPassEntity(int id, int _UserId, String _ResetToken, EBPDateTime _ExpiryTime) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->resetToken = _ResetToken;
        this->expiryTime = _ExpiryTime;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_RESETTOKEN, this->resetToken);
        SetValue(COLUMN_EXPIRYTIME, this->expiryTime.toDateTimeString());
    }

    UserResetPassEntity(int _UserId, String _ResetToken, EBPDateTime _ExpiryTime) : 
        UserResetPassEntity(0, _UserId, _ResetToken, _ExpiryTime) {}

    static UserResetPassEntity fromEntity(Entity entity) {
        UserResetPassEntity userresetpassentity = UserResetPassEntity();
        userresetpassentity.fromString(entity.toString());
        return userresetpassentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    String getResetToken() {
        resetToken = GetValue(COLUMN_RESETTOKEN);
        return resetToken;
    }

    EBPDateTime getExpiryTime() {
        expiryTime.fromString(GetValue(COLUMN_EXPIRYTIME));
        return expiryTime;
    }

    // Setters
    void setUserId(int value) {
        userId = value;
        SetValue(COLUMN_USERID, String(userId));
    }

    void setResetToken(String value) {
        resetToken = value;
        SetValue(COLUMN_RESETTOKEN, resetToken);
    }

    void setExpiryTime(EBPDateTime value) {
        expiryTime = value;
        SetValue(COLUMN_EXPIRYTIME, expiryTime.toDateTimeString());
    }
};

const String UserResetPassEntity::COLUMN_USERID = "UserId";
const String UserResetPassEntity::COLUMN_RESETTOKEN = "ResetToken";
const String UserResetPassEntity::COLUMN_EXPIRYTIME = "ExpiryTime";

#endif // USERRESETPASSENTITY_H
