
#ifndef ButtonControllerApis_h
#define ButtonControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class ButtonControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/buttoncontroller";

public:
    ButtonControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlesetDebounceDelay(int server_id, int delay_millis);
    String handlesetLongPressTime(int server_id, int time);
    String handlegetState(int server_id);
    String handlegetName(int server_id);
    String handlegetEntity(int server_id);
    String handlegetPinNumber(int server_id);
    String handlegetActiveHigh(int server_id);
    String handlegetPullUpActive(int server_id);
};

ButtonControllerApis::ButtonControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setDebounceDelay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_SETDEBOUNCEDELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id") || !isItemInBody(body,"delay_millis")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "delay_millis")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int delay_millis = getItemInBody(body, "delay_millis").toInt();
        
        response(res, handlesetDebounceDelay(server_id, delay_millis));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setLongPressTime"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_SETLONGPRESSTIME) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id") || !isItemInBody(body,"time")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "time")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int time = getItemInBody(body, "time").toInt();
        
        response(res, handlesetLongPressTime(server_id, time));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getState"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETSTATE) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetState(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getName"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETNAME) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetName(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getEntity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetEntity(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPinNumber"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETPINNUMBER) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetPinNumber(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getActiveHigh"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETACTIVEHIGH) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetActiveHigh(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPullUpActive"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::BUTTONCONTROLLER_GETPULLUPACTIVE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetPullUpActive(server_id));
    }));
}

String ButtonControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String ButtonControllerApis::handlesetDebounceDelay(int server_id, int delay_millis) {
    return "";
}
String ButtonControllerApis::handlesetLongPressTime(int server_id, int time) {
    return "";
}
String ButtonControllerApis::handlegetState(int server_id) {
    return "";
}
String ButtonControllerApis::handlegetName(int server_id) {
    return "";
}
String ButtonControllerApis::handlegetEntity(int server_id) {
    return "";
}
String ButtonControllerApis::handlegetPinNumber(int server_id) {
    return "";
}
String ButtonControllerApis::handlegetActiveHigh(int server_id) {
    return "";
}
String ButtonControllerApis::handlegetPullUpActive(int server_id) {
    return "";
}

String ButtonControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlesetDebounceDelay") {
        handlesetDebounceDelay(parameters["server_id"].toInt(), parameters["delay_millis"].toInt());
        return "OK";
    }
    if (functionName == "handlesetLongPressTime") {
        handlesetLongPressTime(parameters["server_id"].toInt(), parameters["time"].toInt());
        return "OK";
    }
    if (functionName == "handlegetState") {
        handlegetState(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetName") {
        handlegetName(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetEntity") {
        handlegetEntity(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetPinNumber") {
        handlegetPinNumber(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetActiveHigh") {
        handlegetActiveHigh(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetPullUpActive") {
        handlegetPullUpActive(parameters["server_id"].toInt());
        return "OK";
    }
    return "";
}

#endif //ButtonControllerApis_h
