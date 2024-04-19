#ifndef USERRESETPASSAPIS_h
#define USERRESETPASSAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/UserResetPassController.h"
#include "Permissions.h"

class UserResetPassApis : public ApiInterface
{
private:
    AppContext* context;
    UserResetPassController* userresetpassController;
    std::string class_path = "/userresetpass";

public:
    UserResetPassApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, String ResetToken, EBPDateTime ExpiryTime);
    String handleupdate(int id, int UserId, String ResetToken, EBPDateTime ExpiryTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

UserResetPassApis::UserResetPassApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    userresetpassController = new UserResetPassController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("ResetToken") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int UserId = getQueryParameterint(req, "UserId");
    String ResetToken = getQueryParameterString(req, "ResetToken");
    EBPDateTime ExpiryTime = getQueryParameterEBPDateTime(req, "ExpiryTime");

        response(res, handlecreate(UserId, ResetToken, ExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("ResetToken") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int UserId = getQueryParameterint(req, "UserId");
    String ResetToken = getQueryParameterString(req, "ResetToken");
    EBPDateTime ExpiryTime = getQueryParameterEBPDateTime(req, "ExpiryTime");
        
        response(res, handleupdate(id, UserId, ResetToken, ExpiryTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::USERRESETPASS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String UserResetPassApis::getClassPath()
{
    return String(class_path.c_str());
}

String UserResetPassApis::handlecreate(int UserId, String ResetToken, EBPDateTime ExpiryTime) {
    UserResetPassEntity* userresetpassEntity = new UserResetPassEntity(UserId, ResetToken, ExpiryTime);
    int id = userresetpassController->Add(*userresetpassEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String UserResetPassApis::handleupdate(int id, int UserId, String ResetToken, EBPDateTime ExpiryTime) {
    UserResetPassEntity* userresetpassEntity = new UserResetPassEntity(id, UserId, ResetToken, ExpiryTime);
    
    if (userresetpassController->Update(*userresetpassEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String UserResetPassApis::handledelete(int id) {
    
    if (userresetpassController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String UserResetPassApis::handlegetAll() {
    return userresetpassController->GetAllJson();
}
String UserResetPassApis::handlegetById(int id) {
    return userresetpassController->GetById(id).toJson();
}
String UserResetPassApis::handleget(String query) {
    return userresetpassController->GetJson(query);
}

String UserResetPassApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["ResetToken"], parameters["ExpiryTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["ResetToken"], parameters["ExpiryTime"]);
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

#endif //USERRESETPASSApis_h

    