#ifndef ButtonManagerApis_h
#define ButtonManagerApis_h

#include "./././Context.h"
#include "DevicePermissions.h"

class ButtonManagerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/buttonmanager";

public:
    ButtonManagerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleadd(String module_id, String button_type, String pin_number, String active_high, String pullup_active, String debounce_delay, String server_id);
    String handleedit(String server_id, String module_id, String button_type, String pin_number, String active_high, String pullup_active, String debounce_delay);
    String handleremove_button(String server_id);
    String handleget_all();
    String handleget_by_server_id(String server_id);
};

ButtonManagerApis::ButtonManagerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::BUTTONMANAGER_ADD) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);

        if(!isItemInBody(body, "module_id") || !isItemInBody(body, "button_type") || !isItemInBody(body, "pin_number") || !isItemInBody(body, "active_high") || !isItemInBody(body, "pullup_active") || !isItemInBody(body, "debounce_delay")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        String server_id = "0";
        if(isItemInBody(body, "server_id"))
        {
            server_id = getItemInBody(body, "server_id");
        }
        
        String module_id = getItemInBody(body, "module_id");
        String button_type = getItemInBody(body, "button_type");
        String pin_number = getItemInBody(body, "pin_number");
        String active_high = getItemInBody(body, "active_high");
        String pullup_active = getItemInBody(body, "pullup_active");
        String debounce_delay = getItemInBody(body, "debounce_delay");
        
        response(res, handleadd(module_id, button_type, pin_number, active_high, pullup_active, debounce_delay, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/edit"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::BUTTONMANAGER_EDIT) == AuthorizationResults::SUCCESFULL){return;}

        String body = getBodyString(req);

        if(!isItemInBody(body, "server_id") || !isItemInBody(body, "module_id") || !isItemInBody(body, "button_type") || !isItemInBody(body, "pin_number") || !isItemInBody(body, "active_high") || !isItemInBody(body, "pullup_active") || !isItemInBody(body, "debounce_delay")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String server_id = getItemInBody(body, "server_id");
        String module_id = getItemInBody(body, "module_id");
        String button_type = getItemInBody(body, "button_type");
        String pin_number = getItemInBody(body, "pin_number");
        String active_high = getItemInBody(body, "active_high");
        String pullup_active = getItemInBody(body, "pullup_active");
        String debounce_delay = getItemInBody(body, "debounce_delay");

        response(res, handleedit(server_id, module_id, button_type, pin_number, active_high, pullup_active, debounce_delay));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/remove"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::BUTTONMANAGER_REMOVE) == AuthorizationResults::SUCCESFULL){return;}

        String server_id = getQueryParameterString(req, "server_id");

        if(server_id.isEmpty() || !context->getValidation()->variableValidator()->isNumber(server_id)){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        response(res, handleremove_button(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_all"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::BUTTONMANAGER_GET_ALL) == AuthorizationResults::SUCCESFULL){return;}

        response(res, handleget_all());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_by_server_id"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::BUTTONMANAGER_GET_BY_SERVER_ID) == AuthorizationResults::SUCCESFULL){return;}

        String server_id = getQueryParameterString(req, "server_id");

        if(server_id.isEmpty() || !context->getValidation()->variableValidator()->isNumber(server_id)){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        response(res, handleget_by_server_id(server_id));
    }));
}

String ButtonManagerApis::getClassPath() {
    return String(class_path.c_str());
}

String ButtonManagerApis::callFunction(String functionName, std::map<String, String> parameters) {
    if (functionName == "handleadd") {
        handleadd(parameters["module_id"], parameters["button_type"], parameters["pin_number"], parameters["active_high"], parameters["pullup_active"], parameters["debounce_delay"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleedit") {
        handleedit(parameters["server_id"], parameters["module_id"], parameters["button_type"], parameters["pin_number"], parameters["active_high"], parameters["pullup_active"], parameters["debounce_delay"]);
        return "OK";
    }
    if (functionName == "handleremove_button") {
        handleremove_button(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleget_all") {
        handleget_all();
        return "OK";
    }
    if (functionName == "handleget_by_server_id") {
        handleget_by_server_id(parameters["server_id"]);
        return "OK";
    }
    return "";
}

String ButtonManagerApis::handleadd(String module_id, String button_type, String pin_number, String active_high, String pullup_active, String debounce_delay, String server_id) {
    if(!context->getValidation()->variableValidator()->isNumber(module_id) || !context->getValidation()->variableValidator()->isNumber(pin_number) || !context->getValidation()->variableValidator()->isNumber(active_high) || !context->getValidation()->variableValidator()->isNumber(pullup_active) || !context->getValidation()->variableValidator()->isNumber(debounce_delay)){
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    ButtonEntity buttonEntity = ButtonEntity(0, module_id.toInt(), button_type, pin_number.toInt(), active_high.toInt() == 1, pullup_active.toInt() == 1, debounce_delay.toInt());
    bool result = context->getDatabase()->getButtonController()->Add(buttonEntity);
    return jsonResponse(result, result ? "" : "Failed to add button.");
}

String ButtonManagerApis::handleedit(String server_id, String module_id, String button_type, String pin_number, String active_high, String pullup_active, String debounce_delay) {
    if(!context->getValidation()->variableValidator()->isNumber(server_id) || !context->getValidation()->variableValidator()->isNumber(module_id) || !context->getValidation()->variableValidator()->isNumber(pin_number) || !context->getValidation()->variableValidator()->isNumber(active_high) || !context->getValidation()->variableValidator()->isNumber(pullup_active) || !context->getValidation()->variableValidator()->isNumber(debounce_delay)){
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    ButtonEntity buttonEntity = ButtonEntity(module_id.toInt(), button_type, pin_number.toInt(), active_high.toInt() == 1, pullup_active.toInt() == 1, debounce_delay.toInt());
    bool result = context->getDatabase()->getButtonController()->Update(buttonEntity);
    return jsonResponse(result, result ? "" : "Failed to update button.");
}

String ButtonManagerApis::handleremove_button(String server_id) {
    if(!context->getValidation()->variableValidator()->isNumber(server_id)){
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    bool result = context->getDatabase()->getButtonController()->Delete(server_id.toInt());
    return jsonResponse(result, result ? "" : "Failed to remove button.");
}

String ButtonManagerApis::handleget_all() {
    // Implement the method to get all buttons
    return "";
}

String ButtonManagerApis::handleget_by_server_id(String server_id) {
    // Implement the method to get buttons by server ID
    return "";
}

#endif //ButtonManagerApis_h
