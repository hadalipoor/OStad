#ifndef GREENHOUSESENSORAPIS_h
#define GREENHOUSESENSORAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/GreenhouseSensorController.h"
#include "Permissions.h"

class GreenhouseSensorApis : public ApiInterface
{
private:
    AppContext* context;
    GreenhouseSensorController* greenhousesensorController;
    std::string class_path = "/greenhousesensor";

public:
    GreenhouseSensorApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int SensorModuleId, String Role);
    String handleupdate(int id, int GreenhouseId, int SensorModuleId, String Role);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

GreenhouseSensorApis::GreenhouseSensorApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    greenhousesensorController = new GreenhouseSensorController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("SensorModuleId") || !req->getParams()->isQueryParameterSet("Role"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int SensorModuleId = getQueryParameterint(req, "SensorModuleId");
    String Role = getQueryParameterString(req, "Role");

        response(res, handlecreate(GreenhouseId, SensorModuleId, Role));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("SensorModuleId") || !req->getParams()->isQueryParameterSet("Role"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int SensorModuleId = getQueryParameterint(req, "SensorModuleId");
    String Role = getQueryParameterString(req, "Role");
        
        response(res, handleupdate(id, GreenhouseId, SensorModuleId, Role));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSESENSOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String GreenhouseSensorApis::getClassPath()
{
    return String(class_path.c_str());
}

String GreenhouseSensorApis::handlecreate(int GreenhouseId, int SensorModuleId, String Role) {
    GreenhouseSensorEntity* greenhousesensorEntity = new GreenhouseSensorEntity(GreenhouseId, SensorModuleId, Role);
    int id = greenhousesensorController->Add(*greenhousesensorEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String GreenhouseSensorApis::handleupdate(int id, int GreenhouseId, int SensorModuleId, String Role) {
    GreenhouseSensorEntity* greenhousesensorEntity = new GreenhouseSensorEntity(id, GreenhouseId, SensorModuleId, Role);
    
    if (greenhousesensorController->Update(*greenhousesensorEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String GreenhouseSensorApis::handledelete(int id) {
    
    if (greenhousesensorController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String GreenhouseSensorApis::handlegetAll() {
    return greenhousesensorController->GetAllJson();
}
String GreenhouseSensorApis::handlegetById(int id) {
    return greenhousesensorController->GetById(id).toJson();
}
String GreenhouseSensorApis::handleget(String query) {
    return greenhousesensorController->GetJson(query);
}

String GreenhouseSensorApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["SensorModuleId"].toInt(), parameters["Role"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["SensorModuleId"].toInt(), parameters["Role"]);
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

#endif //GREENHOUSESENSORApis_h

    