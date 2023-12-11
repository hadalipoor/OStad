#ifndef SOILMOISTURELOGAPIS_h
#define SOILMOISTURELOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/SoilMoistureLogController.h"
#include "Permissions.h"

class SoilMoistureLogApis : public ApiInterface
{
private:
    AppContext* context;
    SoilMoistureLogController* soilmoisturelogController;
    std::string class_path = "/soilmoisturelog";

public:
    SoilMoistureLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int SoilMoistureReading, String WaterPumpState);
    String handleupdate(int id, int GreenhouseId, int SoilMoistureReading, String WaterPumpState);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SoilMoistureLogApis::SoilMoistureLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    soilmoisturelogController = new SoilMoistureLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("SoilMoistureReading") || !req->getParams()->isQueryParameterSet("WaterPumpState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int SoilMoistureReading = getQueryParameterint(req, "SoilMoistureReading");
    String WaterPumpState = getQueryParameterString(req, "WaterPumpState");

        response(res, handlecreate(GreenhouseId, SoilMoistureReading, WaterPumpState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("SoilMoistureReading") || !req->getParams()->isQueryParameterSet("WaterPumpState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int SoilMoistureReading = getQueryParameterint(req, "SoilMoistureReading");
    String WaterPumpState = getQueryParameterString(req, "WaterPumpState");
        
        response(res, handleupdate(id, GreenhouseId, SoilMoistureReading, WaterPumpState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURELOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SoilMoistureLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String SoilMoistureLogApis::handlecreate(int GreenhouseId, int SoilMoistureReading, String WaterPumpState) {
    SoilMoistureLogEntity* soilmoisturelogEntity = new SoilMoistureLogEntity(GreenhouseId, SoilMoistureReading, WaterPumpState);
    int id = soilmoisturelogController->Add(*soilmoisturelogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SoilMoistureLogApis::handleupdate(int id, int GreenhouseId, int SoilMoistureReading, String WaterPumpState) {
    SoilMoistureLogEntity* soilmoisturelogEntity = new SoilMoistureLogEntity(id, GreenhouseId, SoilMoistureReading, WaterPumpState);
    
    if (soilmoisturelogController->Update(*soilmoisturelogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SoilMoistureLogApis::handledelete(int id) {
    
    if (soilmoisturelogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SoilMoistureLogApis::handlegetAll() {
    return soilmoisturelogController->GetAllJson();
}
String SoilMoistureLogApis::handlegetById(int id) {
    return soilmoisturelogController->GetById(id).toJson();
}
String SoilMoistureLogApis::handleget(String query) {
    return soilmoisturelogController->GetJson(query);
}

String SoilMoistureLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["SoilMoistureReading"].toInt(), parameters["WaterPumpState"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["SoilMoistureReading"].toInt(), parameters["WaterPumpState"]);
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

#endif //SOILMOISTURELOGApis_h

    