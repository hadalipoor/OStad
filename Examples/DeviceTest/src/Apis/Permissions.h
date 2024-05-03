#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String DEVICES_CREATE;
    static const String DEVICES_UPDATE;
    static const String DEVICES_DELETE;
    static const String DEVICES_GET;
    static const String RELAYMANAGER_ADD;
    static const String RELAYMANAGER_EDIT;
    static const String RELAYMANAGER_REMOVE_RELAY;
    static const String RELAYMANAGER_GET_ALL;
    static const String RELAYMANAGER_GET_BY_SERVER_ID;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(DEVICES_CREATE, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_UPDATE, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_DELETE, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(DEVICES_GET, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_ADD, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_EDIT, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_REMOVE_RELAY, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_GET_ALL, "DeviceTest Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAYMANAGER_GET_BY_SERVER_ID, "DeviceTest Permissions");

}

const String Permissions::DEVICES_CREATE = "devices_create";
const String Permissions::DEVICES_UPDATE = "devices_update";
const String Permissions::DEVICES_DELETE = "devices_delete";
const String Permissions::DEVICES_GET = "devices_get";
const String Permissions::RELAYMANAGER_ADD = "relaymanager_add";
const String Permissions::RELAYMANAGER_EDIT = "relaymanager_edit";
const String Permissions::RELAYMANAGER_REMOVE_RELAY = "relaymanager_remove_relay";
const String Permissions::RELAYMANAGER_GET_ALL = "relaymanager_get_all";
const String Permissions::RELAYMANAGER_GET_BY_SERVER_ID = "relaymanager_get_by_server_id";


#endif // PERMISSIONS_H
