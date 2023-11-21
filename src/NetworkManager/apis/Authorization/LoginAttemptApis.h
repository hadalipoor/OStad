#ifndef LOGINATTEMPTAPIS_h
#define LOGINATTEMPTAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/LoginAttemptController.h"
#include "../../../Security/AuthorizationPermissions.h"

class LoginAttemptApis : public ApiInterface
{
private:
    Context* context;
    LoginAttemptController* loginattemptController;
    std::string class_path = "/loginattempt";

public:
    LoginAttemptApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, EBPDateTime Timestamp);
    String handleupdate(int id, int UserId, EBPDateTime Timestamp);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LoginAttemptApis::LoginAttemptApis(Context* cntxt, bool add_apis): context(cntxt) {
    loginattemptController = new LoginAttemptController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string Timestamp;
        req->getParams()->getQueryParameter("Timestamp", Timestamp);

        response(res, handlecreate(String(UserId.c_str()).toInt(), String(Timestamp.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("Timestamp"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string Timestamp;
        req->getParams()->getQueryParameter("Timestamp", Timestamp);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(UserId.c_str()).toInt(), String(Timestamp.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_DELETE)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_GET)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::LOGINATTEMPT_GET)){return;}
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

String LoginAttemptApis::getClassPath()
{
    return String(class_path.c_str());
}

String LoginAttemptApis::handlecreate(int UserId, EBPDateTime Timestamp) {
    LoginAttemptEntity* loginattemptEntity = new LoginAttemptEntity(UserId, Timestamp);
    int id = loginattemptController->Add(*loginattemptEntity);
    if (id != -1)
    {
        return String(id);
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
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["UserId"].toInt(), parameters["Timestamp"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["Timestamp"]);
    }
    if (functionName == "handledelete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "handlegetAll") {
        return handlegetAll();
    }
    if (functionName == "handlegetById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "handleget") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //LOGINATTEMPTApis_h

    