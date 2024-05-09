#ifndef RELAYAPIS_h
#define RELAYAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/RelayController.h"
#include "ModulePermissions.h"

class RelayApis : public ApiInterface
{
private:
    Context* context;
    RelayController* relayController;
    std::string class_path = "/relay";

public:
    RelayApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int ModuleId, int PinNumber, bool NormallyOpen);
    String handleupdate(int id, int ModuleId, int PinNumber, bool NormallyOpen);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RelayApis::RelayApis(Context* cntxt, bool add_apis): context(cntxt) {
    relayController = new RelayController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("PinNumber") || !req->getParams()->isQueryParameterSet("NormallyOpen"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int ModuleId = getQueryParameterint(req, "ModuleId");
        int PinNumber = getQueryParameterint(req, "PinNumber");
    bool NormallyOpen = boolean(getQueryParameterString(req, "NormallyOpen"));

        response(res, handlecreate(ModuleId, PinNumber, NormallyOpen));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("PinNumber") || !req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("NormallyOpen"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        int ModuleId = getQueryParameterint(req, "ModuleId");
        int PinNumber = getQueryParameterint(req, "PinNumber");
        bool NormallyOpen = getQueryParameterString(req, "NormallyOpen") == "true"? true: false;
        
        response(res, handleupdate(id, PinNumber, ModuleId,  NormallyOpen));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAY_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String RelayApis::getClassPath()
{
    return String(class_path.c_str());
}

String RelayApis::handlecreate(int ModuleId, int PinNumber, bool NormallyOpen) {
    RelayEntity* relayEntity = new RelayEntity(ModuleId, PinNumber, NormallyOpen);
    int id = relayController->Add(*relayEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String RelayApis::handleupdate(int id, int PinNumber, int ModuleId, bool NormallyOpen) {
    RelayEntity* relayEntity = new RelayEntity(id, PinNumber, ModuleId, NormallyOpen);
    
    if (relayController->Update(*relayEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String RelayApis::handledelete(int id) {
    
    if (relayController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String RelayApis::handlegetAll() {
    return relayController->GetAllJson();
}
String RelayApis::handlegetById(int id) {
    return relayController->GetById(id).toJson();
}
String RelayApis::handleget(String query) {
    return relayController->GetJson(query);
}

String RelayApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["ModuleId"].toInt(), parameters["PinNumber"].toInt(), parameters["NormallyOpen"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["ModuleId"].toInt(), parameters["PinNumber"].toInt(), parameters["NormallyOpen"].toInt());
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

#endif //RELAYApis_h

    