#ifndef TWOFACTORAUTHAPIS_h
#define TWOFACTORAUTHAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/TwoFactorAuthController.h"
#include "Permissions.h"

class TwoFactorAuthApis : public ApiInterface
{
private:
    AppContext* context;
    TwoFactorAuthController* twofactorauthController;
    std::string class_path = "/twofactorauth";

public:
    TwoFactorAuthApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, String OtpCode, EBPDateTime ExpiryTime);
    String handleupdate(int id, int UserId, String OtpCode, EBPDateTime ExpiryTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

TwoFactorAuthApis::TwoFactorAuthApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    twofactorauthController = new TwoFactorAuthController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("OtpCode") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int UserId = getQueryParameterint(req, "UserId");
    String OtpCode = getQueryParameterString(req, "OtpCode");
    EBPDateTime ExpiryTime = getQueryParameterEBPDateTime(req, "ExpiryTime");

        response(res, handlecreate(UserId, OtpCode, ExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("OtpCode") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int UserId = getQueryParameterint(req, "UserId");
    String OtpCode = getQueryParameterString(req, "OtpCode");
    EBPDateTime ExpiryTime = getQueryParameterEBPDateTime(req, "ExpiryTime");
        
        response(res, handleupdate(id, UserId, OtpCode, ExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TWOFACTORAUTH_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String TwoFactorAuthApis::getClassPath()
{
    return String(class_path.c_str());
}

String TwoFactorAuthApis::handlecreate(int UserId, String OtpCode, EBPDateTime ExpiryTime) {
    TwoFactorAuthEntity* twofactorauthEntity = new TwoFactorAuthEntity(UserId, OtpCode, ExpiryTime);
    int id = twofactorauthController->Add(*twofactorauthEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String TwoFactorAuthApis::handleupdate(int id, int UserId, String OtpCode, EBPDateTime ExpiryTime) {
    TwoFactorAuthEntity* twofactorauthEntity = new TwoFactorAuthEntity(id, UserId, OtpCode, ExpiryTime);
    
    if (twofactorauthController->Update(*twofactorauthEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String TwoFactorAuthApis::handledelete(int id) {
    
    if (twofactorauthController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String TwoFactorAuthApis::handlegetAll() {
    return twofactorauthController->GetAllJson();
}
String TwoFactorAuthApis::handlegetById(int id) {
    return twofactorauthController->GetById(id).toJson();
}
String TwoFactorAuthApis::handleget(String query) {
    return twofactorauthController->GetJson(query);
}

String TwoFactorAuthApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["OtpCode"], parameters["ExpiryTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["OtpCode"], parameters["ExpiryTime"]);
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

#endif //TWOFACTORAUTHApis_h

    