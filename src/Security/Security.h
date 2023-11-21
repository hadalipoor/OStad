#ifndef SECURITY_H
#define SECURITY_H

#include "ISecurity.h"
#include "../Context.h"
#include "HMACAuth.h"
#include "LoginResult.h"
#include "../Config/Security/DefaultSecurityConfigs.h"
#include "../Config/Security/SecurityConfigKeys.h"
#include "../Database/Controllers/Security/UserController.h"
#include "../Database/Controllers/Security/PermissionController.h"
#include "../Database/Controllers/Security/RolePermissionController.h"
#include "../Database/Controllers/Security/RoleController.h"

class Security : public ISecurity {
private:
    Context* context;
    LoginResult isLoginAllowed(UserEntity* user, String password);
    bool sendTwoFactorSecurityOtpCode(String username);
    LoginResult createUniqueToken(UserEntity* user);
    void addPermission(int role_id, String title, String group);
    LoginResult generateJWT(UserEntity user);
    bool validateJWT(String jwt);
    int sysAdmin_role_id;
    int admin_role_id;
    char *key;
    HMACAuth auth;
    const char *pin = "6577";
    const char *timestamp = "1156";
    const char *SECRET_KEY = "1111111";



public:
    Security(Context* context);
    
    void initialize() override;
    void update() override;
    LoginResult login(String username, String password) override;
    LoginResult logout(String username) override;
    bool checkTwoFactorSecurityOtpCode(String username, String otpCode) override;
    bool checkUserPermission(String username, String permission) override;
    LoginResult getUserNameFromToken(String token) override;
    AuthorizationResults checkAuthentication(HTTPRequest * req, HTTPResponse * res, String permission) override;
    void addPermissionForAdmin(String title, String group) override;
};

Security::Security(Context* context)
    : context(context) {}

void Security::initialize() {
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Initializing Authorization ...");

    HMACAuth auth(SECRET_KEY);


    String sysAdminRole = "System Admin";
    String AdminRole = "Admin";

    RoleController* roleController = new RoleController(context, storageType);
    UserController* userController = new UserController(context, storageType);

    std::vector<RoleEntity> roleEntities = roleController->Get(String(RoleEntity::COLUMN_ROLENAME + "=" + sysAdminRole));
    if (roleEntities.size() == 0)
    {
        RoleEntity* role = new RoleEntity(sysAdminRole);
        sysAdmin_role_id = roleController->Add(*role);
    }
    else
    {
        sysAdmin_role_id = roleEntities.at(0).id;
    }
    
    roleEntities.clear();
    roleEntities = roleController->Get(String(RoleEntity::COLUMN_ROLENAME + "=" + AdminRole));
    if (roleEntities.size() == 0)
    {
        RoleEntity* role = new RoleEntity(AdminRole);
        admin_role_id = roleController->Add(*role);
        context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Admin Permissions Added To Database.");
    }
    else
    {
        admin_role_id = roleEntities.at(0).id;
    }
    
    String sysAdminUserName = "sysAdmin";
    String AdminUserName = "admin";

    std::vector<UserEntity> users = userController->Get(String(UserEntity::COLUMN_USERNAME + "=" + sysAdminUserName));
    if (users.size() == 0)
    {
        UserEntity* user = new UserEntity(sysAdminUserName, "sysadmin", "", "", sysAdmin_role_id, false, "", "", EBPDateTime::nullDateTime());
        userController->Add(*user);        
    }

    users.clear();
    users = userController->Get(String(UserEntity::COLUMN_USERNAME + "=" + AdminUserName));
    if (users.size() == 0)
    {
        UserEntity* user = new UserEntity(AdminUserName, "admin", "", "", admin_role_id, false, "", "", EBPDateTime::nullDateTime());
        userController->Add(*user);        
        context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Admin Users Added To Database.");
    }
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Authorization Initialized.");

}

void Security::update() {

}

LoginResult Security::login(String username, String password)
{
    UserController* userController = new UserController(context, storageType);
    std::vector<UserEntity> users = userController->Get(String(UserEntity::COLUMN_USERNAME + "=" + username));
    if (users.size() > 0)
    {
        UserEntity user = users.at(0);
        LoginResult loginresult = isLoginAllowed(&user, password);
        if (loginresult.Result == LoginResults::Succesfull)
        {
            LoginResult tokenResult = generateJWT(user);
            user.SetValue(UserEntity::COLUMN_TOKEN, tokenResult.getMessage());
            userController->Update(user);
            return tokenResult;
            // return createUniqueToken(&user);
        }
        else if (loginresult.Result == LoginResults::NeedTwoFactorAuthentication)
        {
            if (sendTwoFactorSecurityOtpCode(username))
            {
                return LoginResult(false, LoginResults::TwoFactorAuthenticationOtpCodeSent);
            }
            else{
                return LoginResult(false, LoginResults::TwoFactorAuthenticationOtpCodeNotSent);
            }            
        }
        else if (loginresult.Result == LoginResults::PasswordIsIncorrect)
        {
            return LoginResult(false, LoginResults::WrongUserNameOrPassword);
        }
        else if (loginresult.Result == LoginResults::TowManyAttempts)
        {
            return loginresult;
        }
        else if (loginresult.Result == LoginResults::UserIsLocked)
        {
            return loginresult;
        }        
    }
    else{
        return LoginResult(false, LoginResults::WrongUserNameOrPassword);
    }
    return LoginResult(false, LoginResults::WrongUserNameOrPassword);
}

