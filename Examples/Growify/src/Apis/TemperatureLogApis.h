#ifndef TEMPERATURELOGAPIS_h
#define TEMPERATURELOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/TemperatureLogController.h"
#include "Permissions.h"

class TemperatureLogApis : public ApiInterface
{
private:
    AppContext* context;
    TemperatureLogController* temperaturelogController;
    std::string class_path = "/temperaturelog";

public:
    TemperatureLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int TemperatureReading, String CoolerState, String HeaterState);
    String handleupdate(int id, int GreenhouseId, int TemperatureReading, String CoolerState, String HeaterState);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

TemperatureLogApis::TemperatureLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    temperaturelogController = new TemperatureLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("TemperatureReading") || !req->getParams()->isQueryParameterSet("CoolerState") || !req->getParams()->isQueryParameterSet("HeaterState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int TemperatureReading = getQueryParameterint(req, "TemperatureReading");
    String CoolerState = getQueryParameterString(req, "CoolerState");
    String HeaterState = getQueryParameterString(req, "HeaterState");

        response(res, handlecreate(GreenhouseId, TemperatureReading, CoolerState, HeaterState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("TemperatureReading") || !req->getParams()->isQueryParameterSet("CoolerState") || !req->getParams()->isQueryParameterSet("HeaterState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int TemperatureReading = getQueryParameterint(req, "TemperatureReading");
    String CoolerState = getQueryParameterString(req, "CoolerState");
    String HeaterState = getQueryParameterString(req, "HeaterState");
        
        response(res, handleupdate(id, GreenhouseId, TemperatureReading, CoolerState, HeaterState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String TemperatureLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String TemperatureLogApis::handlecreate(int GreenhouseId, int TemperatureReading, String CoolerState, String HeaterState) {
    TemperatureLogEntity* temperaturelogEntity = new TemperatureLogEntity(GreenhouseId, TemperatureReading, CoolerState, HeaterState);
    int id = temperaturelogController->Add(*temperaturelogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String TemperatureLogApis::handleupdate(int id, int GreenhouseId, int TemperatureReading, String CoolerState, String HeaterState) {
    TemperatureLogEntity* temperaturelogEntity = new TemperatureLogEntity(id, GreenhouseId, TemperatureReading, CoolerState, HeaterState);
    
    if (temperaturelogController->Update(*temperaturelogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String TemperatureLogApis::handledelete(int id) {
    
    if (temperaturelogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String TemperatureLogApis::handlegetAll() {
    return temperaturelogController->GetAllJson();
}
String TemperatureLogApis::handlegetById(int id) {
    return temperaturelogController->GetById(id).toJson();
}
String TemperatureLogApis::handleget(String query) {
    return temperaturelogController->GetJson(query);
}

String TemperatureLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["TemperatureReading"].toInt(), parameters["CoolerState"], parameters["HeaterState"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["TemperatureReading"].toInt(), parameters["CoolerState"], parameters["HeaterState"]);
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

#endif //TEMPERATURELOGApis_h

    