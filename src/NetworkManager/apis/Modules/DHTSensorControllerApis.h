
#ifndef DHTSensorControllerApis_h
#define DHTSensorControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class DHTSensorControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/dhtsensorcontroller";

public:
    DHTSensorControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlegetName(int server_id);
    String handlegetHumidity(int server_id);
    String handlegetTemperatureC(int server_id);
    String handlegetTemperatureF(int server_id);
    String handleisDataValid(int server_id);
    String handlegetEntity(int server_id);
};

DHTSensorControllerApis::DHTSensorControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getName"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_GETNAME) == AuthorizationResults::SUCCESFULL){return;}
        
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
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getHumidity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_GETHUMIDITY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetHumidity(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getTemperatureC"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_GETTEMPERATUREC) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetTemperatureC(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getTemperatureF"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_GETTEMPERATUREF) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlegetTemperatureF(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/isDataValid"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_ISDATAVALID) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleisDataValid(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getEntity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::DHTSENSORCONTROLLER_GETENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
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
}

String DHTSensorControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String DHTSensorControllerApis::handlegetName(int server_id) {
    return "";
}
String DHTSensorControllerApis::handlegetHumidity(int server_id) {
    return "";
}
String DHTSensorControllerApis::handlegetTemperatureC(int server_id) {
    return "";
}
String DHTSensorControllerApis::handlegetTemperatureF(int server_id) {
    return "";
}
String DHTSensorControllerApis::handleisDataValid(int server_id) {
    return "";
}
String DHTSensorControllerApis::handlegetEntity(int server_id) {
    return "";
}

String DHTSensorControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlegetName") {
        handlegetName(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetHumidity") {
        handlegetHumidity(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetTemperatureC") {
        handlegetTemperatureC(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetTemperatureF") {
        handlegetTemperatureF(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleisDataValid") {
        handleisDataValid(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetEntity") {
        handlegetEntity(parameters["server_id"].toInt());
        return "OK";
    }
    return "";
}

#endif //DHTSensorControllerApis_h
