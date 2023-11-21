#ifndef PrinterApis_h
#define PrinterApis_h


#include "../AppContext.h"
#include "../Database/Controllers/RecentActivitiesController.h"
#include "Permissions.h"

class PrinterApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/printer";

public:
    PrinterApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlegetPrinterStatus();
    String handlegetactiveWiFi();
    String handlegetFrimwareInfo();
    String handlegetRecentActivity(String count);
    String handlegetPrinterSettings();
    String handlesetPrinterSettings(String setting, String value);
    String handlegetPrinterInfo();
};

PrinterApis::PrinterApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/authentication_required"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETPRINTERSTATUS) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, context->systemContext->getConfig()->getSecurityConfig()->get(SecurityConfigKey::AUTHENTICATION_ENABLE));
    }));

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPrinterStatus"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETPRINTERSTATUS) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetPrinterStatus());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getactiveWiFi"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETACTIVEWIFI) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetactiveWiFi());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getFrimwareInfo"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETFRIMWAREINFO) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetFrimwareInfo());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getRecentActivity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETRECENTACTIVITY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("count")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String count = getQueryParameterString(req, "count");
        
        response(res, handlegetRecentActivity(count));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPrinterSettings"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETPRINTERSETTINGS) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetPrinterSettings());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setPrinterSettings"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_SETPRINTERSETTINGS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("setting") || !req->getParams()->isQueryParameterSet("value")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String setting = getQueryParameterString(req, "setting");
        String value = getQueryParameterString(req, "value");
        
        response(res, handlesetPrinterSettings(setting, value));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPrinterInfo"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PRINTER_GETPRINTERINFO) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetPrinterInfo());
    }));
}

String PrinterApis::getClassPath()
{
    return String(class_path.c_str());
}


String PrinterApis::handlegetPrinterStatus() {
    return context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_STATUS);
}
String PrinterApis::handlegetactiveWiFi() {
    return context->systemContext->getNetwork()->getWiFiManager()->getConnectedWifi();
    // return "";
}

String PrinterApis::handlegetFrimwareInfo() {
    // Create a JSON object
    DynamicJsonDocument doc(1024);
    
    // Add firmware update date to the JSON object
    doc["update_date"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_UPDATE_DATE);
    
    // Add firmware version to the JSON object
    doc["version"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_VERSION);
    
    // Convert JSON object to String and return
    String output;
    serializeJson(doc, output);
    return output;
}

String PrinterApis::handlegetRecentActivity(String count) {
    RecentActivitiesController* recentActivitiesController = new RecentActivitiesController(context, storageType);
    return recentActivitiesController->GetAllJson();
}

String PrinterApis::handlegetPrinterSettings() {
    // Create a JSON object
    DynamicJsonDocument doc(2048);
    
    // Add all the settings to the JSON object
    doc["active_template"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ACTIVE_TEMPLATE);
    doc["printer_status"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_STATUS);
    doc["printer_auto_on"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_AUTO_ON);
    doc["encoder_mode"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ENCODER_MODE);
    doc["printspeed"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTSPEED);
    doc["encoder_steps"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ENCODER_STEPS);
    doc["print_mirror"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINT_MIRROR);
    doc["ink_opacity"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::INK_OPACITY);
    doc["login_required"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_REQUIRED);
    doc["login_username"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_USERNAME);
    doc["login_password"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_PASSWORD);
    doc["total_print_count"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::TOTAL_PRINT_COUNT);
    doc["frimware_version"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_VERSION);
    doc["frimware_update_date"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_UPDATE_DATE);
    doc["printer_name"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_NAME);
    doc["printer_serial"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_SERIAL);
    doc["repeat_line_print"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::REPEAT_LINE_PRINT);
    doc["delay_after_printhead_enable"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_AFTE_PRINTHEAD_ENABLE);
    doc["delay_between_lines"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_LINES);
    doc["delay_between_left_right"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_LEFT_RIGHT);
    doc["delay_between_documents"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_DOCUMENTS);
    
    // Convert JSON object to String and return
    String output;
    serializeJson(doc, output);
    return output;
}

String PrinterApis::handlesetPrinterSettings(String setting, String value) {
    context->getInkjetPrinterConfig()->set(setting, value);
    return "Succesfull";
}
String PrinterApis::handlegetPrinterInfo() {
        // Create a JSON object
    DynamicJsonDocument doc(2048);
    
    // Add all the settings to the JSON object
    doc["active_template"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ACTIVE_TEMPLATE);
    doc["printer_status"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_STATUS);
    doc["printer_auto_on"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_AUTO_ON);
    doc["encoder_mode"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ENCODER_MODE);
    doc["printspeed"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTSPEED);
    doc["encoder_steps"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ENCODER_STEPS);
    doc["print_mirror"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINT_MIRROR);
    doc["ink_opacity"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::INK_OPACITY);
    doc["login_required"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_REQUIRED);
    doc["login_username"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_USERNAME);
    doc["login_password"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::LOGIN_PASSWORD);
    doc["total_print_count"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::TOTAL_PRINT_COUNT);
    doc["frimware_version"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_VERSION);
    doc["frimware_update_date"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::FRIMWARE_UPDATE_DATE);
    doc["printer_name"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_NAME);
    doc["printer_serial"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::PRINTER_SERIAL);
    doc["repeat_line_print"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::REPEAT_LINE_PRINT);
    doc["delay_after_printhead_enable"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_AFTE_PRINTHEAD_ENABLE);
    doc["delay_between_lines"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_LINES);
    doc["delay_between_left_right"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_LEFT_RIGHT);
    doc["delay_between_documents"] = context->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::DELAY_BETWEEN_DOCUMENTS);
    
    // Convert JSON object to String and return
    String output;
    serializeJson(doc, output);
    return output;
}

String PrinterApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlegetPrinterStatus") {
        handlegetPrinterStatus();
        return "OK";
    }
    if (functionName == "handlegetactiveWiFi") {
        handlegetactiveWiFi();
        return "OK";
    }
    if (functionName == "handlegetFrimwareInfo") {
        handlegetFrimwareInfo();
        return "OK";
    }
    if (functionName == "handlegetRecentActivity") {
        handlegetRecentActivity(parameters["count"]);
        return "OK";
    }
    if (functionName == "handlegetPrinterSettings") {
        handlegetPrinterSettings();
        return "OK";
    }
    if (functionName == "handlesetPrinterSettings") {
        handlesetPrinterSettings(parameters["setting"], parameters["value"]);
        return "OK";
    }
    if (functionName == "handlegetPrinterInfo") {
        handlegetPrinterInfo();
        return "OK";
    }
    return "";
}

#endif //PrinterApis_h
