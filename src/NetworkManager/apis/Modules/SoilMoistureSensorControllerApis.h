
#ifndef SoilMoistureSensorControllerApis_h
#define SoilMoistureSensorControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class SoilMoistureSensorControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/soilmoisturesensorcontroller";

public:
    SoilMoistureSensorControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlereadMoisture(int server_id);
    String handleisDry(int server_id);
    String handleisWet(int server_id);
    String handlegetEntity(int server_id);
};

SoilMoistureSensorControllerApis::SoilMoistureSensorControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/readMoisture"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURESENSORCONTROLLER_READMOISTURE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handlereadMoisture(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/isDry"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURESENSORCONTROLLER_ISDRY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleisDry(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/isWet"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURESENSORCONTROLLER_ISWET) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getQueryParameterString(req, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getQueryParameterint(req, "server_id");
        
        response(res, handleisWet(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getEntity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::SOILMOISTURESENSORCONTROLLER_GETENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
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

String SoilMoistureSensorControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String SoilMoistureSensorControllerApis::handlereadMoisture(int server_id) {
    return "";
}
String SoilMoistureSensorControllerApis::handleisDry(int server_id) {
    return "";
}
String SoilMoistureSensorControllerApis::handleisWet(int server_id) {
    return "";
}
String SoilMoistureSensorControllerApis::handlegetEntity(int server_id) {
    return "";
}

String SoilMoistureSensorControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlereadMoisture") {
        if (!context->getValidation()->variableValidator()->isNumber(parameters["server_id"]))
        {
            return "false";
        }
        
        handlereadMoisture(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleisDry") {
        if (!context->getValidation()->variableValidator()->isNumber(parameters["server_id"]))
        {
            return "false";
        }
        handleisDry(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handleisWet") {
        if (!context->getValidation()->variableValidator()->isNumber(parameters["server_id"]))
        {
            return "false";
        }

        handleisWet(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetEntity") {
        if (!context->getValidation()->variableValidator()->isNumber(parameters["server_id"]))
        {
            return "false";
        }

        handlegetEntity(parameters["server_id"].toInt());
        return "OK";
    }
    return "";
}

#endif //SoilMoistureSensorControllerApis_h
