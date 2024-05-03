
#ifndef DeviceManagerApis_h
#define DeviceManagerApis_h


#include "../AppContext.h"
#include "Permissions.h"
class DeviceManagerApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/devicemanager";

public:
    DeviceManagerApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleadd_device(String app_ssid, String app_password, String ip, String device_name, String server_name, String server_chip_id);
    String handleremove_device();
};

DeviceManagerApis::DeviceManagerApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add_device"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICEMANAGER_ADD_DEVICE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("app_ssid") || !req->getParams()->isQueryParameterSet("app_password") || !req->getParams()->isQueryParameterSet("ip") || !req->getParams()->isQueryParameterSet("device_name") || !req->getParams()->isQueryParameterSet("server_name") || !req->getParams()->isQueryParameterSet("server_chip_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String app_ssid = getQueryParameterString(req, "app_ssid");
        String app_password = getQueryParameterString(req, "app_password");
        String ip = getQueryParameterString(req, "ip");
        String device_name = getQueryParameterString(req, "device_name");
        String server_name = getQueryParameterString(req, "server_name");
        String server_chip_id = getQueryParameterString(req, "server_chip_id");
        
        response(res, handleadd_device(app_ssid, app_password, ip, device_name, server_name, server_chip_id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/remove_device"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::DEVICEMANAGER_REMOVE_DEVICE) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleremove_device());
    }));
}

String DeviceManagerApis::getClassPath()
{
    return String(class_path.c_str());
}



String DeviceManagerApis::handleadd_device(String app_ssid, String app_password, String ip, String device_name, String server_name, String server_chip_id) {
    return "";
}
String DeviceManagerApis::handleremove_device() {
    return "";
}

String DeviceManagerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleadd_device") {
        handleadd_device(parameters["app_ssid"], parameters["app_password"], parameters["ip"], parameters["device_name"], parameters["server_name"], parameters["server_chip_id"]);
        return "OK";
    }
    if (functionName == "handleremove_device") {
        handleremove_device();
        return "OK";
    }
    return "";
}

#endif //DeviceManagerApis_h
