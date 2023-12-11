#ifndef RGBAPIS_h
#define RGBAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/RGBController.h"
#include "ModulePermissions.h"

class RGBApis : public ApiInterface
{
private:
    Context* context;
    RGBController* rgbController;
    std::string class_path = "/rgb";

public:
    RGBApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Type, int Rpin, int Gpin, int Bpin);
    String handleupdate(int id, String Type, int Rpin, int Gpin, int Bpin);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RGBApis::RGBApis(Context* cntxt, bool add_apis): context(cntxt) {
    rgbController = new RGBController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Type") || !req->getParams()->isQueryParameterSet("Rpin") || !req->getParams()->isQueryParameterSet("Gpin") || !req->getParams()->isQueryParameterSet("Bpin"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Type = getQueryParameterString(req, "Type");
    int Rpin = getQueryParameterint(req, "Rpin");
    int Gpin = getQueryParameterint(req, "Gpin");
    int Bpin = getQueryParameterint(req, "Bpin");

        response(res, handlecreate(Type, Rpin, Gpin, Bpin));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Type") || !req->getParams()->isQueryParameterSet("Rpin") || !req->getParams()->isQueryParameterSet("Gpin") || !req->getParams()->isQueryParameterSet("Bpin"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Type = getQueryParameterString(req, "Type");
    int Rpin = getQueryParameterint(req, "Rpin");
    int Gpin = getQueryParameterint(req, "Gpin");
    int Bpin = getQueryParameterint(req, "Bpin");
        
        response(res, handleupdate(id, Type, Rpin, Gpin, Bpin));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RGB_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String RGBApis::getClassPath()
{
    return String(class_path.c_str());
}

String RGBApis::handlecreate(String Type, int Rpin, int Gpin, int Bpin) {
    RGBEntity* rgbEntity = new RGBEntity(Type, Rpin, Gpin, Bpin);
    int id = rgbController->Add(*rgbEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String RGBApis::handleupdate(int id, String Type, int Rpin, int Gpin, int Bpin) {
    RGBEntity* rgbEntity = new RGBEntity(id, Type, Rpin, Gpin, Bpin);
    
    if (rgbController->Update(*rgbEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String RGBApis::handledelete(int id) {
    
    if (rgbController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String RGBApis::handlegetAll() {
    return rgbController->GetAllJson();
}
String RGBApis::handlegetById(int id) {
    return rgbController->GetById(id).toJson();
}
String RGBApis::handleget(String query) {
    return rgbController->GetJson(query);
}

String RGBApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["Type"], parameters["Rpin"].toInt(), parameters["Gpin"].toInt(), parameters["Bpin"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["Type"], parameters["Rpin"].toInt(), parameters["Gpin"].toInt(), parameters["Bpin"].toInt());
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

#endif //RGBApis_h

    