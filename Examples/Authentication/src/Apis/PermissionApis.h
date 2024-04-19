#ifndef PERMISSIONAPIS_h
#define PERMISSIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/PermissionController.h"
#include "Permissions.h"

class PermissionApis : public ApiInterface
{
private:
    AppContext* context;
    PermissionController* permissionController;
    std::string class_path = "/permission";

public:
    PermissionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String PermissionName, String PermissionGroup);
    String handleupdate(int id, String PermissionName, String PermissionGroup);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PermissionApis::PermissionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    permissionController = new PermissionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("PermissionName") || !req->getParams()->isQueryParameterSet("PermissionGroup"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String PermissionName = getQueryParameterString(req, "PermissionName");
    String PermissionGroup = getQueryParameterString(req, "PermissionGroup");

        response(res, handlecreate(PermissionName, PermissionGroup));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("PermissionName") || !req->getParams()->isQueryParameterSet("PermissionGroup"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String PermissionName = getQueryParameterString(req, "PermissionName");
    String PermissionGroup = getQueryParameterString(req, "PermissionGroup");
        
        response(res, handleupdate(id, PermissionName, PermissionGroup));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PERMISSION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PermissionApis::getClassPath()
{
    return String(class_path.c_str());
}

String PermissionApis::handlecreate(String PermissionName, String PermissionGroup) {
    PermissionEntity* permissionEntity = new PermissionEntity(PermissionName, PermissionGroup);
    int id = permissionController->Add(*permissionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PermissionApis::handleupdate(int id, String PermissionName, String PermissionGroup) {
    PermissionEntity* permissionEntity = new PermissionEntity(id, PermissionName, PermissionGroup);
    
    if (permissionController->Update(*permissionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PermissionApis::handledelete(int id) {
    
    if (permissionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PermissionApis::handlegetAll() {
    return permissionController->GetAllJson();
}
String PermissionApis::handlegetById(int id) {
    return permissionController->GetById(id).toJson();
}
String PermissionApis::handleget(String query) {
    return permissionController->GetJson(query);
}

String PermissionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["PermissionName"], parameters["PermissionGroup"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["PermissionName"], parameters["PermissionGroup"]);
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

#endif //PERMISSIONApis_h

    