#ifndef SSIDApis_h
#define SSIDApis_h


#include <ArduinoJson.h>
#include "../../../Context.h"
#include "../ApiInterface.h"
#include "../../../Database/Controllers/WiFiConroller.h"
#include "SystemPermissions.h"

class SSIDApis : public ApiInterface{
private:
public:
    std::string class_path = "/ssid";
    WiFiController* wifiController;
    Context* context;

    SSIDApis(Context* context, bool add_apis);
    String getClassPath() override;

  String callFunction(String functionName, std::map<String, String> parameters) override;
  String handleCreate(String ssid, String password);
  String handleUpdate(int id, String ssid, String password);
  String handleDelete(int id);
  String handleGet(String query);
  String handleGetById(int id);
  String handleGetAll();
};

SSIDApis::SSIDApis(Context* cntxt, bool add_apis): context(cntxt) {
  wifiController = new WiFiController(context, storageType);

  if (!add_apis) return;

  context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
      if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
      
      if (!req->getParams()->isQueryParameterSet("SSID") || !req->getParams()->isQueryParameterSet("Password"))
      {
          response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
          return;
      }
      
      std::string ssid;
      req->getParams()->getQueryParameter("SSID", ssid);
      std::string password;
      req->getParams()->getQueryParameter("Password", password);

      response(res, handleCreate(String(ssid.c_str()), String(password.c_str())));
  }));

  // Update Endpoint
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("SSID") || !req->getParams()->isQueryParameterSet("Password"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);
        std::string ssid;
        req->getParams()->getQueryParameter("SSID", ssid);
        std::string password;
        req->getParams()->getQueryParameter("Password", password);

        response(res, handleUpdate(String(id.c_str()).toInt(), String(ssid.c_str()), String(password.c_str())));
    }));

    // Delete Endpoint
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);

        response(res, handleDelete(String(id.c_str()).toInt()));
    }));

    // Get All Endpoint
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handleGetAll());
    }));

    // Get By ID Endpoint
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        req->getParams()->getQueryParameter("id", id);

        response(res, handleGetById(String(id.c_str()).toInt()));
    }));

    // Get Endpoint
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string query;
        req->getParams()->getQueryParameter("query", query);

        response(res, handleGet(String(query.c_str())));
    }));
}

String SSIDApis::getClassPath()
{
    return String(class_path.c_str());
}


String SSIDApis::callFunction(String functionName, std::map<String, String> parameters) {
  if (functionName == "handleCreate") {
      handleCreate(parameters["ssid"], parameters["password"]);
      return "OK";
  } else if (functionName == "handleUpdate") {
      handleUpdate(parameters["id"].toInt(), parameters["ssid"], parameters["password"]);
      return "OK";
  } else if (functionName == "handleDelete") {
      handleDelete(parameters["id"].toInt());
      return "OK";
  } else if (functionName == "handleGet") {
      return handleGet(parameters["query"]);
  } else if (functionName == "handleGetById") {
      return handleGetById(parameters["id"].toInt());
  } else if (functionName == "handleGetAll") {
      return handleGetAll();
  } else {
      return "Error: The function doesn't exist";
  }
}

String SSIDApis::handleCreate(String ssid, String password) {
    WiFiEntity *wifiEntity = new WiFiEntity(ssid, password);
    int id = wifiController->Add(*wifiEntity);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}

String SSIDApis::handleUpdate(int id, String ssid, String password) {
    WiFiEntity* wifiEntity = new WiFiEntity(id, ssid, password); 
    if(wifiController->Update(*wifiEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}

String SSIDApis::handleDelete(int id) {
    if(wifiController->Delete(id)) return DELETE_SUCCESFULL_MESSAGE;
    return DELETE_FAILED_MESSAGE;
}

String SSIDApis::handleGet(String query) {
    
    std::vector<WiFiEntity> wifiEntities = wifiController->Get(query);
    String result = "[";
    for (size_t i = 0; i < wifiEntities.size(); i++) {
        result = result + wifiEntities.at(i).toString();
    }
    result = result + "]";
    return result;
}

String SSIDApis::handleGetById(int id) {
    WiFiEntity wifiEntity = wifiController->GetById(id);
    if (wifiEntity.id == -1) {
        return "No entity";
    } else {
        return wifiEntity.toJson();
    }
}

String SSIDApis::handleGetAll() {
    return wifiController->GetAllJson();
}

#endif
