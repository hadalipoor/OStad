#ifndef USERRESETPASSAPIS_h
#define USERRESETPASSAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/UserResetPassController.h"
#include "../../../Security/AuthorizationPermissions.h"

class UserResetPassApis : public ApiInterface
{
private:
    Context* context;
    UserResetPassController* userresetpassController;
    std::string class_path = "/userresetpass";

public:
    UserResetPassApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, String ResetToken, EBPDateTime ExpiryTime);
    String handleupdate(int id, int UserId, String ResetToken, EBPDateTime ExpiryTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

UserResetPassApis::UserResetPassApis(Context* cntxt, bool add_apis): context(cntxt) {
    userresetpassController = new UserResetPassController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("ResetToken") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string ResetToken;
        req->getParams()->getQueryParameter("ResetToken", ResetToken);
    std::string ExpiryTime;
        req->getParams()->getQueryParameter("ExpiryTime", ExpiryTime);

        response(res, handlecreate(String(UserId.c_str()).toInt(), String(ResetToken.c_str()), String(ExpiryTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("ResetToken") || !req->getParams()->isQueryParameterSet("ExpiryTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string UserId;
        req->getParams()->getQueryParameter("UserId", UserId);
    std::string ResetToken;
        req->getParams()->getQueryParameter("ResetToken", ResetToken);
    std::string ExpiryTime;
        req->getParams()->getQueryParameter("ExpiryTime", ExpiryTime);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(UserId.c_str()).toInt(), String(ResetToken.c_str()), String(ExpiryTime.c_str())));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_DELETE)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_GET)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::USERRESETPASS_GET)){return;}
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

String UserResetPassApis::getClassPath()
{
    return String(class_path.c_str());
}

String UserResetPassApis::handlecreate(int UserId, String ResetToken, EBPDateTime ExpiryTime) {
    UserResetPassEntity* userresetpassEntity = new UserResetPassEntity(UserId, ResetToken, ExpiryTime);
    int id = userresetpassController->Add(*userresetpassEntity);
    if (id != -1)
    {
        return String(id);
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

    