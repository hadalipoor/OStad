
#ifndef LCD16x2ControllerApis_h
#define LCD16x2ControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
class LCD16x2ControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/lcd16x2controller";

public:
    LCD16x2ControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handledrawText(int server_id, String text, int textsize);
    String handleclean(int server_id);
    String handlegetEntity(int server_id);
};

LCD16x2ControllerApis::LCD16x2ControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;
    
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/drawText"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD16X2CONTROLLER_DRAWTEXT) == AuthorizationResults::SUCCESFULL){return;}
        
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
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD16X2CONTROLLER_CLEAN) == AuthorizationResults::SUCCESFULL){return;}
        
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
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::LCD16X2CONTROLLER_GETENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
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

String LCD16x2ControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String LCD16x2ControllerApis::handledrawText(int server_id, String text, int textsize) {
    return "";
}
String LCD16x2ControllerApis::handleclean(int server_id) {
    return "";
}
String LCD16x2ControllerApis::handlegetEntity(int server_id) {
    return "";
}

String LCD16x2ControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
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

#endif //LCD16x2ControllerApis_h
