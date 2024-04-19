#ifndef DOORLOGAPIS_h
#define DOORLOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/DoorLogController.h"
#include "Permissions.h"

class DoorLogApis : public ApiInterface
{
private:
    AppContext* context;
    DoorLogController* doorlogController;
    std::string class_path = "/doorlog";

public:
    DoorLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UId, int GuestId, int DoorOpened, EBPDateTime TagReadTime);
    String handleupdate(int id, int UId, int GuestId, int DoorOpened, EBPDateTime TagReadTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

DoorLogApis::DoorLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    doorlogController = new DoorLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("UId") || !req->getParams()->isQueryParameterSet("GuestId") || !req->getParams()->isQueryParameterSet("DoorOpened") || !req->getParams()->isQueryParameterSet("TagReadTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int UId = getQueryParameterint(req, "UId");
    int GuestId = getQueryParameterint(req, "GuestId");
    int DoorOpened = getQueryParameterint(req, "DoorOpened");
    EBPDateTime TagReadTime = getQueryParameterEBPDateTime(req, "TagReadTime");

        response(res, handlecreate(UId, GuestId, DoorOpened, TagReadTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UId") || !req->getParams()->isQueryParameterSet("GuestId") || !req->getParams()->isQueryParameterSet("DoorOpened") || !req->getParams()->isQueryParameterSet("TagReadTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int UId = getQueryParameterint(req, "UId");
    int GuestId = getQueryParameterint(req, "GuestId");
    int DoorOpened = getQueryParameterint(req, "DoorOpened");
    EBPDateTime TagReadTime = getQueryParameterEBPDateTime(req, "TagReadTime");
        
        response(res, handleupdate(id, UId, GuestId, DoorOpened, TagReadTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DOORLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String DoorLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String DoorLogApis::handlecreate(int UId, int GuestId, int DoorOpened, EBPDateTime TagReadTime) {
    DoorLogEntity* doorlogEntity = new DoorLogEntity(UId, GuestId, DoorOpened, TagReadTime);
    int id = doorlogController->Add(*doorlogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String DoorLogApis::handleupdate(int id, int UId, int GuestId, int DoorOpened, EBPDateTime TagReadTime) {
    DoorLogEntity* doorlogEntity = new DoorLogEntity(id, UId, GuestId, DoorOpened, TagReadTime);
    
    if (doorlogController->Update(*doorlogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String DoorLogApis::handledelete(int id) {
    
    if (doorlogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String DoorLogApis::handlegetAll() {
    return doorlogController->GetAllJson();
}
String DoorLogApis::handlegetById(int id) {
    return doorlogController->GetById(id).toJson();
}
String DoorLogApis::handleget(String query) {
    return doorlogController->GetJson(query);
}

String DoorLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UId"].toInt(), parameters["GuestId"].toInt(), parameters["DoorOpened"].toInt(), parameters["TagReadTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UId"].toInt(), parameters["GuestId"].toInt(), parameters["DoorOpened"].toInt(), parameters["TagReadTime"]);
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

#endif //DOORLOGApis_h

    