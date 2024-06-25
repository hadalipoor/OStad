#ifndef RFIDAPIS_h
#define RFIDAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/Modules/RFIDController.h"
#include "ModulePermissions.h"

class RFIDApis : public ApiInterface
{
private:
    Context* context;
    RFIDController* rfidController;
    std::string class_path = "/rfid";

public:
    RFIDApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int ModuleId, int PinNumber1, int PinNumber2);
    String handleupdate(int id, int ModuleId, int PinNumber1, int PinNumber2);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RFIDApis::RFIDApis(Context* cntxt, bool add_apis): context(cntxt) {
    rfidController = new RFIDController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body,"ModuleId") || !isItemInBody(body,"PinNumber1") || !isItemInBody(body,"PinNumber2"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }
        
        
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "ModuleId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int ModuleId = getItemInBody(body, "ModuleId").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "PinNumber1")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int PinNumber1 = getItemInBody(body, "PinNumber1").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "PinNumber2")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int PinNumber2 = getItemInBody(body, "PinNumber2").toInt();

        response(res, handlecreate(ModuleId, PinNumber1, PinNumber2));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body, "id") || !isItemInBody(body,"ModuleId") || !isItemInBody(body,"PinNumber1") || !isItemInBody(body,"PinNumber2"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       
        int id = getItemInBody(body, "id").toInt();
        
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "ModuleId")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int ModuleId = getItemInBody(body, "ModuleId").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "PinNumber1")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int PinNumber1 = getItemInBody(body, "PinNumber1").toInt();
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "PinNumber2")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int PinNumber2 = getItemInBody(body, "PinNumber2").toInt();
        
        response(res, handleupdate(id, ModuleId, PinNumber1, PinNumber2));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        
        if (!isItemInBody(body, "id"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       
        int id = getItemInBody(body, "id").toInt();
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }       

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RFID_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, jsonResponse(false, MISSING_INPUT_PARAMS_MESSAGE));
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String RFIDApis::getClassPath()
{
    return String(class_path.c_str());
}

String RFIDApis::handlecreate(int ModuleId, int PinNumber1, int PinNumber2) {
    RFIDEntity* rfidEntity = new RFIDEntity(ModuleId, PinNumber1, PinNumber2);
    int id = rfidController->Add(*rfidEntity);
    if (id != -1)
    {
        return jsonResponse(true, CREATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, CREATE_FAILED_MESSAGE);
}
String RFIDApis::handleupdate(int id, int ModuleId, int PinNumber1, int PinNumber2) {
    RFIDEntity* rfidEntity = new RFIDEntity(id, ModuleId, PinNumber1, PinNumber2);
    
    if (rfidController->Update(*rfidEntity))
    {
        return jsonResponse(true, UPDATE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, UPDATE_FAILED_MESSAGE);
}
String RFIDApis::handledelete(int id) {
    
    if (rfidController->Delete(id))
    {
        return jsonResponse(true, DELETE_SUCCESFULL_MESSAGE);
    }
    
    return jsonResponse(false, DELETE_FAILED_MESSAGE);
}
String RFIDApis::handlegetAll() {
    return rfidController->GetAllJson();
}
String RFIDApis::handlegetById(int id) {
    return rfidController->GetById(id).toJson();
}
String RFIDApis::handleget(String query) {
    return rfidController->GetJson(query);
}

String RFIDApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["ModuleId"].toInt(), parameters["PinNumber1"].toInt(), parameters["PinNumber2"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["ModuleId"].toInt(), parameters["PinNumber1"].toInt(), parameters["PinNumber2"].toInt());
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

#endif //RFIDApis_h

    