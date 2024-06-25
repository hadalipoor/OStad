#ifndef DEVICEPERMISSIONS_H
#define DEVICEPERMISSIONS_H

#include "../../../Context.h"

class DevicePermissions
{
public:
    static const String DEVICES_CREATE;
    static const String DEVICES_UPDATE;
    static const String DEVICES_DELETE;
    static const String DEVICES_GET;
    static const String DEVICEMANAGER_ADD_DEVICE;
    static const String DEVICEMANAGER_REQUEST_ADD_DEVICE;
    static const String DEVICEMANAGER_REMOVE_DEVICE;
    static const String RELAYMANAGER_ADD;
    static const String RELAYMANAGER_EDIT;
    static const String RELAYMANAGER_REMOVE_RELAY;
    static const String RELAYMANAGER_GET_ALL;
    static const String RELAYMANAGER_GET_BY_SERVER_ID;
    
    // New Permissions
    static const String BUTTONMANAGER_ADD;
    static const String BUTTONMANAGER_EDIT;
    static const String BUTTONMANAGER_REMOVE;
    static const String BUTTONMANAGER_GET_ALL;
    static const String BUTTONMANAGER_GET_BY_SERVER_ID;

    static const String DHTSENSORMANAGER_ADD;
    static const String DHTSENSORMANAGER_EDIT;
    static const String DHTSENSORMANAGER_REMOVE;
    static const String DHTSENSORMANAGER_GET_ALL;
    static const String DHTSENSORMANAGER_GET_BY_SERVER_ID;

    static const String LCDMANAGER_ADD;
    static const String LCDMANAGER_EDIT;
    static const String LCDMANAGER_REMOVE;
    static const String LCDMANAGER_GET_ALL;
    static const String LCDMANAGER_GET_BY_SERVER_ID;

    static const String SOILMOISTUREMANAGER_ADD;
    static const String SOILMOISTUREMANAGER_EDIT;
    static const String SOILMOISTUREMANAGER_REMOVE;
    static const String SOILMOISTUREMANAGER_GET_ALL;
    static const String SOILMOISTUREMANAGER_GET_BY_SERVER_ID;

    static const String PHOTORESISTORMANAGER_ADD;
    static const String PHOTORESISTORMANAGER_EDIT;
    static const String PHOTORESISTORMANAGER_REMOVE;
    static const String PHOTORESISTORMANAGER_GET_ALL;
    static const String PHOTORESISTORMANAGER_GET_BY_SERVER_ID;

    static const String RGBMANAGER_ADD;
    static const String RGBMANAGER_EDIT;
    static const String RGBMANAGER_REMOVE;
    static const String RGBMANAGER_GET_ALL;
    static const String RGBMANAGER_GET_BY_SERVER_ID;

    static const String RFIDMANAGER_ADD;
    static const String RFIDMANAGER_EDIT;
    static const String RFIDMANAGER_REMOVE;
    static const String RFIDMANAGER_GET_ALL;
    static const String RFIDMANAGER_GET_BY_SERVER_ID;

    static void addDevicePermissions(Context* context);
};

