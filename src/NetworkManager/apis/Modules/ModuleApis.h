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
    
    String handlecreate(String Name, String ModuleType, int DeviceId, int ServerId);
    String handleupdate(int id, String Name, String ModuleType, int DeviceId, int ServerId);
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
        String body = getBodyString(req);
        
        if (!isItemInBody(body,"Name") || !isItemInBody(body,"ModuleType") || !isItemInBody(body,"DeviceId") || !isItemInBody(body,"ServerId"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }
        
        
        
        String Name = getItemInBody(body, "Name");
        
        String ModuleType = getItemInBody(body, "ModuleType");
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "DeviceId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int DeviceId = getItemInBody(body, "DeviceId").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "ServerId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int ServerId = getItemInBody(body, "ServerId").toInt();

        response(res, handlecreate(Name, ModuleType, DeviceId, ServerId));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body, "id") || !isItemInBody(body,"Name") || !isItemInBody(body,"ModuleType") || !isItemInBody(body,"DeviceId") || !isItemInBody(body,"ServerId"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       
        int id = getItemInBody(body, "id").toInt();
        
        
        String Name = getItemInBody(body, "Name");
        
        String ModuleType = getItemInBody(body, "ModuleType");
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "DeviceId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int DeviceId = getItemInBody(body, "DeviceId").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "ServerId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int ServerId = getItemInBody(body, "ServerId").toInt();
        
        response(res, handleupdate(id, Name, ModuleType, DeviceId, ServerId));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body, "id"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       
        int id = getItemInBody(body, "id").toInt();
        
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
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::MODULE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
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

String ModuleApis::handlecreate(String Name, String ModuleType, int DeviceId, int ServerId) {
    ModuleEntity* moduleEntity = new ModuleEntity(Name, ModuleType, DeviceId, ServerId);
    int id = moduleController->Add(*moduleEntity);
    if (id != -1)
    {
        return jsonResponse(true, CREATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, CREATE_FAILED_MESSAGE);
}
String ModuleApis::handleupdate(int id, String Name, String ModuleType, int DeviceId, int ServerId) {
    ModuleEntity* moduleEntity = new ModuleEntity(id, Name, ModuleType, DeviceId, ServerId);
    
    if (moduleController->Update(*moduleEntity))
    {
        return jsonResponse(true, UPDATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, UPDATE_FAILED_MESSAGE);
}
String ModuleApis::handledelete(int id) {
    
    if (moduleController->Delete(id))
    {
        return jsonResponse(true, DELETE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, DELETE_FAILED_MESSAGE);
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
    
    if (functionName == "create") {
        return handlecreate(parameters["Name"], parameters["ModuleType"], parameters["DeviceId"].toInt(), parameters["ServerId"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["ModuleType"], parameters["DeviceId"].toInt(), parameters["ServerId"].toInt());
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

#endif //MODULEApis_h

    