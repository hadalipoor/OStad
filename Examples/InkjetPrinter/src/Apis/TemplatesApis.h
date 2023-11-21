
#ifndef TemplatesApis_h
#define TemplatesApis_h


#include "../AppContext.h"
#include "Permissions.h"
class TemplatesApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/templates";

public:
    TemplatesApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlegetActiveTemplate();
    String handlegetAllTemplates();
    String handlegetTemplateSettings(String id);
    String handlesetTemplateSettings(String delay_before_print, String quantity, String quantity_delay, String name, String repeat_template);
    String handleexportTemplate(String id);
    String handleimportTemplate();
    String handlesetActiveTemplate(String id);
    String handlesaveTemplate(String id, String data);
    String handlepreviewTemplate(String id);
    String handleloadTemplate(String id);
};

TemplatesApis::TemplatesApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getActiveTemplate"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_GETACTIVETEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetActiveTemplate());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAllTemplates"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_GETALLTEMPLATES) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetAllTemplates());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getTemplateSettings"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_GETTEMPLATESETTINGS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        
        response(res, handlegetTemplateSettings(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setTemplateSettings"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_SETTEMPLATESETTINGS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("delay_before_print") || !req->getParams()->isQueryParameterSet("quantity") || !req->getParams()->isQueryParameterSet("quantity_delay") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("repeat_template")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String delay_before_print = getQueryParameterString(req, "delay_before_print");
        String quantity = getQueryParameterString(req, "quantity");
        String quantity_delay = getQueryParameterString(req, "quantity_delay");
        String name = getQueryParameterString(req, "name");
        String repeat_template = getQueryParameterString(req, "repeat_template");
        
        response(res, handlesetTemplateSettings(delay_before_print, quantity, quantity_delay, name, repeat_template));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/exportTemplate"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_EXPORTTEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        
        response(res, handleexportTemplate(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/importTemplate"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_IMPORTTEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleimportTemplate());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setActiveTemplate"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_SETACTIVETEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        
        response(res, handlesetActiveTemplate(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/saveTemplate"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_SAVETEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("data")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        String data = getQueryParameterString(req, "data");
        
        response(res, handlesaveTemplate(id, data));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/previewTemplate"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_PREVIEWTEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        
        response(res, handlepreviewTemplate(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/loadTemplate"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPLATES_LOADTEMPLATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String id = getQueryParameterString(req, "id");
        
        response(res, handleloadTemplate(id));
    }));
}

String TemplatesApis::getClassPath()
{
    return String(class_path.c_str());
}



String TemplatesApis::handlegetActiveTemplate() {
    return "";
}
String TemplatesApis::handlegetAllTemplates() {
    return "";
}
String TemplatesApis::handlegetTemplateSettings(String id) {
    return "";
}
String TemplatesApis::handlesetTemplateSettings(String delay_before_print, String quantity, String quantity_delay, String name, String repeat_template) {
    return "";
}
String TemplatesApis::handleexportTemplate(String id) {
    return "";
}
String TemplatesApis::handleimportTemplate() {
    return "";
}
String TemplatesApis::handlesetActiveTemplate(String id) {
    return "";
}
String TemplatesApis::handlesaveTemplate(String id, String data) {
    return "";
}
String TemplatesApis::handlepreviewTemplate(String id) {
    return "";
}
String TemplatesApis::handleloadTemplate(String id) {
    return "";
}

String TemplatesApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlegetActiveTemplate") {
        handlegetActiveTemplate();
        return "OK";
    }
    if (functionName == "handlegetAllTemplates") {
        handlegetAllTemplates();
        return "OK";
    }
    if (functionName == "handlegetTemplateSettings") {
        handlegetTemplateSettings(parameters["id"]);
        return "OK";
    }
    if (functionName == "handlesetTemplateSettings") {
        handlesetTemplateSettings(parameters["delay_before_print"], parameters["quantity"], parameters["quantity_delay"], parameters["name"], parameters["repeat_template"]);
        return "OK";
    }
    if (functionName == "handleexportTemplate") {
        handleexportTemplate(parameters["id"]);
        return "OK";
    }
    if (functionName == "handleimportTemplate") {
        handleimportTemplate();
        return "OK";
    }
    if (functionName == "handlesetActiveTemplate") {
        handlesetActiveTemplate(parameters["id"]);
        return "OK";
    }
    if (functionName == "handlesaveTemplate") {
        handlesaveTemplate(parameters["id"], parameters["data"]);
        return "OK";
    }
    if (functionName == "handlepreviewTemplate") {
        handlepreviewTemplate(parameters["id"]);
        return "OK";
    }
    if (functionName == "handleloadTemplate") {
        handleloadTemplate(parameters["id"]);
        return "OK";
    }
    return "";
}

#endif //TemplatesApis_h
