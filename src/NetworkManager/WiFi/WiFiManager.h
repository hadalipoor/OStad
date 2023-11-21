#ifndef WiFiManager_h
#define WiFiManager_h


#include "../../context.h"
#include "../../Config/System/SystemConfigKeys.h"
#include "../../Database/Controllers/WiFiConroller.h"
#include "IWiFiManager.h"

class WiFiManager : public IWiFiManager
{
private:
    uint8_t BUILTIN_LED_PIN = 2;
    const String WIFI_FILE = "/WiFi.db";
    String DEFAULT_AP = "OStad";
    String DEFAULT_PASSWORD = "12345678";
    void blinkLED(int times, int delayMs);

public:
    WiFiManager(Context*context);
    void WiFiConnect() override;
    void AddSSID(String SSID, String password) override;
    void RemoveSSID(String SSID) override;
    void GetAvailableSSIDs(std::vector<SSIDInfo> &SSIDInfos) override;
    void loop() override;
    void configWifiMode() override;
    void displayNetworkInfo() override;
    void configureAccessPointMode() override;
    void configureStationMode() override;
    void connectToAvailableNetwork(std::vector<WiFiEntity>& wifiEntities) override;
    void connectToNetwork(WiFiEntity& wifiEntity) override;
    void waitForConnection() override;
    String getConnectedWifi() override;

    const int default_WebServerPortHttp = 80;
    Context* context;
};

WiFiManager::WiFiManager(Context*cntxt)
{
  context = cntxt;
  pinMode(BUILTIN_LED_PIN, OUTPUT);
}

void WiFiManager::loop()
{

}

void WiFiManager::WiFiConnect() 
{
  configWifiMode();
  displayNetworkInfo();
}

void WiFiManager::configWifiMode()
{

}

void WiFiManager::configureAccessPointMode()
{
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Initializing Accespoint ...");
  
  // WiFi.mode(WIFI_STA);
  WiFi.softAP(context->getConfig()->getSystemConfig()->get(SystemConfigKey::AP_SSID).c_str(),
              context->getConfig()->getSystemConfig()->get(SystemConfigKey::AP_PASSWORD).c_str(), 
              context->getConfig()->getSystemConfig()->get(SystemConfigKey::CHANNEL).toInt(), 
              context->getConfig()->getSystemConfig()->get(SystemConfigKey::SSID_HIDDEN).toInt(), 
              context->getConfig()->getSystemConfig()->get(SystemConfigKey::MAX_CONNECTION).toInt());
    
  
  char buffer[256]; // Allocate a buffer large enough to hold the formatted string
  snprintf(buffer, sizeof(buffer), "\n\nAccess Point Information :\n      AP SSID: \"%s\"\n      AP IP: \"%s\"\n", WiFi.softAPSSID().c_str(), WiFi.softAPIP().toString().c_str());

  context->getLogger()->SerialPrint(buffer);
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Accespoint Initialized.");

}

void WiFiManager::configureStationMode()
{
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Initializing WiFi ...");

  WiFiController* wiFiController = new WiFiController(context, storageType);
  std::vector<WiFiEntity> wifiEntities = wiFiController->GetAll();
  if (wifiEntities.size() > 0)
  {
    connectToAvailableNetwork(wifiEntities);
  }
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "WiFi Initialized.");

}

void WiFiManager::connectToAvailableNetwork(std::vector<WiFiEntity>& wifiEntities)
{
  int n = WiFi.scanNetworks();
  if (n == 0) 
  {
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "No Networks Found to Connect");
  } 
  else 
  {
    for (int i = 0; i < n; ++i) 
    {
      for (size_t j = 0; j < wifiEntities.size(); j++)
      {
        if(WiFi.SSID(i) == wifiEntities.at(j).getSSID())
        {
          connectToNetwork(wifiEntities.at(j));
          return;
        }
      }
    }
        context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "No Netowrk found in List.");
  } 
}

void WiFiManager::connectToNetwork(WiFiEntity& wifiEntity)
{
  SSIDInfo ssidInfo;
  ssidInfo.SSID = wifiEntity.getSSID();
  ssidInfo.WiFiPassword = wifiEntity.getPassword();
  ssidInfo.WebServerPortHttp = default_WebServerPortHttp;

  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, String("\nConnecting to Wifi " + ssidInfo.SSID));
  
  WiFi.begin(ssidInfo.SSID.c_str(), ssidInfo.WiFiPassword.c_str());
  
  waitForConnection();
  
  WiFi.setSleep(false);
  
  char buffer[256]; // Ensure this buffer is large enough for your message

