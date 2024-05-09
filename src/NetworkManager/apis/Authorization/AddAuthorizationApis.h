#ifndef ADDAUTHORIZATIONAPIS_H
#define ADDAUTHORIZATIONAPIS_H

#include "AuthorizationPermissions.h"
#include "UserApis.h"
#include "RoleApis.h"
#include "PermissionApis.h"
#include "RolePermissionApis.h"
#include "UserResetPassApis.h"
#include "SecurityQuestionApis.h"
#include "SecurityQuestionTitleApis.h"
#include "LoginAttemptApis.h"
#include "AccountLockoutApis.h"
#include "TwoFactorAuthApis.h"
#include "AccountActivityLogApis.h"
#include "AuthenticationApis.h"
#include "AuthorizationConfigApis.h"


void createAuthorizationApis(Context* context)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();
    
    UserApis* userApis = new UserApis(context, true);
    apis.push_back(userApis);
    
    RoleApis* roleApis = new RoleApis(context, true);
    apis.push_back(roleApis);
    
    PermissionApis* permissionApis = new PermissionApis(context, true);
    apis.push_back(permissionApis);
    
    RolePermissionApis* rolepermissionApis = new RolePermissionApis(context, true);
    apis.push_back(rolepermissionApis);
    
    // UserResetPassApis* userresetpassApis = new UserResetPassApis(context, true);
    // apis.push_back(userresetpassApis);
    
    // SecurityQuestionApis* securityquestionApis = new SecurityQuestionApis(context, true);
    // apis.push_back(securityquestionApis);
    
    // SecurityQuestionTitleApis* securityquestiontitleApis = new SecurityQuestionTitleApis(context, true);
    // apis.push_back(securityquestiontitleApis);
    
    // LoginAttemptApis* loginattemptApis = new LoginAttemptApis(context, true);
    // apis.push_back(loginattemptApis);
    
    // AccountLockoutApis* accountlockoutApis = new AccountLockoutApis(context, true);
    // apis.push_back(accountlockoutApis);
    
    AuthenticationApis* authenticationApis = new AuthenticationApis(context, true);
    apis.push_back(authenticationApis);

    AuthenticatioConfigApis* authenticatioConfigApis = new AuthenticatioConfigApis(context, true);
    apis.push_back(authenticatioConfigApis);

    
    // TwoFactorAuthApis* twofactorauthApis = new TwoFactorAuthApis(context, true);
    // apis.push_back(twofactorauthApis);
    
    // AccountActivityLogApis* accountactivitylogApis = new AccountActivityLogApis(context, true);
    // apis.push_back(accountactivitylogApis);
    

    context->getNetwork()->addApis(apis);
}

#endif //ADDAUTHORIZATIONAPIS_H
    