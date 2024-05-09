
#ifndef DeviceManagerApis_h
#define DeviceManagerApis_h


#include "../../../Context.h"
#include "DevicePermissions.h"
#include "../../../Database/Controllers/Modules/DevicesController.h"
#include "../../../Config/Device/DeviceConfigKeys.h"
#include "../../../Config/System/SystemConfigKeys.h"
#include <ArduinoJson.h>

class DeviceManagerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/devicemanager";

public:
    DeviceManagerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleadd_device(String ap_ssid, String ap_password, String ip, String device_name, String server_name, String server_chip_id, String server_ip);
    String handlerequest_add_device(String ap_ssid, String ap_password, String device_name);
    String handleremove_device();
};

DeviceManagerApis::DeviceManagerApis(Context* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add_device"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::DEVICEMANAGER_ADD_DEVICE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("ap_ssid") || !req->getParams()->isQueryParameterSet("ap_password") || !req->getParams()->isQueryParameterSet("ip") || !req->getParams()->isQueryParameterSet("device_name") || !req->getParams()->isQueryParameterSet("server_name") || !req->getParams()->isQueryParameterSet("server_chip_id") || !req->getParams()->isQueryParameterSet("server_ip")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String ap_ssid = getQueryParameterString(req, "ap_ssid");
        String ap_password = getQueryParameterString(req, "ap_password");
        String ip = getQueryParameterString(req, "ip");
        if(context->getValidation()->networkValidator()->isValidIP(ip) == false)
        {
            response(res, 400, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
            return;
        }

        String device_name = getQueryParameterString(req, "device_name");
        String server_name = getQueryParameterString(req, "server_name");
        String server_chip_id = getQueryParameterString(req, "server_chip_id");
        String server_ip = getQueryParameterString(req, "server_ip");
        if(context->getValidation()->networkValidator()->isValidIP(server_ip) == false)
        {
            response(res, 400, WRONG_INPUT_PARAMS_FORMAT_MESSAGE);
            return;
        }
        
        response(res, handleadd_device(ap_ssid, ap_password, ip, device_name, server_name, server_chip_id, server_ip));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/request_add_device"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::DEVICEMANAGER_REQUEST_ADD_DEVICE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("ap_ssid") || !req->getParams()->isQueryParameterSet("ap_password") || !req->getParams()->isQueryParameterSet("device_name")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }

        
        String ap_ssid = getQueryParameterString(req, "ap_ssid");
        String ap_password = getQueryParameterString(req, "ap_password");
        String device_name = getQueryParameterString(req, "device_name");
        response(res, handlerequest_add_device(ap_ssid, ap_password, device_name));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/remove_device"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, DevicePermissions::DEVICEMANAGER_REMOVE_DEVICE) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleremove_device());
    }));
}

String DeviceManagerApis::getClassPath()
{
    return String(class_path.c_str());
}



String DeviceManagerApis::handleadd_device(String ap_ssid, String ap_password, String ip, String device_name, String server_name, String server_chip_id, String server_ip) {
    if(context->getDeviceManager()->addDeviceToServer(ap_ssid, ap_password, ip, device_name, server_name, server_chip_id, server_ip))
    {
        String chipidStr = String(context->getSystemMonitor()->getEfuseMac());
        String output = "{\"success\":\"true\",\"chip_id\":\"" + chipidStr + "\"}";
        return output;
    }
    return "{\"success\":\"false\",\"chip_id\":\"\"}";
}

String DeviceManagerApis::handleremove_device() {
    if (context->getDeviceManager()->resetDevice())
    {
        return "{\"success\":\"true\"}";
    }
    
    return "{\"success\":\"false\"}";
}

String DeviceManagerApis::handlerequest_add_device(String ap_ssid, String ap_password, String device_name)
{
    return String("{\"success\":\"" + context->getDeviceManager()->sendAddDeviceRequest(ap_ssid, ap_password, device_name)) + "\"}";
}

String DeviceManagerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleadd_device") {
        handleadd_device(parameters["ap_ssid"], parameters["ap_password"], parameters["ip"], parameters["device_name"], parameters["server_name"], parameters["server_chip_id"], parameters["server_ip"]);
        return "OK";
    }
    if (functionName == "handleremove_device") {
        handleremove_device();
        return "OK";
    }
    return "";
}

#endif //DeviceManagerApis_h
