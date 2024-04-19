
#ifndef AuthenticationApis_h
#define AuthenticationApis_h


#include "../AppContext.h"
#include "Permissions.h"
class AuthenticationApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/authentication";

public:
    AuthenticationApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlelogin(String username, String password);
    String handlepasswordReset(String username);
    String handlepasswordResetConfirm(String username, String reset_token, String new_password);
    String handletwoFactorAuth(String username);
    String handletwoFactorAuthConfirm(String username, String otp_code);
    String handleaccountLock(String username);
    String handleaccountUnlock(String username);
    String handlesecurityQuestionAnswer(String username, String question_id, String answer);
};

AuthenticationApis::AuthenticationApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/login"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_LOGIN) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username") || !req->getParams()->isQueryParameterSet("password")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        String password = getQueryParameterString(req, "password");
        
        response(res, handlelogin(username, password));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/passwordReset"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_PASSWORDRESET) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        
        response(res, handlepasswordReset(username));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/passwordResetConfirm"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_PASSWORDRESETCONFIRM) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username") || !req->getParams()->isQueryParameterSet("reset_token") || !req->getParams()->isQueryParameterSet("new_password")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        String reset_token = getQueryParameterString(req, "reset_token");
        String new_password = getQueryParameterString(req, "new_password");
        
        response(res, handlepasswordResetConfirm(username, reset_token, new_password));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/twoFactorAuth"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_TWOFACTORAUTH) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        
        response(res, handletwoFactorAuth(username));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/twoFactorAuthConfirm"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_TWOFACTORAUTHCONFIRM) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username") || !req->getParams()->isQueryParameterSet("otp_code")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        String otp_code = getQueryParameterString(req, "otp_code");
        
        response(res, handletwoFactorAuthConfirm(username, otp_code));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/accountLock"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_ACCOUNTLOCK) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        
        response(res, handleaccountLock(username));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/accountUnlock"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_ACCOUNTUNLOCK) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        
        response(res, handleaccountUnlock(username));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/securityQuestionAnswer"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::AUTHENTICATION_SECURITYQUESTIONANSWER) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("username") || !req->getParams()->isQueryParameterSet("question_id") || !req->getParams()->isQueryParameterSet("answer")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String username = getQueryParameterString(req, "username");
        String question_id = getQueryParameterString(req, "question_id");
        String answer = getQueryParameterString(req, "answer");
        
        response(res, handlesecurityQuestionAnswer(username, question_id, answer));
    }));
}

String AuthenticationApis::getClassPath()
{
    return String(class_path.c_str());
}



String AuthenticationApis::handlelogin(String username, String password) {
    return "";
}
String AuthenticationApis::handlepasswordReset(String username) {
    return "";
}
String AuthenticationApis::handlepasswordResetConfirm(String username, String reset_token, String new_password) {
    return "";
}
String AuthenticationApis::handletwoFactorAuth(String username) {
    return "";
}
String AuthenticationApis::handletwoFactorAuthConfirm(String username, String otp_code) {
    return "";
}
String AuthenticationApis::handleaccountLock(String username) {
    return "";
}
String AuthenticationApis::handleaccountUnlock(String username) {
    return "";
}
String AuthenticationApis::handlesecurityQuestionAnswer(String username, String question_id, String answer) {
    return "";
}

String AuthenticationApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlelogin") {
        handlelogin(parameters["username"], parameters["password"]);
        return "OK";
    }
    if (functionName == "handlepasswordReset") {
        handlepasswordReset(parameters["username"]);
        return "OK";
    }
    if (functionName == "handlepasswordResetConfirm") {
        handlepasswordResetConfirm(parameters["username"], parameters["reset_token"], parameters["new_password"]);
        return "OK";
    }
    if (functionName == "handletwoFactorAuth") {
        handletwoFactorAuth(parameters["username"]);
        return "OK";
    }
    if (functionName == "handletwoFactorAuthConfirm") {
        handletwoFactorAuthConfirm(parameters["username"], parameters["otp_code"]);
        return "OK";
    }
    if (functionName == "handleaccountLock") {
        handleaccountLock(parameters["username"]);
        return "OK";
    }
    if (functionName == "handleaccountUnlock") {
        handleaccountUnlock(parameters["username"]);
        return "OK";
    }
    if (functionName == "handlesecurityQuestionAnswer") {
        handlesecurityQuestionAnswer(parameters["username"], parameters["question_id"], parameters["answer"]);
        return "OK";
    }
    return "";
}

#endif //AuthenticationApis_h
