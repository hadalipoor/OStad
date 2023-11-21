
    
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
    String class_path = "/elevator";

public:
    ElevatorApis(AppContext* cntxt);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int CurrentFloor, String Status, String Direction, String LastMaintenanceDate);
    String handleupdate(int id, int CurrentFloor, String Status, String Direction, String LastMaintenanceDate);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ElevatorApis::ElevatorApis(AppContext* cntxt): context(cntxt) {
    elevatorController = new ElevatorController(context, storageType);

    context->systemContext->getNetwork()->getServer().on(String(class_path + "/create").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_CREATE)){return;}
        if (!request->hasParam("CurrentFloor") || !request->hasParam("Status") || !request->hasParam("Direction") || !request->hasParam("LastMaintenanceDate"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int CurrentFloor = request->getParam("CurrentFloor")->value().toInt();
    String Status = request->getParam("Status")->value();
    String Direction = request->getParam("Direction")->value();
    String LastMaintenanceDate = request->getParam("LastMaintenanceDate")->value();

        handlecreate(CurrentFloor, Status, Direction, LastMaintenanceDate);
        request->send(200, "text/html", "Successful");
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/update").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_UPDATE)){return;}
        if (!request->hasParam("id") || !request->hasParam("CurrentFloor") || !request->hasParam("Status") || !request->hasParam("Direction") || !request->hasParam("LastMaintenanceDate"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        int CurrentFloor = request->getParam("CurrentFloor")->value().toInt();
    String Status = request->getParam("Status")->value();
    String Direction = request->getParam("Direction")->value();
    String LastMaintenanceDate = request->getParam("LastMaintenanceDate")->value();
        
        request->send(200, "text/html", handleupdate(id, CurrentFloor, Status, Direction, LastMaintenanceDate));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/delete").c_str(), HTTP_DELETE, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_DELETE)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handledelete(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getAll").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_GET)){return;}
        request->send(200, "text/html", handlegetAll());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getById").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_GET)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handlegetById(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/get").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATOR_GET)){return;}
        if (!request->hasParam("query"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        String query = request->getParam("query")->value();
        
        request->send(200, "text/html", handleget(query));
    });
}

void ElevatorApis::initialize(AsyncWebServer &server)
{
    
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
        return String(id);
    }
    
    return "Create Operation Failed!";
}
String ElevatorApis::handleupdate(int id, int CurrentFloor, String Status, String Direction, String LastMaintenanceDate) {
    ElevatorEntity* elevatorEntity = new ElevatorEntity(id, CurrentFloor, Status, Direction, LastMaintenanceDate);
    
    if (elevatorController->Update(*elevatorEntity))
    {
        return "Update Succesfull";
    }
    
    return "Update Operation Failed!";
}
String ElevatorApis::handledelete(int id) {
    
    if (elevatorController->Delete(id))
    {
        return "Delete Succesfull";
    }
    
    return "Delete Operation Failed!";
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
    
    if (functionName == "handlecreate") {
        handlecreate(parameters["CurrentFloor"].toInt(), parameters["Status"], parameters["Direction"], parameters["LastMaintenanceDate"]);
        return "OK";
    }
    if (functionName == "handleupdate") {
        handleupdate(parameters["id"].toInt(), parameters["CurrentFloor"].toInt(), parameters["Status"], parameters["Direction"], parameters["LastMaintenanceDate"]);
        return "OK";
    }
    if (functionName == "handledelete") {
        handledelete(parameters["id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetAll") {
        handlegetAll();
        return "OK";
    }
    if (functionName == "handlegetById") {
        handlegetById(parameters["id"].toInt());
        return "OK";
    }
    if (functionName == "handleget") {
        handleget(parameters["query"]);
        return "OK";
    }
    return "";
}

#endif //ELEVATORApis_h

    