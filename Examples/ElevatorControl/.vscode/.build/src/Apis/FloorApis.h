
    
#ifndef FLOORAPIS_h
#define FLOORAPIS_h


#include "../AppContext.h"
#include "../Database/Controllers/FloorController.h"
#include "Permissions.h"

class FloorApis : public ApiInterface
{
private:
    AppContext* context;
    FloorController* floorController;
    String class_path = "/floor";

public:
    FloorApis(AppContext* cntxt);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, String AccessRestrictions);
    String handleupdate(int id, String Name, String AccessRestrictions);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

FloorApis::FloorApis(AppContext* cntxt): context(cntxt) {
    floorController = new FloorController(context, storageType);

    context->systemContext->getNetwork()->getServer().on(String(class_path + "/create").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_CREATE)){return;}
        if (!request->hasParam("Name") || !request->hasParam("AccessRestrictions"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        String Name = request->getParam("Name")->value();
    String AccessRestrictions = request->getParam("AccessRestrictions")->value();

        handlecreate(Name, AccessRestrictions);
        request->send(200, "text/html", "Successful");
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/update").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_UPDATE)){return;}
        if (!request->hasParam("id") || !request->hasParam("Name") || !request->hasParam("AccessRestrictions"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        String Name = request->getParam("Name")->value();
    String AccessRestrictions = request->getParam("AccessRestrictions")->value();
        
        request->send(200, "text/html", handleupdate(id, Name, AccessRestrictions));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/delete").c_str(), HTTP_DELETE, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_DELETE)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handledelete(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getAll").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_GET)){return;}
        request->send(200, "text/html", handlegetAll());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getById").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_GET)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handlegetById(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/get").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::FLOOR_GET)){return;}
        if (!request->hasParam("query"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        String query = request->getParam("query")->value();
        
        request->send(200, "text/html", handleget(query));
    });
}

void FloorApis::initialize(AsyncWebServer &server)
{
    
}

String FloorApis::getClassPath()
{
    return String(class_path.c_str());
}

String FloorApis::handlecreate(String Name, String AccessRestrictions) {
    FloorEntity* floorEntity = new FloorEntity(Name, AccessRestrictions);
    int id = floorController->Add(*floorEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return "Create Operation Failed!";
}
String FloorApis::handleupdate(int id, String Name, String AccessRestrictions) {
    FloorEntity* floorEntity = new FloorEntity(id, Name, AccessRestrictions);
    
    if (floorController->Update(*floorEntity))
    {
        return "Update Succesfull";
    }
    
    return "Update Operation Failed!";
}
String FloorApis::handledelete(int id) {
    
    if (floorController->Delete(id))
    {
        return "Delete Succesfull";
    }
    
    return "Delete Operation Failed!";
}
String FloorApis::handlegetAll() {
    return floorController->GetAllJson();
}
String FloorApis::handlegetById(int id) {
    return floorController->GetById(id).toJson();
}
String FloorApis::handleget(String query) {
    return floorController->GetJson(query);
}

String FloorApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        handlecreate(parameters["Name"], parameters["AccessRestrictions"]);
        return "OK";
    }
    if (functionName == "handleupdate") {
        handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["AccessRestrictions"]);
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

#endif //FLOORApis_h

    