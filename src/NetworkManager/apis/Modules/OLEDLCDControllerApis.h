
#ifndef OLEDLCDControllerApis_h
#define OLEDLCDControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class OLEDLCDControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/oledlcdcontroller";

public:
    OLEDLCDControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleprint(int server_id, String message);
    String handleprintAt(int server_id, int column, int row, String message);
    String handledrawText(int server_id, String text, int textsize);
    String handleclean(int server_id);
    String handlegetEntity(int server_id);
};

OLEDLCDControllerApis::OLEDLCDControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/print"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::OLEDLCDCONTROLLER_PRINT) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id") || !isItemInBody(body,"message")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        String message = getItemInBody(body, "message");
        
        response(res, handleprint(server_id, message));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/printAt"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::OLEDLCDCONTROLLER_PRINTAT) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id") || !isItemInBody(body,"column") || !isItemInBody(body,"row") || !isItemInBody(body,"message")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "column")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int column = getItemInBody(body, "column").toInt();
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "row")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int row = getItemInBody(body, "row").toInt();
        String message = getItemInBody(body, "message");
        
        response(res, handleprintAt(server_id, column, row, message));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/drawText"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::OLEDLCDCONTROLLER_DRAWTEXT) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);
        if(!isItemInBody(body,"server_id") || !isItemInBody(body,"text") || !isItemInBody(body,"textsize")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "server_id")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int server_id = getItemInBody(body, "server_id").toInt();
        String text = getItemInBody(body, "text");
        if (!context->getValidation()->variableValidator()->isNumber(getItemInBody(body, "textSize")))
        {
            response(res, jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE));
            return;
        }
        int textsize = getItemInBody(body, "textSize").toInt();
        
        response(res, handledrawText(server_id, text, textsize));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/clean"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::OLEDLCDCONTROLLER_CLEAN) == AuthorizationResults::SUCCESFULL){return;}
        
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
        
        response(res, handleclean(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getEntity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::OLEDLCDCONTROLLER_GETENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
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
        
        response(res, handlegetEntity(server_id));
    }));
}

String OLEDLCDControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String OLEDLCDControllerApis::handleprint(int server_id, String message) {
    return "";
}
String OLEDLCDControllerApis::handleprintAt(int server_id, int column, int row, String message) {
    return "";
}
String OLEDLCDControllerApis::handledrawText(int server_id, String text, int textsize) {
    return "";
}
String OLEDLCDControllerApis::handleclean(int server_id) {
    return "";
}
String OLEDLCDControllerApis::handlegetEntity(int server_id) {
    return "";
}

String OLEDLCDControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleprint") {
        handleprint(parameters["server_id"].toInt(), parameters["message"]);
        return "OK";
    }
    if (functionName == "handleprintAt") {
        handleprintAt(parameters["server_id"].toInt(), parameters["column"].toInt(), parameters["row"].toInt(), parameters["message"]);
        return "OK";
    }
    if (functionName == "handledrawText") {
        handledrawText(parameters["server_id"].toInt(), parameters["text"], parameters["textsize"].toInt());
        return "OK";
    }
    if (functionName == "handleclean") {
        handleclean(parameters["server_id"].toInt());
        return "OK";
    }
    if (functionName == "handlegetEntity") {
        handlegetEntity(parameters["server_id"].toInt());
        return "OK";
    }
    return "";
}

#endif //OLEDLCDControllerApis_h
