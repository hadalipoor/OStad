#ifndef PLANTAPIS_h
#define PLANTAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/PlantController.h"
#include "Permissions.h"

class PlantApis : public ApiInterface
{
private:
    AppContext* context;
    PlantController* plantController;
    std::string class_path = "/plant";

public:
    PlantApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, int PlantTypeId, int GreenhouseId);
    String handleupdate(int id, String Name, int PlantTypeId, int GreenhouseId);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PlantApis::PlantApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    plantController = new PlantController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("PlantTypeId") || !req->getParams()->isQueryParameterSet("GreenhouseId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    int PlantTypeId = getQueryParameterint(req, "PlantTypeId");
    int GreenhouseId = getQueryParameterint(req, "GreenhouseId");

        response(res, handlecreate(Name, PlantTypeId, GreenhouseId));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("PlantTypeId") || !req->getParams()->isQueryParameterSet("GreenhouseId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    int PlantTypeId = getQueryParameterint(req, "PlantTypeId");
    int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
        
        response(res, handleupdate(id, Name, PlantTypeId, GreenhouseId));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PlantApis::getClassPath()
{
    return String(class_path.c_str());
}

String PlantApis::handlecreate(String Name, int PlantTypeId, int GreenhouseId) {
    PlantEntity* plantEntity = new PlantEntity(Name, PlantTypeId, GreenhouseId);
    int id = plantController->Add(*plantEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PlantApis::handleupdate(int id, String Name, int PlantTypeId, int GreenhouseId) {
    PlantEntity* plantEntity = new PlantEntity(id, Name, PlantTypeId, GreenhouseId);
    
    if (plantController->Update(*plantEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PlantApis::handledelete(int id) {
    
    if (plantController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PlantApis::handlegetAll() {
    return plantController->GetAllJson();
}
String PlantApis::handlegetById(int id) {
    return plantController->GetById(id).toJson();
}
String PlantApis::handleget(String query) {
    return plantController->GetJson(query);
}

String PlantApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["Name"], parameters["PlantTypeId"].toInt(), parameters["GreenhouseId"].toInt());
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["PlantTypeId"].toInt(), parameters["GreenhouseId"].toInt());
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

#endif //PLANTApis_h

    