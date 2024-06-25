#ifndef RFID125KH_H
#define RFID125KH_H

#include <Wiegand.h>
#include "../../Database/Entities/Modules/RFIDFullEntity.h"
#include "ModuleTypes.h"
#include "IRFID125Kh.h"
#include "../../Context.h"

class RFID125Kh: public IRFID125Kh
{
private:
    Context* context;
    RFIDCallback onNewTag;
    WIEGAND wg;
    int Pin0;
    int Pin1;
    String ip;
    String protocolType;

public:
    RFID125Kh(Context* context, int pin0, int pin1, int module_id, int server_id, String name, String moduleType, int device_id);
    void setOnNewTag(RFIDCallback function);
    RFIDFullEntity* getEntity();
    void update();

    int getPin0();
    int getPin1();

};

RFID125Kh::RFID125Kh(Context* context, int pin0, int pin1, int module_id, int server_id, String name, String moduleType, int device_id):
    IRFID125Kh(module_id, server_id, name, moduleType, device_id), Pin0(pin0), Pin1(pin1), context(context)
{
    if(device_id == context->getDeviceManager()->deviceId)
    {
        wg.begin(pin0, pin1);
    }
    else
    {
      protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
      ModulesController* modulesController = new ModulesController(context, storageType);
      RFIDFullEntity* rfidFullEntity = modulesController->getRFIDByServerId(getServerId());
      int deviceId = rfidFullEntity->DeviceId;
      DevicesController* devicesController = new DevicesController(context, storageType);
      DevicesEntity device = devicesController->GetById(deviceId);
      ip = device.getIP();
    }
}

void RFID125Kh::setOnNewTag(RFIDCallback function)
{
    onNewTag = function;
}

void RFID125Kh::update()
{
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        if(wg.available())
        {
            onNewTag(String(wg.getCode()));
        }
    }
}

int RFID125Kh::getPin0()
{
    return Pin0;
}

int RFID125Kh::getPin1()
{
    return Pin1;
}

RFIDFullEntity* RFID125Kh::getEntity()
{
    return new RFIDFullEntity(0, getModuleID(), getName(), getPin0(), getPin1(), getDeviceID(), getServerId());
}



#endif //RFID125KH_H