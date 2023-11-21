#ifndef MODULEAPIS_h
#define MODULEAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/ModulesController.h"
#include "ModulePermissions.h"

class ModuleApis : public ApiInterface
{
private:
    Context* context;
    ModulesController* moduleController;
    std::string class_path = "/module";

public:
    ModuleApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, String ModuleType, String ConnectionType, int NodeId, int PinNumber);
    String handleupdate(int id, String Name, String ModuleType, String ConnectionType, int NodeId, int PinNumber);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ModuleApis::ModuleApis(Context* cntxt, bool add_apis): context(cntxt) {
    moduleController = new ModulesController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("ModuleType") || !req->getParams()->isQueryParameterSet("ConnectionType") || !req->getParams()->isQueryParameterSet("NodeId") || !req->getParams()->isQueryParameterSet("PinNumber"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    String ModuleType = getQueryParameterString(req, "ModuleType");
    String ConnectionType = getQueryParameterString(req, "ConnectionType");
    int NodeId = getQueryParameterint(req, "NodeId");
    int PinNumber = getQueryParameterint(req, "PinNumber");

        response(res, handlecreate(Name, ModuleType, ConnectionType, NodeId, PinNumber));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("ModuleType") || !req->getParams()->isQueryParameterSet("ConnectionType") || !req->getParams()->isQueryParameterSet("NodeId") || !req->getParams()->isQueryParameterSet("PinNumber"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    String ModuleType = getQueryParameterString(req, "ModuleType");
    String ConnectionType = getQueryParameterString(req, "ConnectionType");
    int NodeId = getQueryParameterint(req, "NodeId");
    int PinNumber = getQueryParameterint(req, "PinNumber");
        
        response(res, handleupdate(id, Name, ModuleType, ConnectionType, NodeId, PinNumber));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String ModuleApis::getClassPath()
{
    return String(class_path.c_str());
}

String ModuleApis::handlecreate(String Name, String ModuleType, String ConnectionType, int NodeId, int PinNumber) {
    ModuleEntity* moduleEntity = new ModuleEntity(Name, ModuleType, ConnectionType, NodeId, PinNumber);
    int id = moduleController->Add(*moduleEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String ModuleApis::handleupdate(int id, String Name, String ModuleType, String ConnectionType, int NodeId, int PinNumber) {
    ModuleEntity* moduleEntity = new ModuleEntity(id, Name, ModuleType, ConnectionType, NodeId, PinNumber);
    
    if (moduleController->Update(*moduleEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String ModuleApis::handledelete(int id) {
    
    if (moduleController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String ModuleApis::handlegetAll() {
    return moduleController->GetAllJson();
}
String ModuleApis::handlegetById(int id) {
    return moduleController->GetById(id).toJson();
}
String ModuleApis::handleget(String query) {
    return moduleController->GetJson(query);
}

String ModuleApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["Name"], parameters["ModuleType"], parameters["ConnectionType"], parameters["NodeId"].toInt(), parameters["PinNumber"].toInt());
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["ModuleType"], parameters["ConnectionType"], parameters["NodeId"].toInt(), parameters["PinNumber"].toInt());
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

#endif //MODULEApis_h

    