#ifndef HUMIDITYCONDITIONAPIS_h
#define HUMIDITYCONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/HumidityConditionController.h"
#include "Permissions.h"

class HumidityConditionApis : public ApiInterface
{
private:
    AppContext* context;
    HumidityConditionController* humidityconditionController;
    std::string class_path = "/humiditycondition";

public:
    HumidityConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, int MinHumidity, int MaxHumidity, int LowHumidityAlertThreshold, int HighHumidityAlertThreshold);
    String handleupdate(int id, String Name, int MinHumidity, int MaxHumidity, int LowHumidityAlertThreshold, int HighHumidityAlertThreshold);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

HumidityConditionApis::HumidityConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    humidityconditionController = new HumidityConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinHumidity") || !req->getParams()->isQueryParameterSet("MaxHumidity") || !req->getParams()->isQueryParameterSet("LowHumidityAlertThreshold") || !req->getParams()->isQueryParameterSet("HighHumidityAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    int MinHumidity = getQueryParameterint(req, "MinHumidity");
    int MaxHumidity = getQueryParameterint(req, "MaxHumidity");
    int LowHumidityAlertThreshold = getQueryParameterint(req, "LowHumidityAlertThreshold");
    int HighHumidityAlertThreshold = getQueryParameterint(req, "HighHumidityAlertThreshold");

        response(res, handlecreate(Name, MinHumidity, MaxHumidity, LowHumidityAlertThreshold, HighHumidityAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinHumidity") || !req->getParams()->isQueryParameterSet("MaxHumidity") || !req->getParams()->isQueryParameterSet("LowHumidityAlertThreshold") || !req->getParams()->isQueryParameterSet("HighHumidityAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    int MinHumidity = getQueryParameterint(req, "MinHumidity");
    int MaxHumidity = getQueryParameterint(req, "MaxHumidity");
    int LowHumidityAlertThreshold = getQueryParameterint(req, "LowHumidityAlertThreshold");
    int HighHumidityAlertThreshold = getQueryParameterint(req, "HighHumidityAlertThreshold");
        
        response(res, handleupdate(id, Name, MinHumidity, MaxHumidity, LowHumidityAlertThreshold, HighHumidityAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::HUMIDITYCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String HumidityConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String HumidityConditionApis::handlecreate(String Name, int MinHumidity, int MaxHumidity, int LowHumidityAlertThreshold, int HighHumidityAlertThreshold) {
    HumidityConditionEntity* humidityconditionEntity = new HumidityConditionEntity(Name, MinHumidity, MaxHumidity, LowHumidityAlertThreshold, HighHumidityAlertThreshold);
    int id = humidityconditionController->Add(*humidityconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String HumidityConditionApis::handleupdate(int id, String Name, int MinHumidity, int MaxHumidity, int LowHumidityAlertThreshold, int HighHumidityAlertThreshold) {
    HumidityConditionEntity* humidityconditionEntity = new HumidityConditionEntity(id, Name, MinHumidity, MaxHumidity, LowHumidityAlertThreshold, HighHumidityAlertThreshold);
    
    if (humidityconditionController->Update(*humidityconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String HumidityConditionApis::handledelete(int id) {
    
    if (humidityconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String HumidityConditionApis::handlegetAll() {
    return humidityconditionController->GetAllJson();
}
String HumidityConditionApis::handlegetById(int id) {
    return humidityconditionController->GetById(id).toJson();
}
String HumidityConditionApis::handleget(String query) {
    return humidityconditionController->GetJson(query);
}

String HumidityConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Name"], parameters["MinHumidity"].toInt(), parameters["MaxHumidity"].toInt(), parameters["LowHumidityAlertThreshold"].toInt(), parameters["HighHumidityAlertThreshold"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["MinHumidity"].toInt(), parameters["MaxHumidity"].toInt(), parameters["LowHumidityAlertThreshold"].toInt(), parameters["HighHumidityAlertThreshold"].toInt());
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

#endif //HUMIDITYCONDITIONApis_h

    