void DevicePermissions::addDevicePermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(DEVICES_CREATE, "DevicePermissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_UPDATE, "DevicePermissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_DELETE, "DevicePermissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_GET, "DevicePermissions");
    context->getSecurity()->addPermissionForAdmin(DEVICEMANAGER_ADD_DEVICE, "Permissions");
    context->getSecurity()->addPermissionForAdmin(DEVICEMANAGER_REQUEST_ADD_DEVICE, "Permissions");
    context->getSecurity()->addPermissionForAdmin(DEVICEMANAGER_REMOVE_DEVICE, "Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_ADD, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_EDIT, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_REMOVE_RELAY, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_GET_ALL, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_GET_BY_SERVER_ID, "DeviceTest Permissions");
    
    // New Permissions
    context->getSecurity()->addPermissionForAdmin(BUTTONMANAGER_ADD, "ButtonManager Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTONMANAGER_EDIT, "ButtonManager Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTONMANAGER_REMOVE, "ButtonManager Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTONMANAGER_GET_ALL, "ButtonManager Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTONMANAGER_GET_BY_SERVER_ID, "ButtonManager Permissions");

    context->getSecurity()->addPermissionForAdmin(DHTSENSORMANAGER_ADD, "DHTSensorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(DHTSENSORMANAGER_EDIT, "DHTSensorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(DHTSENSORMANAGER_REMOVE, "DHTSensorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(DHTSENSORMANAGER_GET_ALL, "DHTSensorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(DHTSENSORMANAGER_GET_BY_SERVER_ID, "DHTSensorManager Permissions");

    context->getSecurity()->addPermissionForAdmin(LCDMANAGER_ADD, "LCDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(LCDMANAGER_EDIT, "LCDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(LCDMANAGER_REMOVE, "LCDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(LCDMANAGER_GET_ALL, "LCDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(LCDMANAGER_GET_BY_SERVER_ID, "LCDManager Permissions");

    context->getSecurity()->addPermissionForAdmin(SOILMOISTUREMANAGER_ADD, "SoilMoistureManager Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTUREMANAGER_EDIT, "SoilMoistureManager Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTUREMANAGER_REMOVE, "SoilMoistureManager Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTUREMANAGER_GET_ALL, "SoilMoistureManager Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTUREMANAGER_GET_BY_SERVER_ID, "SoilMoistureManager Permissions");

    context->getSecurity()->addPermissionForAdmin(PHOTORESISTORMANAGER_ADD, "PhotoresistorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTORMANAGER_EDIT, "PhotoresistorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTORMANAGER_REMOVE, "PhotoresistorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTORMANAGER_GET_ALL, "PhotoresistorManager Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTORMANAGER_GET_BY_SERVER_ID, "PhotoresistorManager Permissions");

    context->getSecurity()->addPermissionForAdmin(RGBMANAGER_ADD, "RGBManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RGBMANAGER_EDIT, "RGBManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RGBMANAGER_REMOVE, "RGBManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RGBMANAGER_GET_ALL, "RGBManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RGBMANAGER_GET_BY_SERVER_ID, "RGBManager Permissions");

    context->getSecurity()->addPermissionForAdmin(RFIDMANAGER_ADD, "RFIDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RFIDMANAGER_EDIT, "RFIDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RFIDMANAGER_REMOVE, "RFIDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RFIDMANAGER_GET_ALL, "RFIDManager Permissions");
    context->getSecurity()->addPermissionForAdmin(RFIDMANAGER_GET_BY_SERVER_ID, "RFIDManager Permissions");
}

// Define constants
const String DevicePermissions::DEVICES_CREATE = "devices_create";
const String DevicePermissions::DEVICES_UPDATE = "devices_update";
const String DevicePermissions::DEVICES_DELETE = "devices_delete";
const String DevicePermissions::DEVICES_GET = "devices_get";
const String DevicePermissions::DEVICEMANAGER_ADD_DEVICE = "devicemanager_add_device";
const String DevicePermissions::DEVICEMANAGER_REQUEST_ADD_DEVICE = "devicemanager_request_add_device";
const String DevicePermissions::DEVICEMANAGER_REMOVE_DEVICE = "devicemanager_remove_device";
const String DevicePermissions::RELAYMANAGER_ADD = "relaymanager_add";
const String DevicePermissions::RELAYMANAGER_EDIT = "relaymanager_edit";
const String DevicePermissions::RELAYMANAGER_REMOVE_RELAY = "relaymanager_remove_relay";
const String DevicePermissions::RELAYMANAGER_GET_ALL = "relaymanager_get_all";
const String DevicePermissions::RELAYMANAGER_GET_BY_SERVER_ID = "relaymanager_get_by_server_id";

// Define new constants
const String DevicePermissions::BUTTONMANAGER_ADD = "buttonmanager_add";
const String DevicePermissions::BUTTONMANAGER_EDIT = "buttonmanager_edit";
const String DevicePermissions::BUTTONMANAGER_REMOVE = "buttonmanager_remove_button";
const String DevicePermissions::BUTTONMANAGER_GET_ALL = "buttonmanager_get_all";
const String DevicePermissions::BUTTONMANAGER_GET_BY_SERVER_ID = "buttonmanager_get_by_server_id";

const String DevicePermissions::DHTSENSORMANAGER_ADD = "dhtsensormanager_add";
const String DevicePermissions::DHTSENSORMANAGER_EDIT = "dhtsensormanager_edit";
const String DevicePermissions::DHTSENSORMANAGER_REMOVE = "dhtsensormanager_remove";
const String DevicePermissions::DHTSENSORMANAGER_GET_ALL = "dhtsensormanager_get_all";
const String DevicePermissions::DHTSENSORMANAGER_GET_BY_SERVER_ID = "dhtsensormanager_get_by_server_id";

const String DevicePermissions::LCDMANAGER_ADD = "lcdmanager_add";
const String DevicePermissions::LCDMANAGER_EDIT = "lcdmanager_edit";
const String DevicePermissions::LCDMANAGER_REMOVE = "lcdmanager_remove";
const String DevicePermissions::LCDMANAGER_GET_ALL = "lcdmanager_get_all";
const String DevicePermissions::LCDMANAGER_GET_BY_SERVER_ID = "lcdmanager_get_by_server_id";

const String DevicePermissions::SOILMOISTUREMANAGER_ADD = "soilmoisturemanager_add";
const String DevicePermissions::SOILMOISTUREMANAGER_EDIT = "soilmoisturemanager_edit";
const String DevicePermissions::SOILMOISTUREMANAGER_REMOVE = "soilmoisturemanager_remove";
const String DevicePermissions::SOILMOISTUREMANAGER_GET_ALL = "soilmoisturemanager_get_all";
const String DevicePermissions::SOILMOISTUREMANAGER_GET_BY_SERVER_ID = "soilmoisturemanager_get_by_server_id";

const String DevicePermissions::PHOTORESISTORMANAGER_ADD = "photoresistormanager_add";
const String DevicePermissions::PHOTORESISTORMANAGER_EDIT = "photoresistormanager_edit";
const String DevicePermissions::PHOTORESISTORMANAGER_REMOVE = "photoresistormanager_remove";
const String DevicePermissions::PHOTORESISTORMANAGER_GET_ALL = "photoresistormanager_get_all";
const String DevicePermissions::PHOTORESISTORMANAGER_GET_BY_SERVER_ID = "photoresistormanager_get_by_server_id";

const String DevicePermissions::RGBMANAGER_ADD = "rgbmanager_add";
const String DevicePermissions::RGBMANAGER_EDIT = "rgbmanager_edit";
const String DevicePermissions::RGBMANAGER_REMOVE = "rgbmanager_remove";
const String DevicePermissions::RGBMANAGER_GET_ALL = "rgbmanager_get_all";
const String DevicePermissions::RGBMANAGER_GET_BY_SERVER_ID = "rgbmanager_get_by_server_id";

const String DevicePermissions::RFIDMANAGER_ADD = "rfidmanager_add";
const String DevicePermissions::RFIDMANAGER_EDIT = "rfidmanager_edit";
const String DevicePermissions::RFIDMANAGER_REMOVE = "rfidmanager_remove";
const String DevicePermissions::RFIDMANAGER_GET_ALL = "rfidmanager_get_all";
const String DevicePermissions::RFIDMANAGER_GET_BY_SERVER_ID = "rfidmanager_get_by_server_id";

#endif // DEVICEPERMISSIONS_H
