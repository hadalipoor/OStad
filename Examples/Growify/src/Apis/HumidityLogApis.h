#ifndef HUMIDITYLOGAPIS_h
#define HUMIDITYLOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/HumidityLogController.h"
#include "Permissions.h"

class HumidityLogApis : public ApiInterface
{
private:
    AppContext* context;
    HumidityLogController* humiditylogController;
    std::string class_path = "/humiditylog";

public:
    HumidityLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int GreenhouseId, int HumidityReading, String DryerState, String HumidifierState);
    String handleupdate(int id, int GreenhouseId, int HumidityReading, String DryerState, String HumidifierState);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

HumidityLogApis::HumidityLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    humiditylogController = new HumidityLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("HumidityReading") || !req->getParams()->isQueryParameterSet("DryerState") || !req->getParams()->isQueryParameterSet("HumidifierState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int HumidityReading = getQueryParameterint(req, "HumidityReading");
    String DryerState = getQueryParameterString(req, "DryerState");
    String HumidifierState = getQueryParameterString(req, "HumidifierState");

        response(res, handlecreate(GreenhouseId, HumidityReading, DryerState, HumidifierState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("GreenhouseId") || !req->getParams()->isQueryParameterSet("HumidityReading") || !req->getParams()->isQueryParameterSet("DryerState") || !req->getParams()->isQueryParameterSet("HumidifierState"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
    int HumidityReading = getQueryParameterint(req, "HumidityReading");
    String DryerState = getQueryParameterString(req, "DryerState");
    String HumidifierState = getQueryParameterString(req, "HumidifierState");
        
        response(res, handleupdate(id, GreenhouseId, HumidityReading, DryerState, HumidifierState));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String HumidityLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String HumidityLogApis::handlecreate(int GreenhouseId, int HumidityReading, String DryerState, String HumidifierState) {
    HumidityLogEntity* humiditylogEntity = new HumidityLogEntity(GreenhouseId, HumidityReading, DryerState, HumidifierState);
    int id = humiditylogController->Add(*humiditylogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String HumidityLogApis::handleupdate(int id, int GreenhouseId, int HumidityReading, String DryerState, String HumidifierState) {
    HumidityLogEntity* humiditylogEntity = new HumidityLogEntity(id, GreenhouseId, HumidityReading, DryerState, HumidifierState);
    
    if (humiditylogController->Update(*humiditylogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String HumidityLogApis::handledelete(int id) {
    
    if (humiditylogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String HumidityLogApis::handlegetAll() {
    return humiditylogController->GetAllJson();
}
String HumidityLogApis::handlegetById(int id) {
    return humiditylogController->GetById(id).toJson();
}
String HumidityLogApis::handleget(String query) {
    return humiditylogController->GetJson(query);
}

String HumidityLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["GreenhouseId"].toInt(), parameters["HumidityReading"].toInt(), parameters["DryerState"], parameters["HumidifierState"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["GreenhouseId"].toInt(), parameters["HumidityReading"].toInt(), parameters["DryerState"], parameters["HumidifierState"]);
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

#endif //HUMIDITYLOGApis_h

    