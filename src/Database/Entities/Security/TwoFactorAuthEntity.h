#ifndef TWOFACTORAUTHENTITY_H
#define TWOFACTORAUTHENTITY_H

#include "../Entity.h"

class TwoFactorAuthEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_OTPCODE;
    static const String COLUMN_EXPIRYTIME;
    

    int UserId;
    String OtpCode;
    EBPDateTime ExpiryTime;
    

    TwoFactorAuthEntity()  : Entity(){}

    TwoFactorAuthEntity(int id, int _UserId, String _OtpCode, EBPDateTime _ExpiryTime) : Entity() {
        this->id = id;
        UserId = _UserId;
        OtpCode = _OtpCode;
        ExpiryTime = _ExpiryTime;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_OTPCODE, String(OtpCode), "String");
        addColumn(COLUMN_EXPIRYTIME, ExpiryTime.toDateTimeString(), "EBPDateTime");
        
    }

    TwoFactorAuthEntity(int _UserId, String _OtpCode, EBPDateTime _ExpiryTime) : 
        TwoFactorAuthEntity(0, _UserId, _OtpCode, _ExpiryTime)  {}

    static TwoFactorAuthEntity fromEntity(Entity entity)
    {
        TwoFactorAuthEntity twofactorauthentity = TwoFactorAuthEntity();
        twofactorauthentity.fromString(entity.toString());
        return twofactorauthentity;
    }

    // Setters and Getters for each field
};

const String TwoFactorAuthEntity::COLUMN_USERID = "UserId";
const String TwoFactorAuthEntity::COLUMN_OTPCODE = "OtpCode";
const String TwoFactorAuthEntity::COLUMN_EXPIRYTIME = "ExpiryTime";


#endif // TWOFACTORAUTHENTITY_H