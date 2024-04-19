
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "AuthenticationApis.h"
#include "TestRequestsApis.h"
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


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    AuthenticationApis* authenticationApis = new AuthenticationApis(appContext, true);
    apis.push_back(authenticationApis);
    
    TestRequestsApis* testrequestsApis = new TestRequestsApis(appContext, true);
    apis.push_back(testrequestsApis);
    
    UserApis* userApis = new UserApis(appContext, true);
    apis.push_back(userApis);
    
    RoleApis* roleApis = new RoleApis(appContext, true);
    apis.push_back(roleApis);
    
    PermissionApis* permissionApis = new PermissionApis(appContext, true);
    apis.push_back(permissionApis);
    
    RolePermissionApis* rolepermissionApis = new RolePermissionApis(appContext, true);
    apis.push_back(rolepermissionApis);
    
    UserResetPassApis* userresetpassApis = new UserResetPassApis(appContext, true);
    apis.push_back(userresetpassApis);
    
    SecurityQuestionApis* securityquestionApis = new SecurityQuestionApis(appContext, true);
    apis.push_back(securityquestionApis);
    
    SecurityQuestionTitleApis* securityquestiontitleApis = new SecurityQuestionTitleApis(appContext, true);
    apis.push_back(securityquestiontitleApis);
    
    LoginAttemptApis* loginattemptApis = new LoginAttemptApis(appContext, true);
    apis.push_back(loginattemptApis);
    
    AccountLockoutApis* accountlockoutApis = new AccountLockoutApis(appContext, true);
    apis.push_back(accountlockoutApis);
    
    TwoFactorAuthApis* twofactorauthApis = new TwoFactorAuthApis(appContext, true);
    apis.push_back(twofactorauthApis);
    
    AccountActivityLogApis* accountactivitylogApis = new AccountActivityLogApis(appContext, true);
    apis.push_back(accountactivitylogApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    