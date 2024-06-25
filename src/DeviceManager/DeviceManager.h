
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../Context.h"
#include "../Config/Device/DeviceConfigKeys.h"
#include "../Config/System/SystemConfigKeys.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "RelayManager.h"
#include "ButtonManager.h"
#include "DHTSensorManager.h"
#include "LCDManager.h"
#include "RFIDManager.h"
#include "SoilMoistureSensorManager.h"

class DevicesType{
public:
    static const String Server;
    static const String Client;
};
const String DevicesType::Server  = "Server";
const String DevicesType::Client  = "Client";


class DeviceManager : public IDeviceManager
{
private:
    Context* context;
    RelayManager* _relayManager;
    ButtonManager* _buttonManager;
    DHTSensorManager* _dhtSensorManager;
    LCDManager* _lcdManager;
    RFIDManager* _rfidManager;
    SoilMoistureSensorManager* _soileMoistureSensorManager;

    String getNewIP();
    
public:
    DeviceManager(Context* context);

    void initialize() override;
    void update() override;
    bool addDeviceToServer(String ap_ssid, String ap_password, String ip, String device_name, String server_name, String server_chip_id, String server_ip) override;
    bool sendAddDeviceRequest(String ap_ssid, String ap_password, String device_name) override;
    bool resetDevice() override;
    RelayManager* getRelayManager() override;
    ButtonManager* getButtonManager() override;
    DHTSensorManager* getDHTSensorManager() override;
    LCDManager* getLCDManager() override;
    RFIDManager* getRFIDManager() override;
    SoilMoistureSensorManager* getSoilMoistureSensorManager() override;
};

DeviceManager::DeviceManager(Context* context) : context(context) {

}

void DeviceManager::initialize()
{
    _relayManager = new RelayManager(context);

    chipId = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::CHIP_ID);
    if (chipId == "")
    {
        chipId = String(context->getSystemMonitor()->getEfuseMac());
        context->getConfig()->getDeviceConfig()->set(DeviceConfigKeys::CHIP_ID, chipId);
    }
    DevicesController* deviceController = new DevicesController(context, storageType);
    std::vector<DevicesEntity> devicesEntity = deviceController->Get(String(DevicesEntity::COLUMN_CHIPID + "=" + chipId));
    if (devicesEntity.size() == 0)
    {
        DevicesEntity* deviceEntity = new DevicesEntity("Server", chipId, "192.168.4.1", "OStad Server", "", "", "");
        deviceId = deviceController->Add(*deviceEntity);
    }
    else
    {
        deviceId = devicesEntity.at(0).id;
    }  
    
}

void DeviceManager::update()
{

}

