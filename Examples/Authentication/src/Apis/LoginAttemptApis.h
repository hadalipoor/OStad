#ifndef LOGINATTEMPTAPIS_h
#define LOGINATTEMPTAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/LoginAttemptController.h"
#include "Permissions.h"

class LoginAttemptApis : public ApiInterface
{
private:
    AppContext* context;
    LoginAttemptController* loginattemptController;
    std::string class_path = "/loginattempt";

public:
    LoginAttemptApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, EBPDateTime Timestamp);
    String handleupdate(int id, int UserId, EBPDateTime Timestamp);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LoginAttemptApis::LoginAttemptApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    loginattemptController = new LoginAttemptController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int UserId = getQueryParameterint(req, "UserId");
    EBPDateTime Timestamp = getQueryParameterEBPDateTime(req, "Timestamp");

        response(res, handlecreate(UserId, Timestamp));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int UserId = getQueryParameterint(req, "UserId");
    EBPDateTime Timestamp = getQueryParameterEBPDateTime(req, "Timestamp");
        
        response(res, handleupdate(id, UserId, Timestamp));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGINATTEMPT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LoginAttemptApis::getClassPath()
{
    return String(class_path.c_str());
}

String LoginAttemptApis::handlecreate(int UserId, EBPDateTime Timestamp) {
    LoginAttemptEntity* loginattemptEntity = new LoginAttemptEntity(UserId, Timestamp);
    int id = loginattemptController->Add(*loginattemptEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LoginAttemptApis::handleupdate(int id, int UserId, EBPDateTime Timestamp) {
    LoginAttemptEntity* loginattemptEntity = new LoginAttemptEntity(id, UserId, Timestamp);
    
    if (loginattemptController->Update(*loginattemptEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LoginAttemptApis::handledelete(int id) {
    
    if (loginattemptController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LoginAttemptApis::handlegetAll() {
    return loginattemptController->GetAllJson();
}
String LoginAttemptApis::handlegetById(int id) {
    return loginattemptController->GetById(id).toJson();
}
String LoginAttemptApis::handleget(String query) {
    return loginattemptController->GetJson(query);
}

String LoginAttemptApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["Timestamp"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["Timestamp"]);
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

#endif //LOGINATTEMPTApis_h

    