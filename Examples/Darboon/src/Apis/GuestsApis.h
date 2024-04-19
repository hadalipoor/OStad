#ifndef GUESTSAPIS_h
#define GUESTSAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/GuestsController.h"
#include "Permissions.h"

class GuestsApis : public ApiInterface
{
private:
    AppContext* context;
    GuestsController* guestsController;
    std::string class_path = "/guests";

public:
    GuestsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Name, String Description, String UId, int Active, EBPDateTime StartActiveTime, EBPDateTime EndActiveTime);
    String handleupdate(int id, String Name, String Description, String UId, int Active, EBPDateTime StartActiveTime, EBPDateTime EndActiveTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

GuestsApis::GuestsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    guestsController = new GuestsController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("Description") || !req->getParams()->isQueryParameterSet("UId") || !req->getParams()->isQueryParameterSet("Active") || !req->getParams()->isQueryParameterSet("StartActiveTime") || !req->getParams()->isQueryParameterSet("EndActiveTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Name = getQueryParameterString(req, "Name");
    String Description = getQueryParameterString(req, "Description");
    String UId = getQueryParameterString(req, "UId");
    int Active = getQueryParameterint(req, "Active");
    EBPDateTime StartActiveTime = getQueryParameterEBPDateTime(req, "StartActiveTime");
    EBPDateTime EndActiveTime = getQueryParameterEBPDateTime(req, "EndActiveTime");

        response(res, handlecreate(Name, Description, UId, Active, StartActiveTime, EndActiveTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Name") || !req->getParams()->isQueryParameterSet("Description") || !req->getParams()->isQueryParameterSet("UId") || !req->getParams()->isQueryParameterSet("Active") || !req->getParams()->isQueryParameterSet("StartActiveTime") || !req->getParams()->isQueryParameterSet("EndActiveTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Name = getQueryParameterString(req, "Name");
    String Description = getQueryParameterString(req, "Description");
    String UId = getQueryParameterString(req, "UId");
    int Active = getQueryParameterint(req, "Active");
    EBPDateTime StartActiveTime = getQueryParameterEBPDateTime(req, "StartActiveTime");
    EBPDateTime EndActiveTime = getQueryParameterEBPDateTime(req, "EndActiveTime");
        
        response(res, handleupdate(id, Name, Description, UId, Active, StartActiveTime, EndActiveTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GUESTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String GuestsApis::getClassPath()
{
    return String(class_path.c_str());
}

String GuestsApis::handlecreate(String Name, String Description, String UId, int Active, EBPDateTime StartActiveTime, EBPDateTime EndActiveTime) {
    GuestsEntity* guestsEntity = new GuestsEntity(Name, Description, UId, Active, StartActiveTime, EndActiveTime);
    int id = guestsController->Add(*guestsEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String GuestsApis::handleupdate(int id, String Name, String Description, String UId, int Active, EBPDateTime StartActiveTime, EBPDateTime EndActiveTime) {
    GuestsEntity* guestsEntity = new GuestsEntity(id, Name, Description, UId, Active, StartActiveTime, EndActiveTime);
    
    if (guestsController->Update(*guestsEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String GuestsApis::handledelete(int id) {
    
    if (guestsController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String GuestsApis::handlegetAll() {
    return guestsController->GetAllJson();
}
String GuestsApis::handlegetById(int id) {
    return guestsController->GetById(id).toJson();
}
String GuestsApis::handleget(String query) {
    return guestsController->GetJson(query);
}

String GuestsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Name"], parameters["Description"], parameters["UId"], parameters["Active"].toInt(), parameters["StartActiveTime"], parameters["EndActiveTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Name"], parameters["Description"], parameters["UId"], parameters["Active"].toInt(), parameters["StartActiveTime"], parameters["EndActiveTime"]);
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

#endif //GUESTSApis_h

    