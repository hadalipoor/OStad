#ifndef TWOFACTORAUTHENTITY_H
#define TWOFACTORAUTHENTITY_H

#include "../Entity.h"

class TwoFactorAuthEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_OTPCODE;
    static const String COLUMN_EXPIRYTIME;

private:
    int userId;
    String otpCode;
    EBPDateTime expiryTime;

public:
    TwoFactorAuthEntity() : Entity(), userId(0), otpCode(""), expiryTime(EBPDateTime()) {}

    TwoFactorAuthEntity(int id, int _UserId, String _OtpCode, EBPDateTime _ExpiryTime) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->otpCode = _OtpCode;
        this->expiryTime = _ExpiryTime;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_OTPCODE, this->otpCode);
        SetValue(COLUMN_EXPIRYTIME, this->expiryTime.toDateTimeString());
    }

    TwoFactorAuthEntity(int _UserId, String _OtpCode, EBPDateTime _ExpiryTime) : 
        TwoFactorAuthEntity(0, _UserId, _OtpCode, _ExpiryTime) {}

    static TwoFactorAuthEntity fromEntity(Entity entity) {
        TwoFactorAuthEntity twofactorauthentity = TwoFactorAuthEntity();
        twofactorauthentity.fromString(entity.toString());
        return twofactorauthentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    String getOtpCode() {
        otpCode = GetValue(COLUMN_OTPCODE);
        return otpCode;
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

    void setOtpCode(String value) {
        otpCode = value;
        SetValue(COLUMN_OTPCODE, otpCode);
    }

    void setExpiryTime(EBPDateTime value) {
        expiryTime = value;
        SetValue(COLUMN_EXPIRYTIME, expiryTime.toDateTimeString());
    }
};

const String TwoFactorAuthEntity::COLUMN_USERID = "UserId";
const String TwoFactorAuthEntity::COLUMN_OTPCODE = "OtpCode";
const String TwoFactorAuthEntity::COLUMN_EXPIRYTIME = "ExpiryTime";

#endif // TWOFACTORAUTHENTITY_H
