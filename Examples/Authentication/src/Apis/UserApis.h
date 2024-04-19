#ifndef USERAPIS_h
#define USERAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/UserController.h"
#include "Permissions.h"

class UserApis : public ApiInterface
{
private:
    AppContext* context;
    UserController* userController;
    std::string class_path = "/user";

public:
    UserApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime);
    String handleupdate(int id, String Username, String Password, String Email, String PhoneNumber, int RoleId, bool TwoFactorAuth, String ApiKey, String Token, EBPDateTime TokenExpiryTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

UserApis::UserApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    userController = new UserController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Username") || !req->getParams()->isQueryParameterSet("Password") || !req->getParams()->isQueryParameterSet("Email") || !req->getParams()->isQueryParameterSet("PhoneNumber") || !req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("TwoFactorAuth") || !req->getParams()->isQueryParameterSet("ApiKey") || !req->getParams()->isQueryParameterSet("Token") || !req->getParams()->isQueryParameterSet("TokenExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Username = getQueryParameterString(req, "Username");
    String Password = getQueryParameterString(req, "Password");
    String Email = getQueryParameterString(req, "Email");
    String PhoneNumber = getQueryParameterString(req, "PhoneNumber");
    int RoleId = getQueryParameterint(req, "RoleId");
    bool TwoFactorAuth = getQueryParameterbool(req, "TwoFactorAuth");
    String ApiKey = getQueryParameterString(req, "ApiKey");
    String Token = getQueryParameterString(req, "Token");
    EBPDateTime TokenExpiryTime = getQueryParameterEBPDateTime(req, "TokenExpiryTime");

        response(res, handlecreate(Username, Password, Email, PhoneNumber, RoleId, TwoFactorAuth, ApiKey, Token, TokenExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Username") || !req->getParams()->isQueryParameterSet("Password") || !req->getParams()->isQueryParameterSet("Email") || !req->getParams()->isQueryParameterSet("PhoneNumber") || !req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("TwoFactorAuth") || !req->getParams()->isQueryParameterSet("ApiKey") || !req->getParams()->isQueryParameterSet("Token") || !req->getParams()->isQueryParameterSet("TokenExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Username = getQueryParameterString(req, "Username");
    String Password = getQueryParameterString(req, "Password");
    String Email = getQueryParameterString(req, "Email");
    String PhoneNumber = getQueryParameterString(req, "PhoneNumber");
    int RoleId = getQueryParameterint(req, "RoleId");
    bool TwoFactorAuth = getQueryParameterbool(req, "TwoFactorAuth");
    String ApiKey = getQueryParameterString(req, "ApiKey");
    String Token = getQueryParameterString(req, "Token");
    EBPDateTime TokenExpiryTime = getQueryParameterEBPDateTime(req, "TokenExpiryTime");
        
        response(res, handleupdate(id, Username, Password, Email, PhoneNumber, RoleId, TwoFactorAuth, ApiKey, Token, TokenExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USER_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
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
        return CREATE_SUCCESFULL_MESSAGE;
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

    