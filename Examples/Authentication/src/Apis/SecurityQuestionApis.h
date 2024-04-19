#ifndef SECURITYQUESTIONAPIS_h
#define SECURITYQUESTIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/SecurityQuestionController.h"
#include "Permissions.h"

class SecurityQuestionApis : public ApiInterface
{
private:
    AppContext* context;
    SecurityQuestionController* securityquestionController;
    std::string class_path = "/securityquestion";

public:
    SecurityQuestionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int UserId, String SecurityQuestionTitleId, String Answer);
    String handleupdate(int id, int UserId, String SecurityQuestionTitleId, String Answer);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SecurityQuestionApis::SecurityQuestionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    securityquestionController = new SecurityQuestionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("SecurityQuestionTitleId") || !req->getParams()->isQueryParameterSet("Answer"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int UserId = getQueryParameterint(req, "UserId");
    String SecurityQuestionTitleId = getQueryParameterString(req, "SecurityQuestionTitleId");
    String Answer = getQueryParameterString(req, "Answer");

        response(res, handlecreate(UserId, SecurityQuestionTitleId, Answer));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("UserId") || !req->getParams()->isQueryParameterSet("SecurityQuestionTitleId") || !req->getParams()->isQueryParameterSet("Answer"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int UserId = getQueryParameterint(req, "UserId");
    String SecurityQuestionTitleId = getQueryParameterString(req, "SecurityQuestionTitleId");
    String Answer = getQueryParameterString(req, "Answer");
        
        response(res, handleupdate(id, UserId, SecurityQuestionTitleId, Answer));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SecurityQuestionApis::getClassPath()
{
    return String(class_path.c_str());
}

String SecurityQuestionApis::handlecreate(int UserId, String SecurityQuestionTitleId, String Answer) {
    SecurityQuestionEntity* securityquestionEntity = new SecurityQuestionEntity(UserId, SecurityQuestionTitleId, Answer);
    int id = securityquestionController->Add(*securityquestionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SecurityQuestionApis::handleupdate(int id, int UserId, String SecurityQuestionTitleId, String Answer) {
    SecurityQuestionEntity* securityquestionEntity = new SecurityQuestionEntity(id, UserId, SecurityQuestionTitleId, Answer);
    
    if (securityquestionController->Update(*securityquestionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SecurityQuestionApis::handledelete(int id) {
    
    if (securityquestionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SecurityQuestionApis::handlegetAll() {
    return securityquestionController->GetAllJson();
}
String SecurityQuestionApis::handlegetById(int id) {
    return securityquestionController->GetById(id).toJson();
}
String SecurityQuestionApis::handleget(String query) {
    return securityquestionController->GetJson(query);
}

String SecurityQuestionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["UserId"].toInt(), parameters["SecurityQuestionTitleId"], parameters["Answer"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["UserId"].toInt(), parameters["SecurityQuestionTitleId"], parameters["Answer"]);
    }
    if (functionName == "delete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "getAll") {
        return handlegetAll();
    }
    if (functionName == "getById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "get") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //SECURITYQUESTIONApis_h

    