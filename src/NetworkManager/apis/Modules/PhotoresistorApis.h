#ifndef PHOTORESISTORAPIS_h
#define PHOTORESISTORAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/PhotoresistorController.h"
#include "ModulePermissions.h"

class PhotoresistorApis : public ApiInterface
{
private:
    Context* context;
    PhotoresistorController* photoresistorController;
    std::string class_path = "/photoresistor";

public:
    PhotoresistorApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int LowTreshold, int HighTreshold);
    String handleupdate(int id, int LowTreshold, int HighTreshold);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PhotoresistorApis::PhotoresistorApis(Context* cntxt, bool add_apis): context(cntxt) {
    photoresistorController = new PhotoresistorController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("LowTreshold") || !req->getParams()->isQueryParameterSet("HighTreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int LowTreshold = getQueryParameterint(req, "LowTreshold");
    int HighTreshold = getQueryParameterint(req, "HighTreshold");

        response(res, handlecreate(LowTreshold, HighTreshold));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("LowTreshold") || !req->getParams()->isQueryParameterSet("HighTreshold"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int LowTreshold = getQueryParameterint(req, "LowTreshold");
    int HighTreshold = getQueryParameterint(req, "HighTreshold");
        
        response(res, handleupdate(id, LowTreshold, HighTreshold));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::PHOTORESISTOR_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PhotoresistorApis::getClassPath()
{
    return String(class_path.c_str());
}

String PhotoresistorApis::handlecreate(int LowTreshold, int HighTreshold) {
    PhotoresistorEntity* photoresistorEntity = new PhotoresistorEntity(LowTreshold, HighTreshold);
    int id = photoresistorController->Add(*photoresistorEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PhotoresistorApis::handleupdate(int id, int LowTreshold, int HighTreshold) {
    PhotoresistorEntity* photoresistorEntity = new PhotoresistorEntity(id, LowTreshold, HighTreshold);
    
    if (photoresistorController->Update(*photoresistorEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PhotoresistorApis::handledelete(int id) {
    
    if (photoresistorController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PhotoresistorApis::handlegetAll() {
    return photoresistorController->GetAllJson();
}
String PhotoresistorApis::handlegetById(int id) {
    return photoresistorController->GetById(id).toJson();
}
String PhotoresistorApis::handleget(String query) {
    return photoresistorController->GetJson(query);
}

String PhotoresistorApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["LowTreshold"].toInt(), parameters["HighTreshold"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["LowTreshold"].toInt(), parameters["HighTreshold"].toInt());
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

#endif //PHOTORESISTORApis_h

    