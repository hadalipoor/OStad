#ifndef LCDAPIS_h
#define LCDAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/LCDController.h"
#include "ModulePermissions.h"

class LCDApis : public ApiInterface
{
private:
    Context* context;
    LCDController* lcdController;
    std::string class_path = "/lcd";

public:
    LCDApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int ModuleId, int Address, int Rows, int Cols, String Type);
    String handleupdate(int id, int ModuleId, int Address, int Rows, int Cols, String Type);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LCDApis::LCDApis(Context* cntxt, bool add_apis): context(cntxt) {
    lcdController = new LCDController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("Address") || !req->getParams()->isQueryParameterSet("Rows") || !req->getParams()->isQueryParameterSet("Cols") || !req->getParams()->isQueryParameterSet("Type"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int ModuleId = getQueryParameterint(req, "ModuleId");
    int Address = getQueryParameterint(req, "Address");
    int Rows = getQueryParameterint(req, "Rows");
    int Cols = getQueryParameterint(req, "Cols");
    String Type = getQueryParameterString(req, "Type");

        response(res, handlecreate(ModuleId, Address, Rows, Cols, Type));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("Address") || !req->getParams()->isQueryParameterSet("Rows") || !req->getParams()->isQueryParameterSet("Cols") || !req->getParams()->isQueryParameterSet("Type"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int ModuleId = getQueryParameterint(req, "ModuleId");
    int Address = getQueryParameterint(req, "Address");
    int Rows = getQueryParameterint(req, "Rows");
    int Cols = getQueryParameterint(req, "Cols");
    String Type = getQueryParameterString(req, "Type");
        
        response(res, handleupdate(id, ModuleId, Address, Rows, Cols, Type));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LCDApis::getClassPath()
{
    return String(class_path.c_str());
}

String LCDApis::handlecreate(int ModuleId, int Address, int Rows, int Cols, String Type) {
    LCDEntity* lcdEntity = new LCDEntity(ModuleId, Address, Rows, Cols, Type);
    int id = lcdController->Add(*lcdEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LCDApis::handleupdate(int id, int ModuleId, int Address, int Rows, int Cols, String Type) {
    LCDEntity* lcdEntity = new LCDEntity(id, ModuleId, Address, Rows, Cols, Type);
    
    if (lcdController->Update(*lcdEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LCDApis::handledelete(int id) {
    
    if (lcdController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LCDApis::handlegetAll() {
    return lcdController->GetAllJson();
}
String LCDApis::handlegetById(int id) {
    return lcdController->GetById(id).toJson();
}
String LCDApis::handleget(String query) {
    return lcdController->GetJson(query);
}

String LCDApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["ModuleId"].toInt(), parameters["Address"].toInt(), parameters["Rows"].toInt(), parameters["Cols"].toInt(), parameters["Type"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["ModuleId"].toInt(), parameters["Address"].toInt(), parameters["Rows"].toInt(), parameters["Cols"].toInt(), parameters["Type"]);
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

#endif //LCDApis_h

    