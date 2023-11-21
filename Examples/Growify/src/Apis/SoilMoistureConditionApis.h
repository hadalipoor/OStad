#ifndef SOILMOISTURECONDITIONAPIS_h
#define SOILMOISTURECONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/SoilMoistureConditionController.h"
#include "Permissions.h"

class SoilMoistureConditionApis : public ApiInterface
{
private:
    AppContext* context;
    SoilMoistureConditionController* soilmoistureconditionController;
    std::string class_path = "/soilmoisturecondition";

public:
    SoilMoistureConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, int MinSoilMoisture, int MaxSoilMoisture, int LowSoilMoistureAlertThreshold, int HighSoilMoistureAlertThreshold);
    String handleupdate(int id, String Name, int MinSoilMoisture, int MaxSoilMoisture, int LowSoilMoistureAlertThreshold, int HighSoilMoistureAlertThreshold);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SoilMoistureConditionApis::SoilMoistureConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    soilmoistureconditionController = new SoilMoistureConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinSoilMoisture") || !req->getParams()->isQueryParameterSet("MaxSoilMoisture") || !req->getParams()->isQueryParameterSet("LowSoilMoistureAlertThreshold") || !req->getParams()->isQueryParameterSet("HighSoilMoistureAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    int MinSoilMoisture = getQueryParameterint(req, "MinSoilMoisture");
    int MaxSoilMoisture = getQueryParameterint(req, "MaxSoilMoisture");
    int LowSoilMoistureAlertThreshold = getQueryParameterint(req, "LowSoilMoistureAlertThreshold");
    int HighSoilMoistureAlertThreshold = getQueryParameterint(req, "HighSoilMoistureAlertThreshold");

        response(res, handlecreate(Name, MinSoilMoisture, MaxSoilMoisture, LowSoilMoistureAlertThreshold, HighSoilMoistureAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinSoilMoisture") || !req->getParams()->isQueryParameterSet("MaxSoilMoisture") || !req->getParams()->isQueryParameterSet("LowSoilMoistureAlertThreshold") || !req->getParams()->isQueryParameterSet("HighSoilMoistureAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    int MinSoilMoisture = getQueryParameterint(req, "MinSoilMoisture");
    int MaxSoilMoisture = getQueryParameterint(req, "MaxSoilMoisture");
    int LowSoilMoistureAlertThreshold = getQueryParameterint(req, "LowSoilMoistureAlertThreshold");
    int HighSoilMoistureAlertThreshold = getQueryParameterint(req, "HighSoilMoistureAlertThreshold");
        
        response(res, handleupdate(id, Name, MinSoilMoisture, MaxSoilMoisture, LowSoilMoistureAlertThreshold, HighSoilMoistureAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SoilMoistureConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String SoilMoistureConditionApis::handlecreate(String Name, int MinSoilMoisture, int MaxSoilMoisture, int LowSoilMoistureAlertThreshold, int HighSoilMoistureAlertThreshold) {
    SoilMoistureConditionEntity* soilmoistureconditionEntity = new SoilMoistureConditionEntity(Name, MinSoilMoisture, MaxSoilMoisture, LowSoilMoistureAlertThreshold, HighSoilMoistureAlertThreshold);
    int id = soilmoistureconditionController->Add(*soilmoistureconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handleupdate(int id, String Name, int MinSoilMoisture, int MaxSoilMoisture, int LowSoilMoistureAlertThreshold, int HighSoilMoistureAlertThreshold) {
    SoilMoistureConditionEntity* soilmoistureconditionEntity = new SoilMoistureConditionEntity(id, Name, MinSoilMoisture, MaxSoilMoisture, LowSoilMoistureAlertThreshold, HighSoilMoistureAlertThreshold);
    
    if (soilmoistureconditionController->Update(*soilmoistureconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handledelete(int id) {
    
    if (soilmoistureconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handlegetAll() {
    return soilmoistureconditionController->GetAllJson();
}
String SoilMoistureConditionApis::handlegetById(int id) {
    return soilmoistureconditionController->GetById(id).toJson();
}
String SoilMoistureConditionApis::handleget(String query) {
    return soilmoistureconditionController->GetJson(query);
}

String SoilMoistureConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["Name"], parameters["MinSoilMoisture"].toInt(), parameters["MaxSoilMoisture"].toInt(), parameters["LowSoilMoistureAlertThreshold"].toInt(), parameters["HighSoilMoistureAlertThreshold"].toInt());
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["MinSoilMoisture"].toInt(), parameters["MaxSoilMoisture"].toInt(), parameters["LowSoilMoistureAlertThreshold"].toInt(), parameters["HighSoilMoistureAlertThreshold"].toInt());
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

#endif //SOILMOISTURECONDITIONApis_h

    