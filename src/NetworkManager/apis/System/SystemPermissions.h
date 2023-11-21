#ifndef SYSTEMPERMISSIONS_H
#define SYSTEMPERMISSIONS_H

#include "../../../Context.h"

class SystemPermissions
{
public:
    // File permissions
    static const String FILE_CREATE;
    static const String FILE_UPDATE;
    static const String FILE_DELETE;
    static const String FILE_GET;

    // WiFi permissions
    static const String WIFI_CREATE;
    static const String WIFI_UPDATE;
    static const String WIFI_DELETE;
    static const String WIFI_GET;

    // Log permissions
    static const String LOG_CREATE;
    static const String LOG_UPDATE;
    static const String LOG_DELETE;
    static const String LOG_GET;

    // SystemConfig permissions
    static const String SYSTEMCONFIG_CREATE;
    static const String SYSTEMCONFIG_UPDATE;
    static const String SYSTEMCONFIG_DELETE;
    static const String SYSTEMCONFIG_GET;

    // SSID permissions
    static const String SSID_CREATE;
    static const String SSID_UPDATE;
    static const String SSID_DELETE;
    static const String SSID_GET;

    // Clock permissions
    static const String CLOCK_GET;
    static const String CLOCK_SET;


    static void addPermissions(Context* context);
};

void SystemPermissions::addPermissions(Context* context)
{
    // File permissions
    context->getSecurity()->addPermissionForAdmin(FILE_CREATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(FILE_UPDATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(FILE_DELETE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(FILE_GET, "SystemApis Permissions");

    // WiFi permissions
    context->getSecurity()->addPermissionForAdmin(WIFI_CREATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(WIFI_UPDATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(WIFI_DELETE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(WIFI_GET, "SystemApis Permissions");

    // Log permissions
    context->getSecurity()->addPermissionForAdmin(LOG_CREATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LOG_UPDATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LOG_DELETE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LOG_GET, "SystemApis Permissions");

    // SystemConfig permissions
    context->getSecurity()->addPermissionForAdmin(SYSTEMCONFIG_CREATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SYSTEMCONFIG_UPDATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SYSTEMCONFIG_DELETE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SYSTEMCONFIG_GET, "SystemApis Permissions");

    // SSID permissions
    context->getSecurity()->addPermissionForAdmin(SSID_CREATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SSID_UPDATE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SSID_DELETE, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SSID_GET, "SystemApis Permissions");

    // Clock permissions
    context->getSecurity()->addPermissionForAdmin(CLOCK_GET, "SystemApis Permissions");
    context->getSecurity()->addPermissionForAdmin(CLOCK_SET, "SystemApis Permissions");
}

// Define the static constants
const String SystemPermissions::FILE_CREATE = "file_create";
const String SystemPermissions::FILE_UPDATE = "file_update";
const String SystemPermissions::FILE_DELETE = "file_delete";
const String SystemPermissions::FILE_GET = "file_get";

const String SystemPermissions::WIFI_CREATE = "wifi_create";
const String SystemPermissions::WIFI_UPDATE = "wifi_update";
const String SystemPermissions::WIFI_DELETE = "wifi_delete";
const String SystemPermissions::WIFI_GET = "wifi_get";

const String SystemPermissions::LOG_CREATE = "log_create";
const String SystemPermissions::LOG_UPDATE = "log_update";
const String SystemPermissions::LOG_DELETE = "log_delete";
const String SystemPermissions::LOG_GET = "log_get";

const String SystemPermissions::SYSTEMCONFIG_CREATE = "systemconfig_create";
const String SystemPermissions::SYSTEMCONFIG_UPDATE = "systemconfig_update";
const String SystemPermissions::SYSTEMCONFIG_DELETE = "systemconfig_delete";
const String SystemPermissions::SYSTEMCONFIG_GET = "systemconfig_get";

const String SystemPermissions::SSID_CREATE = "ssid_create";
const String SystemPermissions::SSID_UPDATE = "ssid_update";
const String SystemPermissions::SSID_DELETE = "ssid_delete";
const String SystemPermissions::SSID_GET = "ssid_get";

const String SystemPermissions::CLOCK_GET = "clock_get";
const String SystemPermissions::CLOCK_SET = "clock_set";

#endif // SYSTEMPERMISSIONS_H
