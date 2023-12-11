#ifndef LIGHTCONDITIONAPIS_h
#define LIGHTCONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/LightConditionController.h"
#include "Permissions.h"

class LightConditionApis : public ApiInterface
{
private:
    AppContext* context;
    LightConditionController* lightconditionController;
    std::string class_path = "/lightcondition";

public:
    LightConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, int MinLightIntensity, int MaxLightIntensity, int LowLightIntensityAlertThreshold, int HighLightIntensityAlertThreshold);
    String handleupdate(int id, String Name, int MinLightIntensity, int MaxLightIntensity, int LowLightIntensityAlertThreshold, int HighLightIntensityAlertThreshold);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LightConditionApis::LightConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    lightconditionController = new LightConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinLightIntensity") || !req->getParams()->isQueryParameterSet("MaxLightIntensity") || !req->getParams()->isQueryParameterSet("LowLightIntensityAlertThreshold") || !req->getParams()->isQueryParameterSet("HighLightIntensityAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    int MinLightIntensity = getQueryParameterint(req, "MinLightIntensity");
    int MaxLightIntensity = getQueryParameterint(req, "MaxLightIntensity");
    int LowLightIntensityAlertThreshold = getQueryParameterint(req, "LowLightIntensityAlertThreshold");
    int HighLightIntensityAlertThreshold = getQueryParameterint(req, "HighLightIntensityAlertThreshold");

        response(res, handlecreate(Name, MinLightIntensity, MaxLightIntensity, LowLightIntensityAlertThreshold, HighLightIntensityAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("MinLightIntensity") || !req->getParams()->isQueryParameterSet("MaxLightIntensity") || !req->getParams()->isQueryParameterSet("LowLightIntensityAlertThreshold") || !req->getParams()->isQueryParameterSet("HighLightIntensityAlertThreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    int MinLightIntensity = getQueryParameterint(req, "MinLightIntensity");
    int MaxLightIntensity = getQueryParameterint(req, "MaxLightIntensity");
    int LowLightIntensityAlertThreshold = getQueryParameterint(req, "LowLightIntensityAlertThreshold");
    int HighLightIntensityAlertThreshold = getQueryParameterint(req, "HighLightIntensityAlertThreshold");
        
        response(res, handleupdate(id, Name, MinLightIntensity, MaxLightIntensity, LowLightIntensityAlertThreshold, HighLightIntensityAlertThreshold));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LightConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String LightConditionApis::handlecreate(String Name, int MinLightIntensity, int MaxLightIntensity, int LowLightIntensityAlertThreshold, int HighLightIntensityAlertThreshold) {
    LightConditionEntity* lightconditionEntity = new LightConditionEntity(Name, MinLightIntensity, MaxLightIntensity, LowLightIntensityAlertThreshold, HighLightIntensityAlertThreshold);
    int id = lightconditionController->Add(*lightconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LightConditionApis::handleupdate(int id, String Name, int MinLightIntensity, int MaxLightIntensity, int LowLightIntensityAlertThreshold, int HighLightIntensityAlertThreshold) {
    LightConditionEntity* lightconditionEntity = new LightConditionEntity(id, Name, MinLightIntensity, MaxLightIntensity, LowLightIntensityAlertThreshold, HighLightIntensityAlertThreshold);
    
    if (lightconditionController->Update(*lightconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LightConditionApis::handledelete(int id) {
    
    if (lightconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LightConditionApis::handlegetAll() {
    return lightconditionController->GetAllJson();
}
String LightConditionApis::handlegetById(int id) {
    return lightconditionController->GetById(id).toJson();
}
String LightConditionApis::handleget(String query) {
    return lightconditionController->GetJson(query);
}

String LightConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Name"], parameters["MinLightIntensity"].toInt(), parameters["MaxLightIntensity"].toInt(), parameters["LowLightIntensityAlertThreshold"].toInt(), parameters["HighLightIntensityAlertThreshold"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["MinLightIntensity"].toInt(), parameters["MaxLightIntensity"].toInt(), parameters["LowLightIntensityAlertThreshold"].toInt(), parameters["HighLightIntensityAlertThreshold"].toInt());
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

#endif //LIGHTCONDITIONApis_h

    