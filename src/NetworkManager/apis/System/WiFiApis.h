#ifndef WiFiApis_h
#define WiFiApis_h

#include "../ApiInterface.h"
#include "../../../Context.h"
#include "../../../Database/Controllers/WiFiConroller.h"
#include "SystemPermissions.h"

class WiFiApis : public ApiInterface{
private:
    String ssidInfosToJson(const std::vector<SSIDInfo>& SSIDInfos);
public:
    std::string class_path = "/wifi";

    Context* context;

    WiFiApis(Context* cntxt, bool add_apis);
    String getClassPath() override;
    String callFunction(String functionName, std::map<String, String> parameters) override;

    bool removeSSID(String ssid);
    void restartESP();
    void disconnectWiFi();
    bool connectWiFi(String ssid, String password);
    void addSSID(String ssid, String password);
    String getAllSSIDs();
};

WiFiApis::WiFiApis(Context* cntxt, bool add_apis): context(cntxt)
{
    if (!add_apis) return;

    // forget_wifi API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/forget_wifi"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        if(req->getParams()->isQueryParameterSet("ssid")) {
            String ssid = getQueryParameterString(req, "ssid");
            removeSSID(ssid);
            response(res, 200, "text/html", "Successful");
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    // restart API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/restart"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        restartESP();
        response(res, 200, "text/html", "Successful");
    }));

    // disconnect_wifi API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/disconnect_wifi"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        disconnectWiFi();
        response(res, 200, "text/html", "Successful");
    }));

    // connect_wifi API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/connect_wifi"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        if(req->getParams()->isQueryParameterSet("ssid")) {
            String ssid = getQueryParameterString(req, "ssid");
            String password = "";
            if(req->getParams()->isQueryParameterSet("password")){
                password = getQueryParameterString(req, "password");
            }
            response(res, 200, "text/html", "Successful");
            if (connectWiFi(ssid, password)) {
                return;
            } else {
                response(res, 400, "text/html",  "Failed");
            }
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    // add_ssid API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/add_ssid"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        if(req->getParams()->isQueryParameterSet("ssid") && req->getParams()->isQueryParameterSet("password")) {
            String ssid = getQueryParameterString(req, "ssid");
            String password = getQueryParameterString(req, "password");
            addSSID(ssid, password);
            response(res, 200, "text/html", "Successful");
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    // get_all_ssids API
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_all_ssids"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL) { return; }
        String output = getAllSSIDs();
        response(res, 200, "text/json", output);
    }));
}


String WiFiApis::getClassPath()
{
    return String(class_path.c_str());
}

String WiFiApis::callFunction(String functionName, std::map<String, String> parameters)
{
    if (functionName == "removeSSID") {
        bool result = removeSSID(parameters["ssid"]);
        return result ? "OK" : "Error";
    } else if (functionName == "restartESP") {
        restartESP();
        return "OK";
    } else if (functionName == "disconnectWiFi") {
        disconnectWiFi();
        return "OK";
    } else if (functionName == "connectWiFi") {
        bool result = connectWiFi(parameters["ssid"], parameters["password"]);
        return result ? "OK" : "Error";
    } else if (functionName == "addSSID") {
        addSSID(parameters["ssid"], parameters["password"]);
        return "OK";
    } else if (functionName == "getAllSSIDs") {
        return getAllSSIDs();
    } else {
        return "Error: The function doesn't exist";
    }
}

bool WiFiApis::removeSSID(String ssid)
{
    context->getNetwork()->getWiFiManager()->RemoveSSID(ssid);

    return true;
}

void WiFiApis::restartESP()
{
    ESP.restart();
}

void WiFiApis::disconnectWiFi()
{
    WiFi.disconnect(false,false);
}

bool WiFiApis::connectWiFi(String ssid, String password)
{
    WiFiController* wifiController = new WiFiController(context, storageType);
    std::vector<WiFiEntity> wifiEntities = wifiController->GetAll();
    bool in_db = false;
    for (size_t i = 0; i < wifiEntities.size(); i++)
    {
        if (wifiEntities.at(i).getSSID() == ssid)
        {
            password = wifiEntities.at(i).getPassword();
            in_db = true;
        }            
    }
    disconnectWiFi();
    WiFi.begin(ssid.c_str(),password.c_str());
    if(WiFi.status())
    {
        if(in_db == false)
        {
            context->getNetwork()->getWiFiManager()->AddSSID(ssid,password);
            context->getNetwork()->getWiFiManager()->displayNetworkInfo();
        }
    }
    else{
        return false;
    }
    return true;
}


void WiFiApis::addSSID(String ssid, String password)
{
    context->getNetwork()->getWiFiManager()->AddSSID(ssid, password);
}

String WiFiApis::getAllSSIDs()
{
    std::vector<SSIDInfo> SSIDInfos;
    context->getNetwork()->getWiFiManager()->GetAvailableSSIDs(SSIDInfos);
    return ssidInfosToJson(SSIDInfos);
}

String WiFiApis::ssidInfosToJson(const std::vector<SSIDInfo>& SSIDInfos) {
    String json = "[";
    for (size_t i = 0; i < SSIDInfos.size(); i++) {
        json += "{\"SSID\":\"" + SSIDInfos.at(i).SSID + "\",\"WiFiStrength\":" + String(SSIDInfos.at(i).WiFiStrength) + ",\"isSaved\":" + String(SSIDInfos.at(i).isSaved) + "}";
        if (i < SSIDInfos.size() - 1) {
            json += ",";
        }
    }
    json += "]";
    return json;
}
#endif
