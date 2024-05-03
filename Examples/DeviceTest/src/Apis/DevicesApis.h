#ifndef DEVICESAPIS_h
#define DEVICESAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/DevicesController.h"
#include "Permissions.h"

class DevicesApis : public ApiInterface
{
private:
    AppContext* context;
    DevicesController* devicesController;
    std::string class_path = "/devices";

public:
    DevicesApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword);
    String handleupdate(int id, String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

DevicesApis::DevicesApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    devicesController = new DevicesController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("DeviceType") || !req->getParams()->isQueryParameterSet("ChipId") || !req->getParams()->isQueryParameterSet("IP") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("ParentChipId") || !req->getParams()->isQueryParameterSet("ApSSID") || !req->getParams()->isQueryParameterSet("ApPassword"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String DeviceType = getQueryParameterString(req, "DeviceType");
    String ChipId = getQueryParameterString(req, "ChipId");
    String IP = getQueryParameterString(req, "IP");
    String Name = getQueryParameterString(req, "Name");
    String ParentChipId = getQueryParameterString(req, "ParentChipId");
    String ApSSID = getQueryParameterString(req, "ApSSID");
    String ApPassword = getQueryParameterString(req, "ApPassword");

        response(res, handlecreate(DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("DeviceType") || !req->getParams()->isQueryParameterSet("ChipId") || !req->getParams()->isQueryParameterSet("IP") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("ParentChipId") || !req->getParams()->isQueryParameterSet("ApSSID") || !req->getParams()->isQueryParameterSet("ApPassword"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String DeviceType = getQueryParameterString(req, "DeviceType");
    String ChipId = getQueryParameterString(req, "ChipId");
    String IP = getQueryParameterString(req, "IP");
    String Name = getQueryParameterString(req, "Name");
    String ParentChipId = getQueryParameterString(req, "ParentChipId");
    String ApSSID = getQueryParameterString(req, "ApSSID");
    String ApPassword = getQueryParameterString(req, "ApPassword");
        
        response(res, handleupdate(id, DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICES_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
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
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String DevicesApis::handleupdate(int id, String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword) {
    DevicesEntity* devicesEntity = new DevicesEntity(id, DeviceType, ChipId, IP, Name, ParentChipId, ApSSID, ApPassword);
    
    if (devicesController->Update(*devicesEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String DevicesApis::handledelete(int id) {
    
    if (devicesController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
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

    