snprintf(buffer, sizeof(buffer), 
    "\n\nNetwork SSID Information:\n"
    "         SSID: %s\n"
    "Wifi Strength: %ld dBm",
    WiFi.SSID().c_str(),  // Convert the SSID to a C-style string
    WiFi.RSSI());         // RSSI is already a long, so no conversion needed

  context->getLogger()->SerialPrint(buffer);
  blinkLED(10, 100);
  digitalWrite(BUILTIN_LED_PIN, LOW);
}

void WiFiManager::waitForConnection()
{
  int start_millis = millis();
  bool led_on = false;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(400);
    // digitalWrite(BUILTIN_LED_PIN, led_on ? HIGH : LOW);
    led_on = !led_on;

    if (millis() - start_millis > 120000)
    {
      context->getConfig()->getSystemConfig()->set(SystemConfigKey::WIFI_MODE_AP, "true");
      context->getConfig()->getSystemConfig()->set(SystemConfigKey::WIFI_MODE_WIFI, "false");
      #if defined(ESP32)
      ESP.restart();
      #endif
    }
  }
}

void WiFiManager::blinkLED(int times, int delayMs)
{
  bool led_on = false;
  for(int i = 0; i < times; i++)
  {
    digitalWrite(BUILTIN_LED_PIN, led_on ? HIGH : LOW);
    led_on = !led_on;
    delay(delayMs);
  }
}

void WiFiManager::displayNetworkInfo()
{
char buffer[512]; // Ensure this buffer is large enough for your message

snprintf(buffer, sizeof(buffer), 
    " Wifi Status: %d\n"
    " MAC: %s\n"
    " IP: %s\n"
    " Subnet: %s\n"
    " Gateway: %s\n"
    " DNS 1: %s\n"
    " DNS 2: %s\n"
    " DNS 3: %s\n"
    "\nConfiguring Webserver ...\n",
    WiFi.status(),
    WiFi.macAddress().c_str(),
    WiFi.localIP().toString().c_str(),
    WiFi.subnetMask().toString().c_str(),
    WiFi.gatewayIP().toString().c_str(),
    WiFi.dnsIP(0).toString().c_str(),
    WiFi.dnsIP(1).toString().c_str(),
    WiFi.dnsIP(2).toString().c_str());

    context->getLogger()->SerialPrint(buffer);
}

void WiFiManager::AddSSID(String SSID, String password)
{
  WiFiController* wiFiController = new WiFiController(context, storageType);
  WiFiEntity* wifiEntity = new WiFiEntity(SSID, password);
  wiFiController->Add(*wifiEntity);
}

void WiFiManager::RemoveSSID(String SSID)
{
  WiFiController* wiFiController = new WiFiController(context, storageType);
  std::vector<WiFiEntity> wifiEntities = wiFiController->Get(WiFiEntity::COLUMN_SSID + " = " + SSID);
  if (wifiEntities.size() > 0)
  {
    WiFiEntity wifiEntity = wifiEntities.at(0);
    wiFiController->Delete(wifiEntity.id);
  }
  
}

void WiFiManager::GetAvailableSSIDs(std::vector<SSIDInfo> &SSIDInfos)
{
  int n = WiFi.scanNetworks();
  WiFiController* wiFiController = new WiFiController(context, storageType);
  std::vector<WiFiEntity> wifiEntities = wiFiController->GetAll();
  if (n == 0) 
  {
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "No Networks Found to Connect");
  } 
  else 
  {
    for (int i = 0; i < n; ++i) 
    {
      SSIDInfo SSIDInfo;
      SSIDInfo.SSID = WiFi.SSID(i);
      SSIDInfo.WiFiStrength = WiFi.RSSI(i);
      SSIDInfo.isSaved = false;

      for (size_t j = 0; j < wifiEntities.size(); j++)
      {
        if(WiFi.SSID(i) == wifiEntities.at(j).getSSID())
        {
          SSIDInfo.isSaved = true;
        }
      }        
      SSIDInfos.push_back(SSIDInfo); 
    }
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "No Netowrk found in List.");
  }
}

String WiFiManager::getConnectedWifi()
{
  return WiFi.SSID();
}
#endif