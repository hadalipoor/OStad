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

}

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


#endif // PERMISSIONS_H
