#ifndef BUTTONAPIS_h
#define BUTTONAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/ButtonController.h"
#include "ModulePermissions.h"

class ButtonApis : public ApiInterface
{
private:
    Context* context;
    ButtonController* buttonController;
    std::string class_path = "/button";

public:
    ButtonApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int ModuleId, int pinNumber, String ButtonType, bool ActiveHigh, bool PullupActive, int DebounceDelay);
    String handleupdate(int id, int pinNumber, int ModuleId, String ButtonType, bool ActiveHigh, bool PullupActive, int DebounceDelay);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ButtonApis::ButtonApis(Context* cntxt, bool add_apis): context(cntxt) {
    buttonController = new ButtonController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("ButtonType") || !req->getParams()->isQueryParameterSet("ActiveHigh") || !req->getParams()->isQueryParameterSet("PullupActive") || !req->getParams()->isQueryParameterSet("DebounceDelay"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int ModuleId = getQueryParameterint(req, "ModuleId");
         int pinNumber = getQueryParameterint(req, "PinNumber");
    String ButtonType = getQueryParameterString(req, "ButtonType");
    bool ActiveHigh = boolean(getQueryParameterString(req, "ActiveHigh"));
    bool PullupActive = boolean(getQueryParameterString(req, "PullupActive"));
    int DebounceDelay = getQueryParameterint(req, "DebounceDelay");

        response(res, handlecreate(ModuleId,pinNumber, ButtonType, ActiveHigh, PullupActive, DebounceDelay));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("PinNumber") || !req->getParams()->isQueryParameterSet("ModuleId") || !req->getParams()->isQueryParameterSet("ButtonType") || !req->getParams()->isQueryParameterSet("ActiveHigh") || !req->getParams()->isQueryParameterSet("PullupActive") || !req->getParams()->isQueryParameterSet("DebounceDelay"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int ModuleId = getQueryParameterint(req, "ModuleId");
         int pinNumber = getQueryParameterint(req, "PinNumber");
    String ButtonType = getQueryParameterString(req, "ButtonType");
    bool ActiveHigh = boolean(getQueryParameterString(req, "ActiveHigh"));
    bool PullupActive = boolean(getQueryParameterString(req, "PullupActive"));
    int DebounceDelay = getQueryParameterint(req, "DebounceDelay");
        
        response(res, handleupdate(id, pinNumber, ModuleId, ButtonType, ActiveHigh, PullupActive, DebounceDelay));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTON_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String ButtonApis::getClassPath()
{
    return String(class_path.c_str());
}

String ButtonApis::handlecreate(int ModuleId, int pinNumber, String ButtonType, bool ActiveHigh, bool PullupActive, int DebounceDelay) {
    ButtonEntity* buttonEntity = new ButtonEntity(ModuleId, pinNumber, ButtonType, ActiveHigh, PullupActive, DebounceDelay);
    int id = buttonController->Add(*buttonEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String ButtonApis::handleupdate(int id, int pinNumber, int ModuleId, String ButtonType, bool ActiveHigh, bool PullupActive, int DebounceDelay) {
    ButtonEntity* buttonEntity = new ButtonEntity(id,  pinNumber, ModuleId, ButtonType, ActiveHigh, PullupActive, DebounceDelay);
    
    if (buttonController->Update(*buttonEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String ButtonApis::handledelete(int id) {
    
    if (buttonController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String ButtonApis::handlegetAll() {
    return buttonController->GetAllJson();
}
String ButtonApis::handlegetById(int id) {
    return buttonController->GetById(id).toJson();
}
String ButtonApis::handleget(String query) {
    return buttonController->GetJson(query);
}

String ButtonApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["ModuleId"].toInt(), parameters["PinNumber"].toInt(), parameters["ButtonType"], parameters["ActiveHigh"].toInt(), parameters["PullupActive"].toInt(), parameters["DebounceDelay"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["PinNumber"].toInt(), parameters["ModuleId"].toInt(), parameters["ButtonType"], parameters["ActiveHigh"].toInt(), parameters["PullupActive"].toInt(), parameters["DebounceDelay"].toInt());
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

#endif //BUTTONApis_h

    