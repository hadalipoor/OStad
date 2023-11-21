#ifndef Network_H
#define Network_H

#define ASYNC_TCP_SSL_ENABLED 1

#include "INetwork.h"
#include "IPAddress.h"
#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#else
#include <HTTPClient.h>
#endif
#include "../Context.h"
// #include "MeshNetwork/MeshNetworkManager.h"
#include "WiFi/WiFiManager.h"

#include "apis/System/AddSystemApis.h"
#include "apis/Modules/AddModulesApis.h"
#include "apis/Authorization/AuthorizationApis.h"

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

struct ServerTaskParams {
    HTTPSServer* httpsServer;
    HTTPServer* httpServer;
    bool https_enabled;
    // Add other members as needed
};

class Network : public INetwork {
private:
    // AsyncWebServer server;
    HTTPServer* httpServer;
    HTTPSServer* httpsServer;
    // HTTPClient http;
    Context* context;
    Receive receive;
    SSLCert cert;

    void configureWebServer();
    void rebootESP(String message);
    // MeshNetworkManager* meshManager;
    WiFiManager* wiFiManager;
    CertificateData _certificateData;
    static void serverTask(ServerTaskParams* params);
    static void serverTaskWrapper(void *params);

public:
    Network(Context* context);
    Network(Context* context, CertificateData certificateDate);
    void initialize() override;
    void addApi(ResourceNode* api) override;
    void addUrlNotFound(ResourceNode* api) override;
    void addApis(std::vector<ApiInterface*> apis) override;
    void update() override;
    // IMeshNetworkManager* getMeshManager() override;
    IWiFiManager* getWiFiManager() override;
    HTTPServer& getHTTPServer() override;
    HTTPSServer& getHTTPSServer() override;

    Receive* getReceive() override;
    void begin();
};

Network::Network(Context* cntxt) : context(cntxt)
{

}

Network::Network(Context* ctxt, CertificateData certificateData): context(ctxt), _certificateData(certificateData)
{

}

void Network::rebootESP(String message) {
    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::SYSTEM_REBOOT, String("Rebooting ESP: " + message));
    ESP.restart();
}

HTTPServer& Network::getHTTPServer()
{
  return *httpServer;
}

HTTPSServer& Network::getHTTPSServer()
{
  return *httpsServer;
}

Receive* Network::getReceive()
{
  return &receive;
}

void Network::configureWebServer() {
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Configuring Web Server ...");
    
    if (_https_enabled)
    {
      
      cert = SSLCert(
                      _certificateData.certificate, _certificateData.certificate_length,
                      _certificateData.privatekey, _certificateData.privateky_length
                    );

      // First, we create the HTTPSServer with the certificate created above
      httpsServer = new HTTPSServer(&cert);
      // Additionally, we create an HTTPServer for unencrypted traffic
    }
    httpServer = new HTTPServer();

    createSystemApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "System Apis Created.");    
    createAuthorizationApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Authorization Apis Created.");
    createModulesApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Module Apis Created.");
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Web Server Configured.");
}

void Network::addUrlNotFound(ResourceNode* api)
{
  httpServer->setDefaultNode(api);
  if (_https_enabled)
  {
    httpsServer->setDefaultNode(api);
  }
}

void Network::addApi(ResourceNode* api)
{
  httpServer->registerNode(api);
  if (_https_enabled)
  {
    httpsServer->registerNode(api);
  }
}

void Network::addApis(std::vector<ApiInterface*> apis)
{
  for (size_t i = 0; i < apis.size(); i++)
  {
    ApiInterface* api = apis.at(i);
    receive.registerClass(String(api->getClassPath().c_str()), api);
  } 
}

void Network::begin() {
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Starting Webserver ...");
  ServerTaskParams* params = new ServerTaskParams;
  params->httpsServer = httpsServer;
  params->httpServer = httpServer;
  params->https_enabled = _https_enabled;
  // Set other members as needed
  xTaskCreatePinnedToCore(serverTaskWrapper, "https443", 6144, params, 1, NULL, ARDUINO_RUNNING_CORE);
}

void Network::serverTaskWrapper(void *params) {
    
    ServerTaskParams* taskParams = static_cast<ServerTaskParams*>(params);
    Network::serverTask(taskParams);
}

void Network::serverTask(ServerTaskParams* params) {
    // Use params->httpsServer and params->httpServer here
    params->httpServer->start();
    if (params->https_enabled)
    {
      params->httpsServer->start();
    }
    

    if (params->httpServer->isRunning())
    {
      Serial.println("HTTP Server is ready.");
      if(params->https_enabled  && params->httpsServer->isRunning())
      {
        Serial.println("HTTPS Server is ready.");
      }

      // "loop()" function of the separate task
      while (true)
      {
        // This call will let the server do its work
        params->httpServer->loop();
        if (params->https_enabled)
        {
          params->httpsServer->loop();
        }

        // Other code would go here...
        delay(1);
      }
    }
    
}

void Network::initialize() {
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Initializing Network ...");

  // meshManager = new MeshNetworkManager(*context);

  wiFiManager = new WiFiManager(context);

  int stationCount = 0;

  // WiFi.mode(WIFI_MODE_AP);
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_AP) == "true")
  {
    wiFiManager->configureAccessPointMode();
    stationCount = stationCount + 1;
  }
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_WIFI) == "true")
  {
    if(stationCount > 1)
    {
      context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::SYSTEM_BOOT, "Mesh and AccesPoint are active and Wifi can not run. but it is true.");
      return;
    }
    else if(stationCount == 1)
    {
      // WiFi.mode(WIFI_MODE_STA);
    }
    else
    {
      // WiFi.mode(WIFI_MODE_STA);
    }
    wiFiManager->configureStationMode();
  }
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_MESH) == "true")
  {
    // meshManager->initialize();
    stationCount = stationCount + 1;
  }
  else
  {
    if (stationCount == 0)
    {
      wiFiManager->configureAccessPointMode();
    }    
  }
  wiFiManager->displayNetworkInfo();
  configureWebServer();

  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Network Initialized.");
}

void Network::update() {
  // meshManager->loop();  
    // syncDatabaseLoop();
}

// IMeshNetworkManager* Network::getMeshManager()
// {
//   return meshManager;
// }

IWiFiManager* Network::getWiFiManager()
{
  return wiFiManager;
}

#endif
