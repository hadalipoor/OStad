
#ifndef RelayControllerApis_h
#define RelayControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class RelayControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/relaycontroller";

public:
    RelayControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleturn_on(int server_id);
    String handleturn_on_after_delay(int delay_millis, int server_id);
    String handleturn_off(int server_id);
    String handleturn_off_after_delay(int delay_millis, int server_id);
    String handleturn_on_for_delay(int delay_millis, int serverid);
    String handleturn_off_for_delay(int delay_millis, int serverid);
    String handleget_state(int server_id);
    String handleset_normally_open(bool normally_open, int server_id);
    String handleget_normally_open(int server_id);
    String handleset_pin_number(int pin_number, int server_id);
    String handleget_pin_number(int server_id);
    String handleget_entity(int server_id);
};

RelayControllerApis::RelayControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_on"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_TURN_ON) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleturn_on(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_on_after_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_TURN_ON_AFTER_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"delay_millis") || !isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "delay_millis")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int delay_millis = getItemInBody(body, "delay_millis").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleturn_on_after_delay(delay_millis, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_off"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_TURN_OFF) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleturn_off(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_off_after_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_TURN_OFF_AFTER_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"delay_millis") || !isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "delay_millis")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int delay_millis = getItemInBody(body, "delay_millis").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleturn_off_after_delay(delay_millis, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_state"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_GET_STATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleget_state(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/set_normally_open"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_SET_NORMALLY_OPEN) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"normally_open") || !isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String normallyOpenStr = getItemInBody(body, "normally_open");
        normallyOpenStr.toLowerCase();
        if (normallyOpenStr != "true" && normallyOpenStr == "false")
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        bool normally_open = normallyOpenStr == "true" ? true : false ;
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleset_normally_open(normally_open, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_normally_open"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_GET_NORMALLY_OPEN) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleget_normally_open(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/set_pin_number"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_SET_PIN_NUMBER) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"pin_number") || !isItemInBody(body,"server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "pin_number")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int pin_number = getItemInBody(body, "pin_number").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        
        response(res, handleset_pin_number(pin_number, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_pin_number"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_GET_PIN_NUMBER) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleget_pin_number(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_entity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYCONTROLLER_GET_ENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleget_entity(server_id));
    }));
}

String RelayControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String RelayControllerApis::handleturn_on(int serverid) {
    context->getModules()->getRelay(serverid)->turnOn();
    return "Successful";
}
String RelayControllerApis::handleturn_on_after_delay(int delay_millis, int serverid) {
    context->getModules()->getRelay(serverid)->turnOnAfterDelay(delay_millis);
    return "Successful";
}
String RelayControllerApis::handleturn_off(int serverid) {
    IRelay* _relay = context->getModules()->getRelay(serverid);
    _relay->turnOff();
    return "Successful";
}
String RelayControllerApis::handleturn_off_after_delay(int delay_millis, int serverid) {
    context->getModules()->getRelay(serverid)->turnOffAfterDelay(delay_millis);
    return "Successful";
}
String RelayControllerApis::handleturn_on_for_delay(int delay_millis, int serverid) {
    context->getModules()->getRelay(serverid)->turnOnForDelay(delay_millis);
    return "Successful";
}
String RelayControllerApis::handleturn_off_for_delay(int delay_millis, int serverid) {
    context->getModules()->getRelay(serverid)->turnOffForDelay(delay_millis);
    return "Successful";
}
String RelayControllerApis::handleget_state(int serverid) {
    return String(context->getModules()->getRelay(serverid)->getState());
}
String RelayControllerApis::handleset_normally_open(bool normallyopen, int serverid) {
    context->getModules()->getRelay(serverid)->setNormallyOpen(normallyopen);
    return "Successful";
}
String RelayControllerApis::handleget_normally_open(int serverid) {
    return context->getModules()->getRelay(serverid)->getNormallyOpen() ? "true" : "false";
}
String RelayControllerApis::handleset_pin_number(int pinnumber, int serverid) {
    context->getModules()->getRelay(serverid)->setNormallyOpen(pinnumber);
    return "Successful";
}
String RelayControllerApis::handleget_pin_number(int serverid) {
    return String(context->getModules()->getRelay(serverid)->getPinNumber());
}
String RelayControllerApis::handleget_entity(int serverid) {
    RelayFullEntity* relay = context->getModules()->getRelay(serverid)->getEntity();

    return relay->getJsonString();
}

String RelayControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleturn_on") {
        handleturn_on(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleturn_on_after_delay") {
        handleturn_on_after_delay(parameters["delay_millis"].toInt(), parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleturn_off") {
        handleturn_off(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleturn_off_after_delay") {
        handleturn_off_after_delay(parameters["delay_millis"].toInt(), parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleturn_on_for_delay") {
        handleturn_on_for_delay(parameters["delay_millis"].toInt(), parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleturn_off_for_delay") {
        handleturn_off_for_delay(parameters["delay_millis"].toInt(), parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleget_state") {
        handleget_state(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleset_normally_open") {
        handleset_normally_open(parameters["normallyopen"], parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleget_normally_open") {
        handleget_normally_open(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleset_pin_number") {
        handleset_pin_number(parameters["pinnumber"].toInt(), parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleget_pin_number") {
        handleget_pin_number(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleget_entity") {
        handleget_entity(parameters["server_id"].toInt());
        return "OK";
    }
    return "";
}



#endif //RelayControllerApis_h
