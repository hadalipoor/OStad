#ifndef ACCOUNTLOCKOUTAPIS_h
#define ACCOUNTLOCKOUTAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/AccountLockoutController.h"
#include "../../../Security/AuthorizationPermissions.h"

class AccountLockoutApis : public ApiInterface
{
private:
    Context* context;
    AccountLockoutController* accountlockoutController;
    std::string class_path = "/accountlockout";

public:
    AccountLockoutApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, EBPDateTime LockoutStartTime, EBPDateTime LockoutEndTime);
    String handleupdate(int id, int UserId, EBPDateTime LockoutStartTime, EBPDateTime LockoutEndTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

AccountLockoutApis::AccountLockoutApis(Context* cntxt, bool add_apis): context(cntxt) {
    accountlockoutController = new AccountLockoutController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("LockoutStartTime") || !req->getParams()->isQueryParameterSet("LockoutEndTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string LockoutStartTime;
        req->getParams()->getQueryParameter("LockoutStartTime", LockoutStartTime);
    std::string LockoutEndTime;
        req->getParams()->getQueryParameter("LockoutEndTime", LockoutEndTime);

        response(res, handlecreate(String(UserId.c_str()).toInt(), String(LockoutStartTime.c_str()), String(LockoutEndTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("LockoutStartTime") || !req->getParams()->isQueryParameterSet("LockoutEndTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string LockoutStartTime;
        req->getParams()->getQueryParameter("LockoutStartTime", LockoutStartTime);
    std::string LockoutEndTime;
        req->getParams()->getQueryParameter("LockoutEndTime", LockoutEndTime);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(UserId.c_str()).toInt(), String(LockoutStartTime.c_str()), String(LockoutEndTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_DELETE)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_GET)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ACCOUNTLOCKOUT_GET)){return;}
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

String AccountLockoutApis::getClassPath()
{
    return String(class_path.c_str());
}

String AccountLockoutApis::handlecreate(int UserId, EBPDateTime LockoutStartTime, EBPDateTime LockoutEndTime) {
    AccountLockoutEntity* accountlockoutEntity = new AccountLockoutEntity(UserId, LockoutStartTime, LockoutEndTime);
    int id = accountlockoutController->Add(*accountlockoutEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}
String AccountLockoutApis::handleupdate(int id, int UserId, EBPDateTime LockoutStartTime, EBPDateTime LockoutEndTime) {
    AccountLockoutEntity* accountlockoutEntity = new AccountLockoutEntity(id, UserId, LockoutStartTime, LockoutEndTime);
    
    if (accountlockoutController->Update(*accountlockoutEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String AccountLockoutApis::handledelete(int id) {
    
    if (accountlockoutController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String AccountLockoutApis::handlegetAll() {
    return accountlockoutController->GetAllJson();
}
String AccountLockoutApis::handlegetById(int id) {
    return accountlockoutController->GetById(id).toJson();
}
String AccountLockoutApis::handleget(String query) {
    return accountlockoutController->GetJson(query);
}

String AccountLockoutApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["LockoutStartTime"], parameters["LockoutEndTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["LockoutStartTime"], parameters["LockoutEndTime"]);
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

#endif //ACCOUNTLOCKOUTApis_h

    