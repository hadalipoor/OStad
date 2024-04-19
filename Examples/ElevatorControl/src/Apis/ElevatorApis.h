#ifndef ELEVATORAPIS_h
#define ELEVATORAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/ElevatorController.h"
#include "Permissions.h"

class ElevatorApis : public ApiInterface
{
private:
    AppContext* context;
    ElevatorController* elevatorController;
    std::string class_path = "/elevator";

public:
    ElevatorApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int CurrentFloor, String Status, String Direction, String LastMaintenanceDate);
    String handleupdate(int id, int CurrentFloor, String Status, String Direction, String LastMaintenanceDate);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ElevatorApis::ElevatorApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    elevatorController = new ElevatorController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("CurrentFloor") || !req->getParams()->isQueryParameterSet("Status") || !req->getParams()->isQueryParameterSet("Direction") || !req->getParams()->isQueryParameterSet("LastMaintenanceDate"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int CurrentFloor = getQueryParameterint(req, "CurrentFloor");
    String Status = getQueryParameterString(req, "Status");
    String Direction = getQueryParameterString(req, "Direction");
    String LastMaintenanceDate = getQueryParameterString(req, "LastMaintenanceDate");

        response(res, handlecreate(CurrentFloor, Status, Direction, LastMaintenanceDate));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("CurrentFloor") || !req->getParams()->isQueryParameterSet("Status") || !req->getParams()->isQueryParameterSet("Direction") || !req->getParams()->isQueryParameterSet("LastMaintenanceDate"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int CurrentFloor = getQueryParameterint(req, "CurrentFloor");
    String Status = getQueryParameterString(req, "Status");
    String Direction = getQueryParameterString(req, "Direction");
    String LastMaintenanceDate = getQueryParameterString(req, "LastMaintenanceDate");
        
        response(res, handleupdate(id, CurrentFloor, Status, Direction, LastMaintenanceDate));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String ElevatorApis::getClassPath()
{
    return String(class_path.c_str());
}

String ElevatorApis::handlecreate(int CurrentFloor, String Status, String Direction, String LastMaintenanceDate) {
    ElevatorEntity* elevatorEntity = new ElevatorEntity(CurrentFloor, Status, Direction, LastMaintenanceDate);
    int id = elevatorController->Add(*elevatorEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String ElevatorApis::handleupdate(int id, int CurrentFloor, String Status, String Direction, String LastMaintenanceDate) {
    ElevatorEntity* elevatorEntity = new ElevatorEntity(id, CurrentFloor, Status, Direction, LastMaintenanceDate);
    
    if (elevatorController->Update(*elevatorEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String ElevatorApis::handledelete(int id) {
    
    if (elevatorController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String ElevatorApis::handlegetAll() {
    return elevatorController->GetAllJson();
}
String ElevatorApis::handlegetById(int id) {
    return elevatorController->GetById(id).toJson();
}
String ElevatorApis::handleget(String query) {
    return elevatorController->GetJson(query);
}

String ElevatorApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["CurrentFloor"].toInt(), parameters["Status"], parameters["Direction"], parameters["LastMaintenanceDate"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["CurrentFloor"].toInt(), parameters["Status"], parameters["Direction"], parameters["LastMaintenanceDate"]);
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

#endif //ELEVATORApis_h

    