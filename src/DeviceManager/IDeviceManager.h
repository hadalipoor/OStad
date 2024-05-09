
#ifndef IDEVICEMANAGER_H
#define IDEVICEMANAGER_H

#include <EBPInterfaces.h>
#include "IRelayManager.h"

class IDeviceManager
{
public:
    virtual ~IDeviceManager(){}

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual bool addDeviceToServer(String ap_ssid, String ap_password, String ip, String device_name, String server_name, String server_chip_id, String server_ip) = 0;
    virtual bool sendAddDeviceRequest(String ap_ssid, String ap_password, String device_name) = 0;
    virtual bool resetDevice() = 0;
    virtual IRelayManager* getRelayManager() = 0;
    int deviceId = 0;
    String chipId = "";
};

#endif
