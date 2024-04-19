#ifndef USERENTITY_H
#define USERENTITY_H

#include <OStad.h>

class UserEntity : public Entity {
public:
    static const String COLUMN_USERNAME;
    static const String COLUMN_PASSWORD;
    static const String COLUMN_EMAIL;
    static const String COLUMN_PHONENUMBER;
    static const String COLUMN_ROLEID;
    static const String COLUMN_TWOFACTORAUTH;
    static const String COLUMN_APIKEY;
    static const String COLUMN_TOKEN;
    static const String COLUMN_TOKENEXPIRYTIME;
    

    String Username;
    String Password;
    String Email;
    String PhoneNumber;
    int RoleId;
    bool TwoFactorAuth;
    String ApiKey;
    String Token;
    EBPDateTime TokenExpiryTime;
    

    UserEntity()  : Entity(){}

    UserEntity(int id, String _Username, String _Password, String _Email, String _PhoneNumber, int _RoleId, bool _TwoFactorAuth, String _ApiKey, String _Token, EBPDateTime _TokenExpiryTime) : Entity() {
        this->id = id;
        Username = _Username;
        Password = _Password;
        Email = _Email;
        PhoneNumber = _PhoneNumber;
        RoleId = _RoleId;
        TwoFactorAuth = _TwoFactorAuth;
        ApiKey = _ApiKey;
        Token = _Token;
        TokenExpiryTime = _TokenExpiryTime;
        

        addColumn(COLUMN_USERNAME, String(Username), "String");
        addColumn(COLUMN_PASSWORD, String(Password), "String");
        addColumn(COLUMN_EMAIL, String(Email), "String");
        addColumn(COLUMN_PHONENUMBER, String(PhoneNumber), "String");
        addColumn(COLUMN_ROLEID, String(RoleId), "int");
        addColumn(COLUMN_TWOFACTORAUTH, String(TwoFactorAuth), "bool");
        addColumn(COLUMN_APIKEY, String(ApiKey), "String");
        addColumn(COLUMN_TOKEN, String(Token), "String");
        addColumn(COLUMN_TOKENEXPIRYTIME, TokenExpiryTime.toDateTimeString(), "EBPDateTime");
        
    }

    UserEntity(String _Username, String _Password, String _Email, String _PhoneNumber, int _RoleId, bool _TwoFactorAuth, String _ApiKey, String _Token, EBPDateTime _TokenExpiryTime) : 
        UserEntity(0, _Username, _Password, _Email, _PhoneNumber, _RoleId, _TwoFactorAuth, _ApiKey, _Token, _TokenExpiryTime)  {}

    static UserEntity fromEntity(Entity entity)
    {
        UserEntity userentity = UserEntity();
        userentity.fromString(entity.toString());
        return userentity;
    }

    // Setters and Getters for each field
};

const String UserEntity::COLUMN_USERNAME = "Username";
const String UserEntity::COLUMN_PASSWORD = "Password";
const String UserEntity::COLUMN_EMAIL = "Email";
const String UserEntity::COLUMN_PHONENUMBER = "PhoneNumber";
const String UserEntity::COLUMN_ROLEID = "RoleId";
const String UserEntity::COLUMN_TWOFACTORAUTH = "TwoFactorAuth";
const String UserEntity::COLUMN_APIKEY = "ApiKey";
const String UserEntity::COLUMN_TOKEN = "Token";
const String UserEntity::COLUMN_TOKENEXPIRYTIME = "TokenExpiryTime";


#endif // USERENTITY_H