
#ifndef RelayManagerApis_h
#define RelayManagerApis_h


#include "../../../Context.h"
#include "DevicePermissions.h"

class RelayManagerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/relaymanager";

public:
    RelayManagerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleadd(String chip_id, String name, String pin_number, String normally_open, String server_id);
    String handleedit(String server_id, String chip_id, String name, String pin_number, String normally_open);
    String handleremove_relay(String server_id);
    String handleget_all();
    String handleget_by_server_id(String server_id);
};

RelayManagerApis::RelayManagerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::RELAYMANAGER_ADD) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);

        if(!isItemInBody(body, "chip_id") || !isItemInBody(body, "name") || !isItemInBody(body, "pin_number") || !isItemInBody(body, "normally_open")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        String server_id = "0";
        if(isItemInBody(body, "server_id"))
        {
            server_id = getItemInBody(body, "server_id");
        }
        
        String chip_id = getItemInBody(body, "chip_id");
        String name = getItemInBody(body, "name");
        String pin_number = getItemInBody(body, "pin_number");
        String normally_open = getItemInBody(body, "normally_open");
        
        response(res, handleadd(chip_id, name, pin_number, normally_open, server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/edit"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::RELAYMANAGER_EDIT) == AuthorizationResults::SUCCESFULL){return;}
        
        String body = getBodyString(req);

        if(!isItemInBody(body, "chip_id") || !isItemInBody(body, "name") || !isItemInBody(body, "pin_number") || !isItemInBody(body, "normally_open") || !isItemInBody(body, "server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String server_id = getItemInBody(body, "server_id");
        String chip_id = getItemInBody(body, "chip_id");
        String name = getItemInBody(body, "name");
        String pin_number = getItemInBody(body, "pin_number");
        String normally_open = getItemInBody(body, "normally_open");
        
        response(res, handleedit(server_id, chip_id, name, pin_number, normally_open));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/remove_relay"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::RELAYMANAGER_REMOVE_RELAY) == AuthorizationResults::SUCCESFULL){return;}
        String body = getBodyString(req);
        if(!isItemInBody(body, "server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String server_id = getItemInBody(body, "server_id");
        Serial.print("server_id = ");
        Serial.println(server_id);
        response(res, handleremove_relay(server_id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_all"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::RELAYMANAGER_GET_ALL) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleget_all());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_by_server_id"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::RELAYMANAGER_GET_BY_SERVER_ID) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String server_id = getQueryParameterString(req, "server_id");
        
        response(res, handleget_by_server_id(server_id));
    }));
}

String RelayManagerApis::getClassPath()
{
    return String(class_path.c_str());
}



String RelayManagerApis::handleadd(String chip_id, String name, String pin_number, String normally_open, String server_id) {
    if(!context->getValidation()->variableValidator()->isNumber(pin_number) || !context->getValidation()->variableValidator()->isNumber(server_id))
    {
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    return jsonResponse(context->getDeviceManager()->getRelayManager()->addRelay(name, chip_id, pin_number.toInt(), normally_open == "true"? true : false, server_id.toInt()), "");
}
String RelayManagerApis::handleedit(String server_id, String chip_id, String name, String pin_number, String normally_open) {
    if(!context->getValidation()->variableValidator()->isNumber(pin_number) || !context->getValidation()->variableValidator()->isNumber(server_id))
    {
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    return jsonResponse(context->getDeviceManager()->getRelayManager()->editRelay(server_id.toInt(), name, chip_id, pin_number.toInt(), normally_open == "true"? true : false),"");
}
String RelayManagerApis::handleremove_relay(String server_id) {
    if(!context->getValidation()->variableValidator()->isNumber(server_id))
    {
        return jsonResponse(false, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
    }

    return jsonResponse(context->getDeviceManager()->getRelayManager()->removeRelay(server_id.toInt()),"");
}
String RelayManagerApis::handleget_all() {
    return "";
}
String RelayManagerApis::handleget_by_server_id(String server_id) {
    return "";
}

String RelayManagerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleadd") {
        handleadd(parameters["device_id"], parameters["name"], parameters["pin_number"], parameters["normally_open"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleedit") {
        handleedit(parameters["server_id"], parameters["device_id"], parameters["name"], parameters["pin_number"], parameters["normally_open"]);
        return "OK";
    }
    if (functionName == "handleremove_relay") {
        handleremove_relay(parameters["server_id"]);
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

#endif //RelayManagerApis_h
