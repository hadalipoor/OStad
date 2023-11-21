
    
#ifndef REQUESTLOGAPIS_h
#define REQUESTLOGAPIS_h


#include "../AppContext.h"
#include "../Database/Controllers/RequestLogController.h"
#include "Permissions.h"

class RequestLogApis : public ApiInterface
{
private:
    AppContext* context;
    RequestLogController* requestlogController;
    String class_path = "/requestlog";

public:
    RequestLogApis(AppContext* cntxt);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int RequestFloor, String Direction, String RequestTime);
    String handleupdate(int id, int RequestFloor, String Direction, String RequestTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RequestLogApis::RequestLogApis(AppContext* cntxt): context(cntxt) {
    requestlogController = new RequestLogController(context, storageType);

    context->systemContext->getNetwork()->getServer().on(String(class_path + "/create").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_CREATE)){return;}
        if (!request->hasParam("RequestFloor") || !request->hasParam("Direction") || !request->hasParam("RequestTime"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int RequestFloor = request->getParam("RequestFloor")->value().toInt();
    String Direction = request->getParam("Direction")->value();
    String RequestTime = request->getParam("RequestTime")->value();

        handlecreate(RequestFloor, Direction, RequestTime);
        request->send(200, "text/html", "Successful");
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/update").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_UPDATE)){return;}
        if (!request->hasParam("id") || !request->hasParam("RequestFloor") || !request->hasParam("Direction") || !request->hasParam("RequestTime"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        int RequestFloor = request->getParam("RequestFloor")->value().toInt();
    String Direction = request->getParam("Direction")->value();
    String RequestTime = request->getParam("RequestTime")->value();
        
        request->send(200, "text/html", handleupdate(id, RequestFloor, Direction, RequestTime));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/delete").c_str(), HTTP_DELETE, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_DELETE)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }
        
        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handledelete(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getAll").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_GET)){return;}
        request->send(200, "text/html", handlegetAll());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getById").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_GET)){return;}
        if (!request->hasParam("id"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        int id = request->getParam("id")->value().toInt();
        
        request->send(200, "text/html", handlegetById(id));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/get").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::REQUESTLOG_GET)){return;}
        if (!request->hasParam("query"))
        {
            request->send(400, "text/html", "missing some input params in your request");
        }

        String query = request->getParam("query")->value();
        
        request->send(200, "text/html", handleget(query));
    });
}

void RequestLogApis::initialize(AsyncWebServer &server)
{
    
}

String RequestLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String RequestLogApis::handlecreate(int RequestFloor, String Direction, String RequestTime) {
    RequestLogEntity* requestlogEntity = new RequestLogEntity(RequestFloor, Direction, RequestTime);
    int id = requestlogController->Add(*requestlogEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return "Create Operation Failed!";
}
String RequestLogApis::handleupdate(int id, int RequestFloor, String Direction, String RequestTime) {
    RequestLogEntity* requestlogEntity = new RequestLogEntity(id, RequestFloor, Direction, RequestTime);
    
    if (requestlogController->Update(*requestlogEntity))
    {
        return "Update Succesfull";
    }
    
    return "Update Operation Failed!";
}
String RequestLogApis::handledelete(int id) {
    
    if (requestlogController->Delete(id))
    {
        return "Delete Succesfull";
    }
    
    return "Delete Operation Failed!";
}
String RequestLogApis::handlegetAll() {
    return requestlogController->GetAllJson();
}
String RequestLogApis::handlegetById(int id) {
    return requestlogController->GetById(id).toJson();
}
String RequestLogApis::handleget(String query) {
    return requestlogController->GetJson(query);
}

String RequestLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        handlecreate(parameters["RequestFloor"].toInt(), parameters["Direction"], parameters["RequestTime"]);
        return "OK";
    }
    if (functionName == "handleupdate") {
        handleupdate(parameters["id"].toInt(), parameters["RequestFloor"].toInt(), parameters["Direction"], parameters["RequestTime"]);
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

#endif //REQUESTLOGApis_h

    