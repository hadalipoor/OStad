
    
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
    String class_path = "/elevatorlog";

public:
    ElevatorLogApis(AppContext* cntxt);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Action, String ActionTime);
    String handleupdate(int id, String Action, String ActionTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ElevatorLogApis::ElevatorLogApis(AppContext* cntxt): context(cntxt) {
    elevatorlogController = new ElevatorLogController(context, storageType);

    context->systemContext->getNetwork()->getServer().on(String(class_path + "/create").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_CREATE)){return;}
        if (!request->hasParam("Action") || !request->hasParam("ActionTime"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        String Action = request->getParam("Action")->value();
    String ActionTime = request->getParam("ActionTime")->value();

        handlecreate(Action, ActionTime);
        request->send(200, "text/html", "Successful");
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/update").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_UPDATE)){return;}
        if (!request->hasParam("id") || !request->hasParam("Action") || !request->hasParam("ActionTime"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        String Action = request->getParam("Action")->value();
    String ActionTime = request->getParam("ActionTime")->value();
        
        request->send(200, "text/html", handleupdate(id, Action, ActionTime));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/delete").c_str(), HTTP_DELETE, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_DELETE)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handledelete(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getAll").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_GET)){return;}
        request->send(200, "text/html", handlegetAll());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getById").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_GET)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handlegetById(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/get").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORLOG_GET)){return;}
        if (!request->hasParam("query"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        String query = request->getParam("query")->value();
        
        request->send(200, "text/html", handleget(query));
    });
}

void ElevatorLogApis::initialize(AsyncWebServer &server)
{
    
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
        return String(id);
    }
    
    return "Create Operation Failed!";
}
String ElevatorLogApis::handleupdate(int id, String Action, String ActionTime) {
    ElevatorLogEntity* elevatorlogEntity = new ElevatorLogEntity(id, Action, ActionTime);
    
    if (elevatorlogController->Update(*elevatorlogEntity))
    {
        return "Update Succesfull";
    }
    
    return "Update Operation Failed!";
}
String ElevatorLogApis::handledelete(int id) {
    
    if (elevatorlogController->Delete(id))
    {
        return "Delete Succesfull";
    }
    
    return "Delete Operation Failed!";
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
    
    if (functionName == "handlecreate") {
        handlecreate(parameters["Action"], parameters["ActionTime"]);
        return "OK";
    }
    if (functionName == "handleupdate") {
        handleupdate(parameters["id"].toInt(), parameters["Action"], parameters["ActionTime"]);
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

#endif //ELEVATORLOGApis_h

    