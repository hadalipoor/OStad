
#ifndef ADDDEVICEAPIS_H
#define ADDDEVICEAPIS_H

#include "DevicePermissions.h"
#include "DeviceManagerApis.h"
#include "DevicesApis.h"
#include "RelayManagerApis.h"

void createDeviceApis(Context* context)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    DeviceManagerApis* deviceManagerapis = new DeviceManagerApis(context, true);
    apis.push_back(deviceManagerapis);        

    DevicesApis* devicesApis = new DevicesApis(context, true);
    apis.push_back(devicesApis);        

    RelayManagerApis* relayManagerApis = new RelayManagerApis(context, true);
    apis.push_back(relayManagerApis);        

    context->getNetwork()->addApis(apis);
}

#endif //ADDDEVICEAPIS_H
    