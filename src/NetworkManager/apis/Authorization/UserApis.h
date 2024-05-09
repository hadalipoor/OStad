#ifndef USERAPIS_h
#define USERAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/UserController.h"
#include "AuthorizationPermissions.h"

class UserApis : public ApiInterface
{
private:
    Context* context;
    UserController* userController;
    std::string class_path = "/user";

public:
    UserApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime);
    String handleupdate(int id, String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

UserApis::UserApis(Context* cntxt, bool add_apis): context(cntxt) {
    userController = new UserController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("Username") || !req->getParams()->isQueryParameterSet("Password") || !req->getParams()->isQueryParameterSet("Email") || !req->getParams()->isQueryParameterSet("PhoneNumber") || !req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("TwoFactorAuth") || !req->getParams()->isQueryParameterSet("ApiKey") || !req->getParams()->isQueryParameterSet("Token") || !req->getParams()->isQueryParameterSet("TokenExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string Username;
        req->getParams()->getQueryParameter("Username", Username);
    std::string Password;
        req->getParams()->getQueryParameter("Password", Password);
    std::string Email;
        req->getParams()->getQueryParameter("Email", Email);
    std::string PhoneNumber;
        req->getParams()->getQueryParameter("PhoneNumber", PhoneNumber);
    std::string RoleId;
        req->getParams()->getQueryParameter("RoleId", RoleId);
    std::string TwoFactorAuth;
        req->getParams()->getQueryParameter("TwoFactorAuth", TwoFactorAuth);
    std::string ApiKey;
        req->getParams()->getQueryParameter("ApiKey", ApiKey);
    std::string Token;
        req->getParams()->getQueryParameter("Token", Token);
    std::string TokenExpiryTime;
        req->getParams()->getQueryParameter("TokenExpiryTime", TokenExpiryTime);

        response(res, handlecreate(String(Username.c_str()), String(Password.c_str()), String(Email.c_str()), String(PhoneNumber.c_str()), String(RoleId.c_str()).toInt(), String(TwoFactorAuth.c_str()).toInt(), String(ApiKey.c_str()), String(Token.c_str()), String(TokenExpiryTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Username") || !req->getParams()->isQueryParameterSet("Password") || !req->getParams()->isQueryParameterSet("Email") || !req->getParams()->isQueryParameterSet("PhoneNumber") || !req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("TwoFactorAuth") || !req->getParams()->isQueryParameterSet("ApiKey") || !req->getParams()->isQueryParameterSet("Token") || !req->getParams()->isQueryParameterSet("TokenExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string Username;
        req->getParams()->getQueryParameter("Username", Username);
    std::string Password;
        req->getParams()->getQueryParameter("Password", Password);
    std::string Email;
        req->getParams()->getQueryParameter("Email", Email);
    std::string PhoneNumber;
        req->getParams()->getQueryParameter("PhoneNumber", PhoneNumber);
    std::string RoleId;
        req->getParams()->getQueryParameter("RoleId", RoleId);
    std::string TwoFactorAuth;
        req->getParams()->getQueryParameter("TwoFactorAuth", TwoFactorAuth);
    std::string ApiKey;
        req->getParams()->getQueryParameter("ApiKey", ApiKey);
    std::string Token;
        req->getParams()->getQueryParameter("Token", Token);
    std::string TokenExpiryTime;
        req->getParams()->getQueryParameter("TokenExpiryTime", TokenExpiryTime);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(Username.c_str()), String(Password.c_str()), String(Email.c_str()), String(PhoneNumber.c_str()), String(RoleId.c_str()).toInt(), String(TwoFactorAuth.c_str()).toInt(), String(ApiKey.c_str()), String(Token.c_str()), String(TokenExpiryTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_DELETE)){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string id;
        req->getParams()->getQueryParameter("id", id);
        
        response(res, handledelete(String(id.c_str()).toInt()));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_GET)){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        
        response(res, handlegetById(String(id.c_str()).toInt()));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USER_GET)){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string query;
        req->getParams()->getQueryParameter("query", query);
        
        response(res, handleget(String(query.c_str())));
    }));
}

String UserApis::getClassPath()
{
    return String(class_path.c_str());
}

String UserApis::handlecreate(String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime) {
    UserEntity* userEntity = new UserEntity(Username, Password, Email, PhoneNumber, RoleId, TwoFactorAuth, ApiKey, Token, TokenExpiryTime);
    int id = userController->Add(*userEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}
String UserApis::handleupdate(int id, String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime) {
    UserEntity* userEntity = new UserEntity(id, Username, Password, Email, PhoneNumber, RoleId, TwoFactorAuth, ApiKey, Token, TokenExpiryTime);
    
    if (userController->Update(*userEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String UserApis::handledelete(int id) {
    
    if (userController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String UserApis::handlegetAll() {
    return userController->GetAllJson();
}
String UserApis::handlegetById(int id) {
    return userController->GetById(id).toJson();
}
String UserApis::handleget(String query) {
    return userController->GetJson(query);
}

String UserApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Username"], parameters["Password"], parameters["Email"], parameters["PhoneNumber"], parameters["RoleId"].toInt(), parameters["TwoFactorAuth"].toInt(), parameters["ApiKey"], parameters["Token"], parameters["TokenExpiryTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Username"], parameters["Password"], parameters["Email"], parameters["PhoneNumber"], parameters["RoleId"].toInt(), parameters["TwoFactorAuth"].toInt(), parameters["ApiKey"], parameters["Token"], parameters["TokenExpiryTime"]);
    }
    if (functionName == "delete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "getAll") {
        return handlegetAll();
    }
    if (functionName == "getById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "get") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //USERApis_h

    