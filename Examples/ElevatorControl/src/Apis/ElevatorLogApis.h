#ifndef ELEVATORLOGAPIS_h
#define ELEVATORLOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/ElevatorLogController.h"
#include "Permissions.h"

class ElevatorLogApis : public ApiInterface
{
private:
    AppContext* context;
    ElevatorLogController* elevatorlogController;
    std::string class_path = "/elevatorlog";

public:
    ElevatorLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Action, String ActionTime);
    String handleupdate(int id, String Action, String ActionTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ElevatorLogApis::ElevatorLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    elevatorlogController = new ElevatorLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Action") || !req->getParams()->isQueryParameterSet("ActionTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Action = getQueryParameterString(req, "Action");
    String ActionTime = getQueryParameterString(req, "ActionTime");

        response(res, handlecreate(Action, ActionTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Action") || !req->getParams()->isQueryParameterSet("ActionTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Action = getQueryParameterString(req, "Action");
    String ActionTime = getQueryParameterString(req, "ActionTime");
        
        response(res, handleupdate(id, Action, ActionTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String ElevatorLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String ElevatorLogApis::handlecreate(String Action, String ActionTime) {
    ElevatorLogEntity* elevatorlogEntity = new ElevatorLogEntity(Action, ActionTime);
    int id = elevatorlogController->Add(*elevatorlogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String ElevatorLogApis::handleupdate(int id, String Action, String ActionTime) {
    ElevatorLogEntity* elevatorlogEntity = new ElevatorLogEntity(id, Action, ActionTime);
    
    if (elevatorlogController->Update(*elevatorlogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String ElevatorLogApis::handledelete(int id) {
    
    if (elevatorlogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String ElevatorLogApis::handlegetAll() {
    return elevatorlogController->GetAllJson();
}
String ElevatorLogApis::handlegetById(int id) {
    return elevatorlogController->GetById(id).toJson();
}
String ElevatorLogApis::handleget(String query) {
    return elevatorlogController->GetJson(query);
}

String ElevatorLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Action"], parameters["ActionTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Action"], parameters["ActionTime"]);
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

#endif //ELEVATORLOGApis_h

    