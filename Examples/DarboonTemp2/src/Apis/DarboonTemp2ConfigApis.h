#ifndef DARBOONTEMP2CONFIGAPIS_h
#define DARBOONTEMP2CONFIGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/DarboonTemp2ConfigController.h"
#include "Permissions.h"

class DarboonTemp2ConfigApis : public ApiInterface
{
private:
    AppContext* context;
    DarboonTemp2ConfigController* darboontemp2configController;
    std::string class_path = "/darboontemp2config";

public:
    DarboonTemp2ConfigApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Key, String Value);
    String handleupdate(int id, String Key, String Value);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

DarboonTemp2ConfigApis::DarboonTemp2ConfigApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    darboontemp2configController = new DarboonTemp2ConfigController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Key") || !req->getParams()->isQueryParameterSet("Value"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Key = getQueryParameterString(req, "Key");
    String Value = getQueryParameterString(req, "Value");

        response(res, handlecreate(Key, Value));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Key") || !req->getParams()->isQueryParameterSet("Value"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Key = getQueryParameterString(req, "Key");
    String Value = getQueryParameterString(req, "Value");
        
        response(res, handleupdate(id, Key, Value));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DARBOONTEMP2CONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String DarboonTemp2ConfigApis::getClassPath()
{
    return String(class_path.c_str());
}

String DarboonTemp2ConfigApis::handlecreate(String Key, String Value) {
    DarboonTemp2ConfigEntity* darboontemp2configEntity = new DarboonTemp2ConfigEntity(Key, Value);
    int id = darboontemp2configController->Add(*darboontemp2configEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String DarboonTemp2ConfigApis::handleupdate(int id, String Key, String Value) {
    DarboonTemp2ConfigEntity* darboontemp2configEntity = new DarboonTemp2ConfigEntity(id, Key, Value);
    
    if (darboontemp2configController->Update(*darboontemp2configEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String DarboonTemp2ConfigApis::handledelete(int id) {
    
    if (darboontemp2configController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String DarboonTemp2ConfigApis::handlegetAll() {
    return darboontemp2configController->GetAllJson();
}
String DarboonTemp2ConfigApis::handlegetById(int id) {
    return darboontemp2configController->GetById(id).toJson();
}
String DarboonTemp2ConfigApis::handleget(String query) {
    return darboontemp2configController->GetJson(query);
}

String DarboonTemp2ConfigApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Key"], parameters["Value"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Key"], parameters["Value"]);
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

#endif //DARBOONTEMP2CONFIGApis_h

    