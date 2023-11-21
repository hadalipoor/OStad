
#ifndef AuthenticationApis_h
#define AuthenticationApis_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/LoginAttemptController.h"
#include "../../../Security/AuthorizationPermissions.h"

class AuthenticationApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/authentication";

public:
    AuthenticationApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    void handlelogin(HTTPResponse * res, String username, String password);
    String handlelogin(String username, String password);
    String handlelogout(String username);
    String handlepasswordReset(String username);
    String handlepasswordResetConfirm(String username, String reset_token, String new_password);
    String handletwoFactorAuth(String username);
    String handletwoFactorAuthConfirm(String username, String otp_code);
    String handleaccountLock(String username);
    String handleaccountUnlock(String username);
    String handlesecurityQuestionAnswer(String username, String question_id, String answer);
};

AuthenticationApis::AuthenticationApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/login"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLE_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("username") || !req->getParams()->isQueryParameterSet("password"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String username = getQueryParameterString(req, "username");
        String password = getQueryParameterString(req, "password");
        
        handlelogin(res, username, password);
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/logout"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::GetData)){return;}

        if (!req->getParams()->isQueryParameterSet("username"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String username = getQueryParameterString(req, "username");
        
        response(res, handlelogout(username)); 
    }));

    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/passwordReset"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!request->hasParam("username"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }

    //     String username = request->getParam("username")->value();
        
    //     request->send(200, "text/html", handlepasswordReset(username));
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/passwordResetConfirm"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!request->hasParam("username") || !request->hasParam("new_password") || !request->hasParam("token"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     String reset_token = request->getParam("token")->value();
    //     String new_password = request->getParam("new_password")->value();
        
    //     request->send(200, "text/html", handlepasswordResetConfirm(username, reset_token, new_password));
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/twoFactorAuth"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!request->hasParam("username"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     handletwoFactorAuth(username);
    //     request->send(200, "text/html", "Successful");
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/twoFactorAuthConfirm"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!request->hasParam("username") || !request->hasParam("otp_code"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     String otp_code = request->getParam("otp_code")->value();
        
    //     request->send(200, "text/html", handletwoFactorAuthConfirm(username, otp_code));
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/accountLock"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!context->getSecurity()->checkAuthentication(request, AuthorizationPermissions::AUTHENTICATION_ACCOUNTLOCK)){return;}
    //     if (!request->hasParam("username"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     handleaccountLock(username);
    //     request->send(200, "text/html", "Successful");
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/accountUnlock"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!context->getSecurity()->checkAuthentication(request, AuthorizationPermissions::AUTHENTICATION_ACCOUNTUNLOCK)){return;}
    //     if (!request->hasParam("username"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     handleaccountUnlock(username);
    //     request->send(200, "text/html", "Successful");
    // }));
    // context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/securityQuestionAnswer"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
    //     if (!request->hasParam("username") || !request->hasParam("question_id") || !request->hasParam("answer"))
    //     {
    //         request->send(400, "text/html", "missing some input params in your request");
    //     }
    //     String username = request->getParam("username")->value();
    //     String question_id = request->getParam("question_id")->value();
    //     String answer = request->getParam("answer")->value();
    //     handlesecurityQuestionAnswer(username, question_id, answer);
    //     request->send(200, "text/html", "Successful");
    // }));
}

String AuthenticationApis::getClassPath()
{
    return String(class_path.c_str());
}



String AuthenticationApis::handlelogin(String username, String password) {
    return context->getSecurity()->login(username, password).getMessage();
}

void AuthenticationApis::handlelogin(HTTPResponse * res, String username, String password) {
    LoginResult result = context->getSecurity()->login(username, password);
    if (result.Succesfull)
    {
        response(res, result.getMessage());
    }
    else{
        response(res, 401, result.getMessage());
    }
    
}

String AuthenticationApis::handlelogout(String username) {
    return context->getSecurity()->logout(username).getMessage();
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
    if (functionName == "handlelogout") {
        return handlelogout(parameters["username"]);
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