LoginResult Security::logout(String username)
{
    UserController* userController = new UserController(context, storageType);
    std::vector<UserEntity> users = userController->Get(String(UserEntity::COLUMN_USERNAME + "=" + username));
    if (users.size() > 0)
    {
        UserEntity user = users.at(0);
        user.Token = "";
        if(userController->Update(user))
        {
            return LoginResult(true, LoginResults::LogoutSuccessfull);
        }
        return LoginResult(false, LoginResults::LogoutUnSuccessfull);
    }
    return LoginResult(false, LoginResults::UsernameNotExists);
}

//check LoginAttepts and AccountLockout
LoginResult Security::isLoginAllowed(UserEntity* user, String password)
{
    if (user->GetValue(UserEntity::COLUMN_PASSWORD) != password)
    {
        ///TODO:: add to login attempts
        return LoginResult(false, LoginResults::PasswordIsIncorrect);
    }
    
    return LoginResult(true, LoginResults::Succesfull);
}

bool Security::sendTwoFactorSecurityOtpCode(String username)
{
    return false;
}

bool Security::checkTwoFactorSecurityOtpCode(String username, String otpCode)
{
    return false;
}

bool Security::checkUserPermission(String username, String permission)
{
    if (username == "sysAdmin" || username == "admin")
    {
        return true;
    }
    ///TODO:: check permission for each admin level

    int permissionId;
    UserEntity user;
    PermissionController* permissionController = new PermissionController(context, storageType);
    std::vector<PermissionEntity> permissionEntities = permissionController->Get(String(PermissionEntity::COLUMN_PERMISSIONNAME + "=" + permission));
    UserController* userController = new UserController(context, storageType);
    
    std::vector<UserEntity> users = userController->Get(String(UserEntity::COLUMN_USERNAME + "=" + username));
    if (users.size() > 0)
    {
        user = users.at(0);
    }else{
        return false;
    }

    if (user.RoleId == 1)
    {
        //this is sys admin
        return true;
    }
    

    if (permissionEntities.size()>0)
    {
        permissionId = permissionEntities.at(0).id;
    }else{
        return false;
    }
    RolePermissionController* rolePermissionController = new RolePermissionController(context, storageType);
    String query = String(RolePermissionEntity::COLUMN_ROLEID + "=" + user.GetValue(UserEntity::COLUMN_ROLEID) + " AND " + RolePermissionEntity::COLUMN_PERMISSIONID + "=" + permissionId);
    std::vector<RolePermissionEntity> rolePermissionEntities = rolePermissionController->Get(query);
    
    if (rolePermissionEntities.size() > 0)
    {
        return true;
    }else{
        return false;
    }
    
    return false;
}

LoginResult Security::createUniqueToken(UserEntity* user)
{
    String token = "";
    String chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < 16; i++) {
    char randomChar = chars[random(0, chars.length())];
    token += randomChar;
    }
    
    UserController* userController = new UserController(context, storageType);
    EBPDateTime expiryDate = context->getClock()->now();
    expiryDate.addToDateTime(0,0,context->getConfig()->getSecurityConfig()->get(SecurityConfigKey::TOKEN_ACTIVE_DAY).toInt(),0,0,0);
    user = new UserEntity(user->id, user->GetValue(UserEntity::COLUMN_USERNAME), user->GetValue(UserEntity::COLUMN_PASSWORD), 
        user->GetValue(UserEntity::COLUMN_EMAIL), user->GetValue(UserEntity::COLUMN_PHONENUMBER), user->GetValue(UserEntity::COLUMN_ROLEID).toInt(), 
        boolean(user->GetValue(UserEntity::COLUMN_TWOFACTORAUTH)), user->GetValue(UserEntity::COLUMN_APIKEY), token, expiryDate);
    if(userController->Update(*user))
    {
        LoginResult result = LoginResult(true, LoginResults::UsernameNotExists);
        result.Message = token;
        return result;
    }
    return LoginResult(false, LoginResults::TokenNotSaved);
}

LoginResult Security::getUserNameFromToken(String token)
{
    UserController* userController = new UserController(context, storageType);
    std::vector<UserEntity> users = userController->Get(String(UserEntity::COLUMN_TOKEN + "=" + token));
    if (users.size() > 0)
    {
        UserEntity user = users.at(0);
        LoginResult result;
        if (user.id == 1)
        {
            result = LoginResult(true, LoginResults::AdminUser);

        }
        else
        {
            result = LoginResult(true, LoginResults::Succesfull);
        }
        
        result.Message = user.GetValue(UserEntity::COLUMN_USERNAME);
        return result;
    }
    else{
        return LoginResult(false, LoginResults::UsernameNotExists);
    }

}


