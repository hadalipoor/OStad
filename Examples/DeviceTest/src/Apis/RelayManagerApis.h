
#ifndef RelayManagerApis_h
#define RelayManagerApis_h


#include "../AppContext.h"
#include "Permissions.h"
class RelayManagerApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/relaymanager";

public:
    RelayManagerApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleadd(String device_id, String name, String pin_number, String normally_open);
    String handleedit(String server_id, String device_id, String name, String pin_number, String normally_open);
    String handleremove_relay(String server_id);
    String handleget_all();
    String handleget_by_server_id(String server_id);
};

RelayManagerApis::RelayManagerApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RELAYMANAGER_ADD) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("device_id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("pin_number") || !req->getParams()->isQueryParameterSet("normally_open")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String device_id = getQueryParameterString(req, "device_id");
        String name = getQueryParameterString(req, "name");
        String pin_number = getQueryParameterString(req, "pin_number");
        String normally_open = getQueryParameterString(req, "normally_open");
        
        response(res, handleadd(device_id, name, pin_number, normally_open));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/edit"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RELAYMANAGER_EDIT) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id") || !req->getParams()->isQueryParameterSet("device_id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("pin_number") || !req->getParams()->isQueryParameterSet("normally_open")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String server_id = getQueryParameterString(req, "server_id");
        String device_id = getQueryParameterString(req, "device_id");
        String name = getQueryParameterString(req, "name");
        String pin_number = getQueryParameterString(req, "pin_number");
        String normally_open = getQueryParameterString(req, "normally_open");
        
        response(res, handleedit(server_id, device_id, name, pin_number, normally_open));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/remove_relay"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RELAYMANAGER_REMOVE_RELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String server_id = getQueryParameterString(req, "server_id");
        
        response(res, handleremove_relay(server_id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_all"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RELAYMANAGER_GET_ALL) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleget_all());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_by_server_id"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RELAYMANAGER_GET_BY_SERVER_ID) == AuthorizationResults::SUCCESFULL){return;}
        
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



String RelayManagerApis::handleadd(String device_id, String name, String pin_number, String normally_open) {
    return "";
}
String RelayManagerApis::handleedit(String server_id, String device_id, String name, String pin_number, String normally_open) {
    return "";
}
String RelayManagerApis::handleremove_relay(String server_id) {
    return "";
}
String RelayManagerApis::handleget_all() {
    return "";
}
String RelayManagerApis::handleget_by_server_id(String server_id) {
    return "";
}

String RelayManagerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleadd") {
        handleadd(parameters["device_id"], parameters["name"], parameters["pin_number"], parameters["normally_open"]);
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
