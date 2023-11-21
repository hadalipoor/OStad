#ifndef SOILMOISTUREAPIS_h
#define SOILMOISTUREAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/SoilMoistureController.h"
#include "ModulePermissions.h"

class SoilMoistureApis : public ApiInterface
{
private:
    Context* context;
    SoilMoistureController* soilmoistureController;
    std::string class_path = "/soilmoisture";

public:
    SoilMoistureApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int DryTreshold, int WetTreshold, String Type);
    String handleupdate(int id, int DryTreshold, int WetTreshold, String Type);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SoilMoistureApis::SoilMoistureApis(Context* cntxt, bool add_apis): context(cntxt) {
    soilmoistureController = new SoilMoistureController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("DryTreshold") || !req->getParams()->isQueryParameterSet("WetTreshold") || !req->getParams()->isQueryParameterSet("Type"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int DryTreshold = getQueryParameterint(req, "DryTreshold");
    int WetTreshold = getQueryParameterint(req, "WetTreshold");
    String Type = getQueryParameterString(req, "Type");

        response(res, handlecreate(DryTreshold, WetTreshold, Type));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("DryTreshold") || !req->getParams()->isQueryParameterSet("WetTreshold") || !req->getParams()->isQueryParameterSet("Type"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int DryTreshold = getQueryParameterint(req, "DryTreshold");
    int WetTreshold = getQueryParameterint(req, "WetTreshold");
    String Type = getQueryParameterString(req, "Type");
        
        response(res, handleupdate(id, DryTreshold, WetTreshold, Type));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SoilMoistureApis::getClassPath()
{
    return String(class_path.c_str());
}

String SoilMoistureApis::handlecreate(int DryTreshold, int WetTreshold, String Type) {
    SoilMoistureEntity* soilmoistureEntity = new SoilMoistureEntity(DryTreshold, WetTreshold, Type);
    int id = soilmoistureController->Add(*soilmoistureEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SoilMoistureApis::handleupdate(int id, int DryTreshold, int WetTreshold, String Type) {
    SoilMoistureEntity* soilmoistureEntity = new SoilMoistureEntity(id, DryTreshold, WetTreshold, Type);
    
    if (soilmoistureController->Update(*soilmoistureEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SoilMoistureApis::handledelete(int id) {
    
    if (soilmoistureController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SoilMoistureApis::handlegetAll() {
    return soilmoistureController->GetAllJson();
}
String SoilMoistureApis::handlegetById(int id) {
    return soilmoistureController->GetById(id).toJson();
}
String SoilMoistureApis::handleget(String query) {
    return soilmoistureController->GetJson(query);
}

String SoilMoistureApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["DryTreshold"].toInt(), parameters["WetTreshold"].toInt(), parameters["Type"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["DryTreshold"].toInt(), parameters["WetTreshold"].toInt(), parameters["Type"]);
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

#endif //SOILMOISTUREApis_h

    