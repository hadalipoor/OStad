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
    static const String DARBOONTEMP2CONFIG_CREATE;
    static const String DARBOONTEMP2CONFIG_UPDATE;
    static const String DARBOONTEMP2CONFIG_DELETE;
    static const String DARBOONTEMP2CONFIG_GET;
    static const String TAGCONTROLLER_ADDGUEST;
    static const String TAGCONTROLLER_OPENDOOR;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(GUESTS_CREATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_UPDATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_DELETE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(GUESTS_GET, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_CREATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_UPDATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_DELETE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DOORLOG_GET, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DARBOONTEMP2CONFIG_CREATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DARBOONTEMP2CONFIG_UPDATE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DARBOONTEMP2CONFIG_DELETE, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(DARBOONTEMP2CONFIG_GET, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(TAGCONTROLLER_ADDGUEST, "DarboonTemp2 Permissions");
    context->getSecurity()->addPermissionForAdmin(TAGCONTROLLER_OPENDOOR, "DarboonTemp2 Permissions");

}

const String Permissions::GUESTS_CREATE = "guests_create";
const String Permissions::GUESTS_UPDATE = "guests_update";
const String Permissions::GUESTS_DELETE = "guests_delete";
const String Permissions::GUESTS_GET = "guests_get";
const String Permissions::DOORLOG_CREATE = "doorlog_create";
const String Permissions::DOORLOG_UPDATE = "doorlog_update";
const String Permissions::DOORLOG_DELETE = "doorlog_delete";
const String Permissions::DOORLOG_GET = "doorlog_get";
const String Permissions::DARBOONTEMP2CONFIG_CREATE = "darboontemp2config_create";
const String Permissions::DARBOONTEMP2CONFIG_UPDATE = "darboontemp2config_update";
const String Permissions::DARBOONTEMP2CONFIG_DELETE = "darboontemp2config_delete";
const String Permissions::DARBOONTEMP2CONFIG_GET = "darboontemp2config_get";
const String Permissions::TAGCONTROLLER_ADDGUEST = "tagcontroller_addguest";
const String Permissions::TAGCONTROLLER_OPENDOOR = "tagcontroller_opendoor";


#endif // PERMISSIONS_H