bool DeviceManager::addDeviceToServer(String ap_ssid, String ap_password, String ip, String device_name, String server_name, String server_chip_id, String server_ip)
{
    resetDevice();
    DevicesController* deviceController = new DevicesController(context, storageType);
    std::vector<DevicesEntity> device_entities = deviceController->Get(DevicesEntity::COLUMN_CHIPID+"="+chipId);
    if (device_entities.size() > 0)
    {
        deviceController->Delete(device_entities.at(0).id);
    }
    //add new server device
    DevicesEntity serverDeviceEntity = DevicesEntity(DevicesType::Server, server_chip_id, server_ip, server_name, server_chip_id, ap_ssid, ap_password);
    deviceController->Add(serverDeviceEntity);

    DevicesEntity devicesEntity = DevicesEntity(DevicesType::Client, chipId, ip, device_name, server_chip_id, "", "");
    deviceId = deviceController->Add(devicesEntity);

    
    //edit network ip in config
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::DEFAULT_IP, ip);
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::DEFAULT_GATEWAY, server_ip);
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::DEFAULT_SUBNET, "255,255,255,0");
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::DEFAULT_PRIMARYDNS, server_ip);
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::DEFAULT_SECONDARYDNS, "0,0,0,0");
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::WIFI_MODE_WIFI, "true");

    context->getNetwork()->getWiFiManager()->AddSSID(ap_ssid, ap_password);
    

    return true;
}
bool DeviceManager::sendAddDeviceRequest(String ap_ssid, String ap_password, String device_name)
{
    String default_wifi_mode = context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_WIFI);
    context->getConfig()->getSystemConfig()->set(SystemConfigKey::WIFI_MODE_WIFI, "true");
    WiFiEntity wifiEntity = WiFiEntity(ap_ssid, ap_password);
    context->getNetwork()->getWiFiManager()->connectToNetwork(wifiEntity);
    if(context->getNetwork()->getWiFiManager()->getConnectedWifi() == ap_ssid)
    {
        String endpoint = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE) + "://192.168.4.1/devicemanager/add_device";

        String client_ip = "192.168.4.2";
        //TODO: check for new ip
        String postData = "?ap_ssid="+context->getNetwork()->getApiManager()->urlEncode(context->getConfig()->getSystemConfig()->get(SystemConfigKey::AP_SSID))+
                        "&ap_password="+context->getNetwork()->getApiManager()->urlEncode(context->getConfig()->getSystemConfig()->get(SystemConfigKey::AP_PASSWORD))+
                        "&ip="+ context->getNetwork()->getApiManager()->urlEncode(client_ip) +
                        "&device_name="+context->getNetwork()->getApiManager()->urlEncode(device_name)+
                        "&server_name="+context->getNetwork()->getApiManager()->urlEncode(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::DEVICE_NAME))+
                        "&server_chip_id="+context->getNetwork()->getApiManager()->urlEncode(context->getDeviceManager()->chipId)+
                        "&server_ip=192.168.4.1";

        String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint + postData, "");
        // Calculate the required capacity for the JSON document
        StaticJsonDocument<256> doc;

        // Parse the JSON string
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            return false;
        }

        // Extract the value of "success"
        String success = doc["success"];
        context->getConfig()->getSystemConfig()->set(SystemConfigKey::WIFI_MODE_WIFI, default_wifi_mode);
        WiFi.disconnect();
        if (success == "true")
        {
            String client_chip_id = doc["chip_id"].as<String>();
            DevicesController* devicesController = new DevicesController(context, storageType);
            if(devicesController->Get(DevicesEntity::COLUMN_CHIPID+String("="+client_chip_id)).size() == 0)
            {
                DevicesEntity devicesEntity = DevicesEntity(DevicesType::Client, client_chip_id, client_ip, device_name, context->getDeviceManager()->chipId, ap_ssid, ap_password);
                devicesController->Add(devicesEntity);
            }
        }
        
        return success == "true" ? true : false;
    }
    return false;
}

bool DeviceManager::resetDevice()
{
    DevicesController* deviceController = new DevicesController(context, storageType);
    
    // remove current servers
    std::vector<DevicesEntity> server_device_entities = deviceController->GetAll();
    for(auto& server_device: server_device_entities)
    {
        deviceController->Delete(server_device.id);
    }

    //add new server device
    DevicesEntity deviceEntity = DevicesEntity(DevicesType::Server, chipId, "192.168.4.1", "Ostad Server", "", "", "");
    deviceId = deviceController->Add(deviceEntity);
    
    return true;
}

RelayManager* DeviceManager::getRelayManager()
{
    return _relayManager;
}

ButtonManager* DeviceManager::getButtonManager()
{
    return _buttonManager;
}

DHTSensorManager* DeviceManager::getDHTSensorManager()
{
    return _dhtSensorManager;
}

LCDManager* DeviceManager::getLCDManager()
{
    return _lcdManager;
}

RFIDManager* DeviceManager::getRFIDManager()
{
    return _rfidManager;
}

SoilMoistureSensorManager* DeviceManager::getSoilMoistureSensorManager()
{
    return _soileMoistureSensorManager;
}

#endif
