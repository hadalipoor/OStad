#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String GUESTS_CREATE;
    static const String GUESTS_UPDATE;
    static const String GUESTS_DELETE;
    static const String GUESTS_GET;
    static const String DOORLOG_CREATE;
    static const String DOORLOG_UPDATE;
    static const String DOORLOG_DELETE;
    static const String DOORLOG_GET;
    static const String TAGCONTROLLER_ADDGUEST;
    static const String TAGCONTROLLER_OPENDOOR;
    static const String LIGHT_SWITCH_GARDEN_LIGHTS;
    static const String LIGHT_SWITCH_GAZEBO_LIGHTS;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(GUESTS_CREATE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_UPDATE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_DELETE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_GET, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_CREATE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_UPDATE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_DELETE, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_GET, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(TAGCONTROLLER_ADDGUEST, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(TAGCONTROLLER_OPENDOOR, "Darboon Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHT_SWITCH_GARDEN_LIGHTS, "SabooraHub2 Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHT_SWITCH_GAZEBO_LIGHTS, "SabooraHub2 Permissions");

}

const String Permissions::GUESTS_CREATE = "guests_create";
const String Permissions::GUESTS_UPDATE = "guests_update";
const String Permissions::GUESTS_DELETE = "guests_delete";
const String Permissions::GUESTS_GET = "guests_get";
const String Permissions::DOORLOG_CREATE = "doorlog_create";
const String Permissions::DOORLOG_UPDATE = "doorlog_update";
const String Permissions::DOORLOG_DELETE = "doorlog_delete";
const String Permissions::DOORLOG_GET = "doorlog_get";
const String Permissions::TAGCONTROLLER_ADDGUEST = "tagcontroller_addguest";
const String Permissions::TAGCONTROLLER_OPENDOOR = "tagcontroller_opendoor";
const String Permissions::LIGHT_SWITCH_GARDEN_LIGHTS = "light_switch_garden_lights";
const String Permissions::LIGHT_SWITCH_GAZEBO_LIGHTS = "light_switch_gazebo_lights";


#endif // PERMISSIONS_H
