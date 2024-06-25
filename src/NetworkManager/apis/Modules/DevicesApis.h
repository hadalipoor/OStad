#ifndef DEVICESAPIS_h
#define DEVICESAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/DevicesController.h"
#include "ModulePermissions.h"

class DevicesApis : public ApiInterface
{
private:
    Context* context;
    DevicesController* devicesController;
    std::string class_path = "/devices";

public:
    DevicesApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword);
    String handleupdate(int id, String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

DevicesApis::DevicesApis(Context* cntxt, bool add_apis): context(cntxt) {
    devicesController = new DevicesController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body,"DeviceType") || !isItemInBody(body,"ChipId") || !isItemInBody(body,"IP") || !isItemInBody(body,"Name") || !isItemInBody(body,"ParentChipId") || !isItemInBody(body,"ApSSID") || !isItemInBody(body,"ApPassword"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }
        
        
        
        String DeviceType = getItemInBody(body, "DeviceType");
        
        String ChipId = getItemInBody(body, "ChipId");
        
        String IP = getItemInBody(body, "IP");
        
        String Name = getItemInBody(body, "Name");
        
        String ParentChipId = getItemInBody(body, "ParentChipId");
        
        String ApSSID = getItemInBody(body, "ApSSID");
        
        String ApPassword = getItemInBody(body, "ApPassword");

        response(res, handlecreate(DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body, "id") || !isItemInBody(body,"DeviceType") || !isItemInBody(body,"ChipId") || !isItemInBody(body,"IP") || !isItemInBody(body,"Name") || !isItemInBody(body,"ParentChipId") || !isItemInBody(body,"ApSSID") || !isItemInBody(body,"ApPassword"))
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
        
        
        String DeviceType = getItemInBody(body, "DeviceType");
        
        String ChipId = getItemInBody(body, "ChipId");
        
        String IP = getItemInBody(body, "IP");
        
        String Name = getItemInBody(body, "Name");
        
        String ParentChipId = getItemInBody(body, "ParentChipId");
        
        String ApSSID = getItemInBody(body, "ApSSID");
        
        String ApPassword = getItemInBody(body, "ApPassword");
        
        response(res, handleupdate(id, DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_DELETE) == AuthorizationResults::SUCCESFULL){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
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
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String DevicesApis::getClassPath()
{
    return String(class_path.c_str());
}

String DevicesApis::handlecreate(String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword) {
    DevicesEntity* devicesEntity = new DevicesEntity(DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword);
    int id = devicesController->Add(*devicesEntity);
    if (id != -1)
    {
        return jsonResponse(true, CREATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, CREATE_FAILED_MESSAGE);
}
String DevicesApis::handleupdate(int id, String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword) {
    DevicesEntity* devicesEntity = new DevicesEntity(id, DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword);
    
    if (devicesController->Update(*devicesEntity))
    {
        return jsonResponse(true, UPDATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, UPDATE_FAILED_MESSAGE);
}
String DevicesApis::handledelete(int id) {
    
    if (devicesController->Delete(id))
    {
        return jsonResponse(true, DELETE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, DELETE_FAILED_MESSAGE);
}
String DevicesApis::handlegetAll() {
    return devicesController->GetAllJson();
}
String DevicesApis::handlegetById(int id) {
    return devicesController->GetById(id).toJson();
}
String DevicesApis::handleget(String query) {
    return devicesController->GetJson(query);
}

String DevicesApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["DeviceType"], parameters["ChipId"], parameters["IP"], parameters["Name"], parameters["ParentChipId"], parameters["ApSSID"], parameters["ApPassword"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["DeviceType"], parameters["ChipId"], parameters["IP"], parameters["Name"], parameters["ParentChipId"], parameters["ApSSID"], parameters["ApPassword"]);
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

#endif //DEVICESApis_h

    