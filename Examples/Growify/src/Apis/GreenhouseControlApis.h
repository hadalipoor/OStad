#ifndef GREENHOUSECONTROLAPIS_h
#define GREENHOUSECONTROLAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/GreenhouseControlController.h"
#include "Permissions.h"

class GreenhouseControlApis : public ApiInterface
{
private:
    AppContext* context;
    GreenhouseControlController* greenhousecontrolController;
    std::string class_path = "/greenhousecontrol";

public:
    GreenhouseControlApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int ControlModuleId, String Role);
    String handleupdate(int id, int GreenhouseId, int ControlModuleId, String Role);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

GreenhouseControlApis::GreenhouseControlApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    greenhousecontrolController = new GreenhouseControlController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("ControlModuleId") || !req->getParams()->isQueryParameterSet("Role"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int ControlModuleId = getQueryParameterint(req, "ControlModuleId");
    String Role = getQueryParameterString(req, "Role");

        response(res, handlecreate(GreenhouseId, ControlModuleId, Role));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("ControlModuleId") || !req->getParams()->isQueryParameterSet("Role"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int ControlModuleId = getQueryParameterint(req, "ControlModuleId");
    String Role = getQueryParameterString(req, "Role");
        
        response(res, handleupdate(id, GreenhouseId, ControlModuleId, Role));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSECONTROL_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String GreenhouseControlApis::getClassPath()
{
    return String(class_path.c_str());
}

String GreenhouseControlApis::handlecreate(int GreenhouseId, int ControlModuleId, String Role) {
    GreenhouseControlEntity* greenhousecontrolEntity = new GreenhouseControlEntity(GreenhouseId, ControlModuleId, Role);
    int id = greenhousecontrolController->Add(*greenhousecontrolEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String GreenhouseControlApis::handleupdate(int id, int GreenhouseId, int ControlModuleId, String Role) {
    GreenhouseControlEntity* greenhousecontrolEntity = new GreenhouseControlEntity(id, GreenhouseId, ControlModuleId, Role);
    
    if (greenhousecontrolController->Update(*greenhousecontrolEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String GreenhouseControlApis::handledelete(int id) {
    
    if (greenhousecontrolController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String GreenhouseControlApis::handlegetAll() {
    return greenhousecontrolController->GetAllJson();
}
String GreenhouseControlApis::handlegetById(int id) {
    return greenhousecontrolController->GetById(id).toJson();
}
String GreenhouseControlApis::handleget(String query) {
    return greenhousecontrolController->GetJson(query);
}

String GreenhouseControlApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["ControlModuleId"].toInt(), parameters["Role"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["ControlModuleId"].toInt(), parameters["Role"]);
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

#endif //GREENHOUSECONTROLApis_h

    