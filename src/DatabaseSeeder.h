#ifndef DATABASESEEDER_H
#define DATABASESEEDER_H

#include "Context.h"
#include "Database/Controllers/Security/PermissionController.h"
#include "Database/Controllers/Security/RoleController.h"
#include "Database/Controllers/Security/RolePermissionController.h"
#include "Database/Controllers/Security/UserController.h"

#include "Security/AuthorizationPermissions.h"

class DatabaseSeeder
{
private:
    Context* context;
public:
    DatabaseSeeder(Context* context);
    ~DatabaseSeeder();
    void seed();
};

DatabaseSeeder::DatabaseSeeder(Context* context): context(context)
{

}

DatabaseSeeder::~DatabaseSeeder()
{
}

void DatabaseSeeder::seed()
{
    long start_millis = millis();

    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USER_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USER_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USER_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USER_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLE_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLE_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLE_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLE_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::PERMISSION_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::PERMISSION_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::PERMISSION_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::PERMISSION_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLEPERMISSION_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLEPERMISSION_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLEPERMISSION_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ROLEPERMISSION_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USERRESETPASS_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USERRESETPASS_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USERRESETPASS_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::USERRESETPASS_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTION_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTION_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTION_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTION_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTIONTITLE_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTIONTITLE_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTIONTITLE_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::SECURITYQUESTIONTITLE_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::LOGINATTEMPT_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::LOGINATTEMPT_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::LOGINATTEMPT_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::LOGINATTEMPT_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTLOCKOUT_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTLOCKOUT_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTLOCKOUT_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTLOCKOUT_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TWOFACTORAUTH_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TWOFACTORAUTH_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TWOFACTORAUTH_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TWOFACTORAUTH_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTACTIVITYLOG_CREATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTACTIVITYLOG_UPDATE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTACTIVITYLOG_DELETE, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::ACCOUNTACTIVITYLOG_GET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_LOGIN, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_PASSWORDRESET, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_PASSWORDRESETCONFIRM, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_TWOFACTORAUTH, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_TWOFACTORAUTHCONFIRM, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_ACCOUNTLOCK, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_ACCOUNTUNLOCK, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AUTHENTICATION_SECURITYQUESTIONANSWER, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TESTREQUESTS_ADDDATA, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TESTREQUESTS_GETDATA, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::TESTREQUESTS_PUBLICREQUEST, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::GetData, "Security Permissions");
    context->getSecurity()->addPermissionForAdmin(AuthorizationPermissions::AddData, "Security Permissions");

    long passed_millis = millis() - start_millis;
    
    Serial.print("Seeding System Database finished in ");Serial.print(passed_millis);Serial.println(" miliseconds.");
}

#endif //DATABASESEEDER_H