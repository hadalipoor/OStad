#ifndef LIGHTLOGAPIS_h
#define LIGHTLOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/LightLogController.h"
#include "Permissions.h"

class LightLogApis : public ApiInterface
{
private:
    AppContext* context;
    LightLogController* lightlogController;
    std::string class_path = "/lightlog";

public:
    LightLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int LightIntensityReading, String LightState);
    String handleupdate(int id, int GreenhouseId, int LightIntensityReading, String LightState);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LightLogApis::LightLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    lightlogController = new LightLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("LightIntensityReading") || !req->getParams()->isQueryParameterSet("LightState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int LightIntensityReading = getQueryParameterint(req, "LightIntensityReading");
    String LightState = getQueryParameterString(req, "LightState");

        response(res, handlecreate(GreenhouseId, LightIntensityReading, LightState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("LightIntensityReading") || !req->getParams()->isQueryParameterSet("LightState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int LightIntensityReading = getQueryParameterint(req, "LightIntensityReading");
    String LightState = getQueryParameterString(req, "LightState");
        
        response(res, handleupdate(id, GreenhouseId, LightIntensityReading, LightState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LightLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String LightLogApis::handlecreate(int GreenhouseId, int LightIntensityReading, String LightState) {
    LightLogEntity* lightlogEntity = new LightLogEntity(GreenhouseId, LightIntensityReading, LightState);
    int id = lightlogController->Add(*lightlogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LightLogApis::handleupdate(int id, int GreenhouseId, int LightIntensityReading, String LightState) {
    LightLogEntity* lightlogEntity = new LightLogEntity(id, GreenhouseId, LightIntensityReading, LightState);
    
    if (lightlogController->Update(*lightlogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LightLogApis::handledelete(int id) {
    
    if (lightlogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LightLogApis::handlegetAll() {
    return lightlogController->GetAllJson();
}
String LightLogApis::handlegetById(int id) {
    return lightlogController->GetById(id).toJson();
}
String LightLogApis::handleget(String query) {
    return lightlogController->GetJson(query);
}

String LightLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["LightIntensityReading"].toInt(), parameters["LightState"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["LightIntensityReading"].toInt(), parameters["LightState"]);
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

#endif //LIGHTLOGApis_h

    