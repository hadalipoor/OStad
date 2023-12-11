#ifndef ROLEPERMISSIONAPIS_h
#define ROLEPERMISSIONAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Security/RolePermissionController.h"
#include "../../../Security/AuthorizationPermissions.h"

class RolePermissionApis : public ApiInterface
{
private:
    Context* context;
    RolePermissionController* rolepermissionController;
    std::string class_path = "/rolepermission";

public:
    RolePermissionApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int RoleId, int PermissionId);
    String handleupdate(int id, int RoleId, int PermissionId);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RolePermissionApis::RolePermissionApis(Context* cntxt, bool add_apis): context(cntxt) {
    rolepermissionController = new RolePermissionController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_CREATE)){return;}
        if (!req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("PermissionId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        std::string RoleId;
        req->getParams()->getQueryParameter("RoleId", RoleId);
    std::string PermissionId;
        req->getParams()->getQueryParameter("PermissionId", PermissionId);

        response(res, handlecreate(String(RoleId.c_str()).toInt(), String(PermissionId.c_str()).toInt()));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_UPDATE)){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("RoleId") || !req->getParams()->isQueryParameterSet("PermissionId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string RoleId;
        req->getParams()->getQueryParameter("RoleId", RoleId);
    std::string PermissionId;
        req->getParams()->getQueryParameter("PermissionId", PermissionId);
        
        response(res, handleupdate(String(id.c_str()).toInt(), String(RoleId.c_str()).toInt(), String(PermissionId.c_str()).toInt()));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_DELETE)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_GET)){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_GET)){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, AuthorizationPermissions::ROLEPERMISSION_GET)){return;}
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

String RolePermissionApis::getClassPath()
{
    return String(class_path.c_str());
}

String RolePermissionApis::handlecreate(int RoleId, int PermissionId) {
    RolePermissionEntity* rolepermissionEntity = new RolePermissionEntity(RoleId, PermissionId);
    int id = rolepermissionController->Add(*rolepermissionEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}
String RolePermissionApis::handleupdate(int id, int RoleId, int PermissionId) {
    RolePermissionEntity* rolepermissionEntity = new RolePermissionEntity(id, RoleId, PermissionId);
    
    if (rolepermissionController->Update(*rolepermissionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String RolePermissionApis::handledelete(int id) {
    
    if (rolepermissionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String RolePermissionApis::handlegetAll() {
    return rolepermissionController->GetAllJson();
}
String RolePermissionApis::handlegetById(int id) {
    return rolepermissionController->GetById(id).toJson();
}
String RolePermissionApis::handleget(String query) {
    return rolepermissionController->GetJson(query);
}

String RolePermissionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["RoleId"].toInt(), parameters["PermissionId"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["RoleId"].toInt(), parameters["PermissionId"].toInt());
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

#endif //ROLEPERMISSIONApis_h

    