AuthorizationResults Security::checkAuthentication(HTTPRequest * req, HTTPResponse * res, String permission)
{

    bool authenticationEnable = context->getConfig()->getSecurityConfig()->get(SecurityConfigKey::AUTHENTICATION_ENABLE) == "true" ? true : false;
    String username = "";

    if(authenticationEnable)
    {
        // Check if the request has an Authorization header with the format "Bearer <token>"
        if(req->getHeader("Authorization").substr(0, 7) != "Bearer ")
        {
            response(res, 403, "text/html", "Authorization Header Missing");
            return AuthorizationResults::AUTH_HEADER_MISSING;
        }
        String authHeader = String(req->getHeader("Authorization").c_str());
        if(!authHeader.startsWith("Bearer "))
        {
            response(res, 403, "text/html", "Invalid Authorization format");
            return AuthorizationResults::INVALID_AUTHORIZATION_FORMAT;
        }
        String token = authHeader.substring(7); // Extract JWT token after "Bearer "
        
        if (!validateJWT(token))
        {
            response(res, 403, "text/html", "Invalid token");
            return AuthorizationResults::INVALID_TOKEN;
        }
        

        LoginResult result = getUserNameFromToken(token); // Assuming this function extracts the username from the JWT payload
        if (result.Result == LoginResults::AdminUser)
        {
            return AuthorizationResults::SUCCESFULL;
        }
        
        if (result.Result == LoginResults::UsernameNotExists)
        {
            response(res, 403, "text/html", result.getMessage());
            return AuthorizationResults::USER_NOT_EXISTS;
        }            
        username = result.getMessage();
        if (!checkUserPermission(username, permission))
        {
            response(res, 403, "text/html", "User does not have the required permission");
            return AuthorizationResults::USER_NO_PERMISSION;
        }
        return AuthorizationResults::SUCCESFULL;
    }
    else
    {
        return AuthorizationResults::SUCCESFULL;
    }
    response(res, 500, "text/html", "some error happend");
    return AuthorizationResults::ERROR;
}


void Security::addPermissionForAdmin(String title, String group)
{
    addPermission(sysAdmin_role_id, title, group);
    addPermission(admin_role_id, title, group);
}

void Security::addPermission(int role_id, String title, String group)
{
    RolePermissionController* rolePermissionController = new RolePermissionController(context, storageType);
    PermissionController* permissionController = new PermissionController(context, storageType);

    std::vector<PermissionEntity> permissions = permissionController->Get(String(PermissionEntity::COLUMN_PERMISSIONGROUP + "=") + String(group + " AND ") + String(PermissionEntity::COLUMN_PERMISSIONNAME + "=")+title);
    if (permissions.size() > 0)
    {
        return;
    }
        
    RolePermissionEntity* rolePermission;
    PermissionEntity* permission;
    
    permission = new PermissionEntity(title, group);
    
    int permission_id = permissionController->Add(*permission);

    rolePermission = new RolePermissionEntity(role_id, permission_id);

    rolePermissionController->Add(*rolePermission);
}

LoginResult Security::generateJWT(UserEntity user) {
    // Construct the payload string using the provided username
    String payload = user.GetValue(UserEntity::COLUMN_USERNAME);
    // For now, let's assume pin is static. You can modify this
    
    // Initialize the hash with SECRET_KEY
    HMACAuth auth(SECRET_KEY);
    
    // Update hash with payload and pin
    auth.updateHash(payload.c_str());
    auth.updateHash(pin);

    // Finalize and get the hashed and encoded result
    String jwtResult = auth.finalizeHash();
    
    // Assuming you store this result in the user entity or wherever necessary
    LoginResult loginResult = LoginResult(true, LoginResults::Succesfull);
    loginResult.Message = jwtResult;
    
    return loginResult;
}

bool Security::validateJWT(String jwtString) {
    // Decode from Base64
    return true;
    unsigned char decodedOutput[65];
    size_t decodedLength;
    mbedtls_base64_decode(decodedOutput, sizeof(decodedOutput), &decodedLength, (unsigned char *)jwtString.c_str(), jwtString.length());
    
    // Extract payload from decoded value (assuming it's the first part)
    String payload = String((char *)decodedOutput).substring(0, jwtString.length() - strlen("6577"));  // Adjust as per actual structure
    
    // Recompute hash
    HMACAuth auth(SECRET_KEY);

    auth.updateHash(payload.c_str());
    auth.updateHash("6577"); // Assuming pin is static
    String recomputedJWT = auth.finalizeHash();
    
    return jwtString == recomputedJWT;
}
#endif //SECURITY_H
