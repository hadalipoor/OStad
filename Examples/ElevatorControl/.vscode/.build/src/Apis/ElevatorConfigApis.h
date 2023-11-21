
#ifndef ElevatorConfigApis_h
#define ElevatorConfigApis_h


#include <EBPInterfaces.h>
#include "../Database/Controllers/ElevatorControlConfigController.h"
#include "../Config/DefaultElevatorControlConfigs.h"
#include "../AppContext.h"

class ElevatorConfigApis : public ApiInterface
{
private:
public:
    String class_path = "/elevatorsystemconfig";
    ElevatorControlConfigController* elevatorControlConfigController;
    AppContext* context;

    ElevatorConfigApis(AppContext* context);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    void handleCreate(String key, String value);
    void handleUpdate(int id, String key, String value);
    String handleUpdateConfigs(String configs);
    void handleSubmit(String key, String value);
    void handleDelete(int id);
    String handleGet(String query);
    String handleGetById(int id);
    String handleGetAll();
};

ElevatorConfigApis::ElevatorConfigApis(AppContext* cntxt): context(cntxt)
{
    initialize(context->systemContext->getNetwork()->getServer());

}

void ElevatorConfigApis::initialize(AsyncWebServer &server)
{    
    elevatorControlConfigController = new ElevatorControlConfigController(context, storageType);

    server.on(String(class_path + "/create").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
            if(request->params()>1)
    {
        String key = request->getParam("key")->value();
        String value = request->getParam("value")->value();
        this->handleCreate(key, value);
        request->send(200, "text/html", "Succesfull");
    }
    else
    {
        request->send(200, "text/html", "params not correct.");
    }
    });
    server.on(String(class_path + "/update").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
            if(request->params()>2)
    {
        int id = request->getParam("id")->value().toInt();
        String key = request->getParam("key")->value();
        String value = request->getParam("value")->value();
        this->handleUpdate(id, key, value);
        request->send(200, "text/html", "Succesfull");
    }
    else
    {
        request->send(200, "text/html", "params not correct.");
    }

    });
    
    server.on(String(class_path + "/update_configs").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
    if(request->params()>0)
    {
        String configs = request->getParam("configs")->value();
        Serial.println(configs);   

        request->send(200, "text/html", this->handleUpdateConfigs(configs));
    }
    else
    {
        request->send(200, "text/html", "params not correct.");
    }

    });
    server.on(String(class_path + "/submit").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
        if(request->params()>1)
        {
            String key = request->getParam("key")->value();
            String value = request->getParam("value")->value();
            
            this->handleSubmit(key, value);
            request->send(200, "text/html", "Succesfull");
        }
        else
        {
            request->send(200, "text/html", "params not correct.");
        }
    });
    server.on(String(class_path + "/reload").c_str(), HTTP_PUT, [=](AsyncWebServerRequest * request) {
            context->getElevatorControl()->initialize();
            request->send(200, "text/html", "Succesfull");
    });
    server.on(String(class_path + "/delete").c_str(), HTTP_DELETE, [=](AsyncWebServerRequest * request) {
        if(request->params()>0)
        {
            int id = request->getParam("id")->value().toInt();
            this->handleDelete(id);
            request->send(200, "text/html", "Succesfull");
        }
        else
        {
            request->send(200, "text/html", "params not correct.");
        }
    });
    server.on(String(class_path + "/get").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if(request->params()>0)
        {
            String query = request->getParam("query")->value();
            String result = this->handleGet(query);
            
            request->send(200, "text/html", result);
        }
    });

    server.on(String(class_path + "/getById").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        if(request->params()>0)
        {
            int id = request->getParam("id")->value().toInt();
            request->send(200, "text/html", this->handleGetById(id));
        }
        else
        {
            request->send(200, "text/html", "params not correct.");
        }
    });

    server.on(String(class_path + "/getAll").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        request->send(200, "text/html", this->handleGetAll());
    });

    server.on(String(class_path + "/getSystemConfigs").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        request->send(200, "text/html", DefaultElevatorControlConfigs::jsonString);
    });

    server.on(String(class_path + "/getConfigsJson").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        request->send(200, "text/html", DefaultElevatorControlConfigs::jsonString);
    });
}

String ElevatorConfigApis::getClassPath()
{
    return String(class_path.c_str());
}


String ElevatorConfigApis::callFunction(String functionName, std::map<String, String> parameters)
{
    if (functionName == "handleCreate") {
        handleCreate(parameters["key"], parameters["value"]);
        return "OK";
    } else if (functionName == "handleUpdate") {
        handleUpdate(parameters["id"].toInt(), parameters["key"], parameters["value"]);
        return "OK";
    } else if (functionName == "handleSubmit") {
        handleSubmit(parameters["key"], parameters["value"]);
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
void ElevatorConfigApis::handleCreate(String key, String value) {
        KeyValueEntity *elecatorSystemConfig = new KeyValueEntity(key, value);
        
        elevatorControlConfigController->Add(*elecatorSystemConfig);

}

String ElevatorConfigApis::handleUpdateConfigs(String configs)
{
    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, configs);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "Failed to parse jsonString";
    }

    // Check if "configs" key exists in the parsed JSON
    if (doc.containsKey("configs")) {
        JsonArray configArray = doc["configs"];

        // Iterate through each config in the JSON array
        for (size_t i = 0; i < configArray.size(); i++) {
            JsonObject config = configArray[i];
            
            // Extract id, key, and value
            int id = config["id"];
            String key = config["key"].as<String>();
            String value = config["value"].as<String>();

            // Call handleUpdate function
            handleSubmit(key, value);
        }
    } else {
        Serial.println(F("No 'configs' key found in JSON"));
        return "No 'configs' key found in JSON";
    }

    return "Configurations updated successfully";
}


void ElevatorConfigApis::handleUpdate(int id, String key, String value) {
        KeyValueEntity* entity = new KeyValueEntity(id, key, value);
        elevatorControlConfigController->Update(*entity);
}
void ElevatorConfigApis::handleSubmit(String key, String value) {
    std::vector<KeyValueEntity> elecatorSystemConfigEntities = elevatorControlConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
    if (elecatorSystemConfigEntities.size() > 0)
    {
        KeyValueEntity* entity = new KeyValueEntity(elecatorSystemConfigEntities.at(0).id, key, value);
        elevatorControlConfigController->Update(*entity);
    }
    else
    {
        KeyValueEntity *elecatorSystemConfig = new KeyValueEntity(key, value);
        elevatorControlConfigController->Add(*elecatorSystemConfig);
    }
}

void ElevatorConfigApis::handleDelete(int id) {
    elevatorControlConfigController->Delete(id);
}

String ElevatorConfigApis::handleGetAll() {
    return elevatorControlConfigController->GetAllJson();
}

String ElevatorConfigApis::handleGet(String query) {
    std::vector<KeyValueEntity> elecatorSystemConfigEntities = elevatorControlConfigController->Get(query);
    String result = "[";
    for (size_t i = 0; i < elecatorSystemConfigEntities.size(); i++)
    {
        result = result + elecatorSystemConfigEntities.at(i).toString();
    }
    result = result + "]";
    return result;
}

String ElevatorConfigApis::handleGetById(int id) {
    KeyValueEntity elecatorSystemConfig = elevatorControlConfigController->GetById(id);

    if (elecatorSystemConfig.id == -1)
    {
        return "no entity";
    }
    else
    {
        return elecatorSystemConfig.toJson();
    }
}


#endif
