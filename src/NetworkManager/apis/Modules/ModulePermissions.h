#ifndef MODULEPERMISSIONS_H
#define MODULEPERMISSIONS_H

#include "../../../Context.h"

class ModulePermissions
{
public:
    static const String BUTTON_CREATE;
    static const String BUTTON_UPDATE;
    static const String BUTTON_DELETE;
    static const String BUTTON_GET;
    static const String MODULE_CREATE;
    static const String MODULE_UPDATE;
    static const String MODULE_DELETE;
    static const String MODULE_GET;
    static const String RELAY_CREATE;
    static const String RELAY_UPDATE;
    static const String RELAY_DELETE;
    static const String RELAY_GET;
    static const String LCD_CREATE;
    static const String LCD_UPDATE;
    static const String LCD_DELETE;
    static const String LCD_GET;
    static const String DHT_CREATE;
    static const String DHT_UPDATE;
    static const String DHT_DELETE;
    static const String DHT_GET;
    static const String PHOTORESISTOR_CREATE;
    static const String PHOTORESISTOR_UPDATE;
    static const String PHOTORESISTOR_DELETE;
    static const String PHOTORESISTOR_GET;
    static const String RGB_CREATE;
    static const String RGB_UPDATE;
    static const String RGB_DELETE;
    static const String RGB_GET;
    static const String SOILMOISTURE_CREATE;
    static const String SOILMOISTURE_UPDATE;
    static const String SOILMOISTURE_DELETE;
    static const String SOILMOISTURE_GET;


    static void addPermissions(Context* context);
};

void ModulePermissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(BUTTON_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTON_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTON_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(BUTTON_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(MODULE_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(MODULE_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(MODULE_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(MODULE_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAY_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAY_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAY_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RELAY_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LCD_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LCD_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LCD_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(LCD_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(DHT_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(DHT_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(DHT_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(DHT_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTOR_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTOR_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTOR_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(PHOTORESISTOR_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RGB_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RGB_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RGB_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(RGB_GET, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURE_CREATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURE_UPDATE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURE_DELETE, "ModuleApis Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURE_GET, "ModuleApis Permissions");

}

const String ModulePermissions::BUTTON_CREATE = "button_create";
const String ModulePermissions::BUTTON_UPDATE = "button_update";
const String ModulePermissions::BUTTON_DELETE = "button_delete";
const String ModulePermissions::BUTTON_GET = "button_get";
const String ModulePermissions::MODULE_CREATE = "module_create";
const String ModulePermissions::MODULE_UPDATE = "module_update";
const String ModulePermissions::MODULE_DELETE = "module_delete";
const String ModulePermissions::MODULE_GET = "module_get";
const String ModulePermissions::RELAY_CREATE = "relay_create";
const String ModulePermissions::RELAY_UPDATE = "relay_update";
const String ModulePermissions::RELAY_DELETE = "relay_delete";
const String ModulePermissions::RELAY_GET = "relay_get";
const String ModulePermissions::LCD_CREATE = "lcd_create";
const String ModulePermissions::LCD_UPDATE = "lcd_update";
const String ModulePermissions::LCD_DELETE = "lcd_delete";
const String ModulePermissions::LCD_GET = "lcd_get";
const String ModulePermissions::DHT_CREATE = "dht_create";
const String ModulePermissions::DHT_UPDATE = "dht_update";
const String ModulePermissions::DHT_DELETE = "dht_delete";
const String ModulePermissions::DHT_GET = "dht_get";
const String ModulePermissions::PHOTORESISTOR_CREATE = "photoresistor_create";
const String ModulePermissions::PHOTORESISTOR_UPDATE = "photoresistor_update";
const String ModulePermissions::PHOTORESISTOR_DELETE = "photoresistor_delete";
const String ModulePermissions::PHOTORESISTOR_GET = "photoresistor_get";
const String ModulePermissions::RGB_CREATE = "rgb_create";
const String ModulePermissions::RGB_UPDATE = "rgb_update";
const String ModulePermissions::RGB_DELETE = "rgb_delete";
const String ModulePermissions::RGB_GET = "rgb_get";
const String ModulePermissions::SOILMOISTURE_CREATE = "soilmoisture_create";
const String ModulePermissions::SOILMOISTURE_UPDATE = "soilmoisture_update";
const String ModulePermissions::SOILMOISTURE_DELETE = "soilmoisture_delete";
const String ModulePermissions::SOILMOISTURE_GET = "soilmoisture_get";


#endif // PERMISSIONS_H
