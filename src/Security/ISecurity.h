#ifndef ISECURITY_H
#define ISECURITY_H

#include "LoginResult.h"
#include <HTTPS_Server_Generic.h>
#include <base64.h>
#include "../NetworkManager/apis/ApiInterface.h"

enum AuthorizationResults{
    SUCCESFULL,
    AUTH_HEADER_MISSING,
    INVALID_AUTHORIZATION_FORMAT,
    INVALID_TOKEN,
    USER_NOT_EXISTS,
    USER_NO_PERMISSION,
    ERROR
};
class ISecurity {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
    virtual LoginResult login(String username, String password) = 0;
    virtual LoginResult logout(String username) = 0;
    virtual bool checkTwoFactorSecurityOtpCode(String username, String otpCode) = 0;
    virtual bool checkUserPermission(String username, String permission) = 0;
    virtual LoginResult getUserNameFromToken(String token) = 0;
    virtual AuthorizationResults checkAuthentication(HTTPRequest * req, HTTPResponse * res, String permission) = 0;
    virtual void addPermissionForAdmin(String title, String group) = 0;
};

#endif // ISECURITY_H
