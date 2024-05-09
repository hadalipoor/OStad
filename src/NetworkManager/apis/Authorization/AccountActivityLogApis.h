#ifndef ACCOUNTACTIVITYLOGAPIS_h
#define ACCOUNTACTIVITYLOGAPIS_h


#include "../../../Context.h"
#include "../../../Database/Controllers/Security/AccountActivityLogController.h"
#include "AuthorizationPermissions.h"

class AccountActivityLogApis : public ApiInterface
{
private:
    Context* context;
    AccountActivityLogController* accountactivitylogController;
    std::string class_path = "/accountactivitylog";

public:
    AccountActivityLogApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, String Activity, EBPDateTime Timestamp);
    String handleupdate(int id, int UserId, String Activity, EBPDateTime Timestamp);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

AccountActivityLogApis::AccountActivityLogApis(Context* cntxt, bool add_apis): context(cntxt) {
    accountactivitylogController = new AccountActivityLogController(context, storageType);
    
    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Activity") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string Activity;
        req->getParams()->getQueryParameter("Activity", Activity);
    std::string Timestamp;
        req->getParams()->getQueryParameter("Timestamp", Timestamp);

        response(res, handlecreate(String(UserId.c_str()).toInt(), String(Activity.c_str()), String(Timestamp.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Activity") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string Activity;
        req->getParams()->getQueryParameter("Activity", Activity);
    std::string Timestamp;
        req->getParams()->getQueryParameter("Timestamp", Timestamp);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(UserId.c_str()).toInt(), String(Activity.c_str()), String(Timestamp.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_DELETE)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_GET)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTACTIVITYLOG_GET)){return;}
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

String AccountActivityLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String AccountActivityLogApis::handlecreate(int UserId, String Activity, EBPDateTime Timestamp) {
    AccountActivityLogEntity* accountactivitylogEntity = new AccountActivityLogEntity(UserId, Activity, Timestamp);
    int id = accountactivitylogController->Add(*accountactivitylogEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}
String AccountActivityLogApis::handleupdate(int id, int UserId, String Activity, EBPDateTime Timestamp) {
    AccountActivityLogEntity* accountactivitylogEntity = new AccountActivityLogEntity(id, UserId, Activity, Timestamp);
    
    if (accountactivitylogController->Update(*accountactivitylogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String AccountActivityLogApis::handledelete(int id) {
    
    if (accountactivitylogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String AccountActivityLogApis::handlegetAll() {
    return accountactivitylogController->GetAllJson();
}
String AccountActivityLogApis::handlegetById(int id) {
    return accountactivitylogController->GetById(id).toJson();
}
String AccountActivityLogApis::handleget(String query) {
    return accountactivitylogController->GetJson(query);
}

String AccountActivityLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["Activity"], parameters["Timestamp"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["Activity"], parameters["Timestamp"]);
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

#endif //ACCOUNTACTIVITYLOGApis_h

    