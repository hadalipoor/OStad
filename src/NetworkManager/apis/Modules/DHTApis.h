#ifndef DHTAPIS_h
#define DHTAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/DHTController.h"
#include "ModulePermissions.h"

class DHTApis : public ApiInterface
{
private:
    Context* context;
    DHTController* dhtController;
    std::string class_path = "/dht";

public:
    DHTApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Type, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold);
    String handleupdate(int id, String Type, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

DHTApis::DHTApis(Context* cntxt, bool add_apis): context(cntxt) {
    dhtController = new DHTController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Type") || !req->getParams()->isQueryParameterSet("DryTreshold") || !req->getParams()->isQueryParameterSet("WetTreshold") || !req->getParams()->isQueryParameterSet("CoolTreshold") || !req->getParams()->isQueryParameterSet("HotTreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Type = getQueryParameterString(req, "Type");
    int DryTreshold = getQueryParameterint(req, "DryTreshold");
    int WetTreshold = getQueryParameterint(req, "WetTreshold");
    int CoolTreshold = getQueryParameterint(req, "CoolTreshold");
    int HotTreshold = getQueryParameterint(req, "HotTreshold");

        response(res, handlecreate(Type, DryTreshold, WetTreshold, CoolTreshold, HotTreshold));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Type") || !req->getParams()->isQueryParameterSet("DryTreshold") || !req->getParams()->isQueryParameterSet("WetTreshold") || !req->getParams()->isQueryParameterSet("CoolTreshold") || !req->getParams()->isQueryParameterSet("HotTreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Type = getQueryParameterString(req, "Type");
    int DryTreshold = getQueryParameterint(req, "DryTreshold");
    int WetTreshold = getQueryParameterint(req, "WetTreshold");
    int CoolTreshold = getQueryParameterint(req, "CoolTreshold");
    int HotTreshold = getQueryParameterint(req, "HotTreshold");
        
        response(res, handleupdate(id, Type, DryTreshold, WetTreshold, CoolTreshold, HotTreshold));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHT_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String DHTApis::getClassPath()
{
    return String(class_path.c_str());
}

String DHTApis::handlecreate(String Type, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold) {
    DHTEntity* dhtEntity = new DHTEntity(Type, DryTreshold, WetTreshold, CoolTreshold, HotTreshold);
    int id = dhtController->Add(*dhtEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String DHTApis::handleupdate(int id, String Type, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold) {
    DHTEntity* dhtEntity = new DHTEntity(id, Type, DryTreshold, WetTreshold, CoolTreshold, HotTreshold);
    
    if (dhtController->Update(*dhtEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String DHTApis::handledelete(int id) {
    
    if (dhtController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String DHTApis::handlegetAll() {
    return dhtController->GetAllJson();
}
String DHTApis::handlegetById(int id) {
    return dhtController->GetById(id).toJson();
}
String DHTApis::handleget(String query) {
    return dhtController->GetJson(query);
}

String DHTApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["Type"], parameters["DryTreshold"].toInt(), parameters["WetTreshold"].toInt(), parameters["CoolTreshold"].toInt(), parameters["HotTreshold"].toInt());
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["Type"], parameters["DryTreshold"].toInt(), parameters["WetTreshold"].toInt(), parameters["CoolTreshold"].toInt(), parameters["HotTreshold"].toInt());
    }
    if (functionName == "handledelete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "handlegetAll") {
        return handlegetAll();
    }
    if (functionName == "handlegetById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "handleget") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //DHTApis_h

    