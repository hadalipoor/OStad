#ifndef PLANTTYPEAPIS_h
#define PLANTTYPEAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/PlantTypeController.h"
#include "Permissions.h"

class PlantTypeApis : public ApiInterface
{
private:
    AppContext* context;
    PlantTypeController* planttypeController;
    std::string class_path = "/planttype";

public:
    PlantTypeApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, int GreenhouseId);
    String handleupdate(int id, String Name, int GreenhouseId);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PlantTypeApis::PlantTypeApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    planttypeController = new PlantTypeController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("GreenhouseId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    int GreenhouseId = getQueryParameterint(req, "GreenhouseId");

        response(res, handlecreate(Name, GreenhouseId));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("GreenhouseId"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    int GreenhouseId = getQueryParameterint(req, "GreenhouseId");
        
        response(res, handleupdate(id, Name, GreenhouseId));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PlantTypeApis::getClassPath()
{
    return String(class_path.c_str());
}

String PlantTypeApis::handlecreate(String Name, int GreenhouseId) {
    PlantTypeEntity* planttypeEntity = new PlantTypeEntity(Name, GreenhouseId);
    int id = planttypeController->Add(*planttypeEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PlantTypeApis::handleupdate(int id, String Name, int GreenhouseId) {
    PlantTypeEntity* planttypeEntity = new PlantTypeEntity(id, Name, GreenhouseId);
    
    if (planttypeController->Update(*planttypeEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PlantTypeApis::handledelete(int id) {
    
    if (planttypeController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PlantTypeApis::handlegetAll() {
    return planttypeController->GetAllJson();
}
String PlantTypeApis::handlegetById(int id) {
    return planttypeController->GetById(id).toJson();
}
String PlantTypeApis::handleget(String query) {
    return planttypeController->GetJson(query);
}

String PlantTypeApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Name"], parameters["GreenhouseId"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["GreenhouseId"].toInt());
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

#endif //PLANTTYPEApis_h

    