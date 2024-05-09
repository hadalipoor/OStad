#ifndef USERENTITY_H
#define USERENTITY_H

#include "../Entity.h"

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

private:
    String username;
    String password;
    String email;
    String phoneNumber;
    int roleId;
    bool twoFactorAuth;
    String apiKey;
    String token;
    EBPDateTime tokenExpiryTime;

public:
    UserEntity() : Entity(), username(""), password(""), email(""), phoneNumber(""), roleId(0), twoFactorAuth(false), apiKey(""), token(""), tokenExpiryTime(EBPDateTime()) {}

    UserEntity(int id, String _Username, String _Password, String _Email, String _PhoneNumber, int _RoleId, bool _TwoFactorAuth, String _ApiKey, String _Token, EBPDateTime _TokenExpiryTime) : Entity() {
        this->id = id;
        this->username = _Username;
        this->password = _Password;
        this->email = _Email;
        this->phoneNumber = _PhoneNumber;
        this->roleId = _RoleId;
        this->twoFactorAuth = _TwoFactorAuth;
        this->apiKey = _ApiKey;
        this->token = _Token;
        this->tokenExpiryTime = _TokenExpiryTime;
        SetValue(COLUMN_USERNAME, this->username);
        SetValue(COLUMN_PASSWORD, this->password);
        SetValue(COLUMN_EMAIL, this->email);
        SetValue(COLUMN_PHONENUMBER, this->phoneNumber);
        SetValue(COLUMN_ROLEID, String(this->roleId));
        SetValue(COLUMN_TWOFACTORAUTH, String(this->twoFactorAuth));
        SetValue(COLUMN_APIKEY, this->apiKey);
        SetValue(COLUMN_TOKEN, this->token);
        SetValue(COLUMN_TOKENEXPIRYTIME, this->tokenExpiryTime.toDateTimeString());
    }

    UserEntity(String _Username, String _Password, String _Email, String _PhoneNumber, int _RoleId, bool _TwoFactorAuth, String _ApiKey, String _Token, EBPDateTime _TokenExpiryTime) : 
        UserEntity(0, _Username, _Password, _Email, _PhoneNumber, _RoleId, _TwoFactorAuth, _ApiKey, _Token, _TokenExpiryTime) {}

    static UserEntity fromEntity(Entity entity) {
        UserEntity userentity = UserEntity();
        userentity.fromString(entity.toString());
        return userentity;
    }

    // Getters
    String getUsername() {
        username = GetValue(COLUMN_USERNAME);
        return username;
    }

    String getPassword() {
        password = GetValue(COLUMN_PASSWORD);
        return password;
    }

    String getEmail() {
        email = GetValue(COLUMN_EMAIL);
        return email;
    }

    String getPhoneNumber() {
        phoneNumber = GetValue(COLUMN_PHONENUMBER);
        return phoneNumber;
    }

    int getRoleId() {
        roleId = GetValue(COLUMN_ROLEID).toInt();
        return roleId;
    }

    bool getTwoFactorAuth() {
        twoFactorAuth = GetValue(COLUMN_TWOFACTORAUTH) == "true";
        return twoFactorAuth;
    }

    String getApiKey() {
        apiKey = GetValue(COLUMN_APIKEY);
        return apiKey;
    }

    String getToken() {
        token = GetValue(COLUMN_TOKEN);
        return token;
    }

    EBPDateTime getTokenExpiryTime() {
        tokenExpiryTime.fromString(GetValue(COLUMN_TOKENEXPIRYTIME));
        return tokenExpiryTime;
    }

    // Setters
    void setUsername(String value) {
        username = value;
        SetValue(COLUMN_USERNAME, username);
    }

    void setPassword(String value) {
        password = value;
        SetValue(COLUMN_PASSWORD, password);
    }

    void setEmail(String value) {
        email = value;
        SetValue(COLUMN_EMAIL, email);
    }

    void setPhoneNumber(String value) {
        phoneNumber = value;
        SetValue(COLUMN_PHONENUMBER, phoneNumber);
    }

    void setRoleId(int value) {
        roleId = value;
        SetValue(COLUMN_ROLEID, String(roleId));
    }

    void setTwoFactorAuth(bool value) {
        twoFactorAuth = value;
        SetValue(COLUMN_TWOFACTORAUTH, String(twoFactorAuth));
    }

    void setApiKey(String value) {
        apiKey = value;
        SetValue(COLUMN_APIKEY, apiKey);
    }

    void setToken(String value) {
        token = value;
        SetValue(COLUMN_TOKEN, token);
    }

    void setTokenExpiryTime(EBPDateTime value) {
        tokenExpiryTime = value;
        SetValue(COLUMN_TOKENEXPIRYTIME, tokenExpiryTime.toDateTimeString());
    }
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
