#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include "OStad.h"

class Permissions
{
public:
    static const String RECENTACTIVITIES_CREATE;
    static const String RECENTACTIVITIES_UPDATE;
    static const String RECENTACTIVITIES_DELETE;
    static const String RECENTACTIVITIES_GET;
    static const String PRINTER_GETPRINTERSTATUS;
    static const String PRINTER_GETACTIVEWIFI;
    static const String PRINTER_GETFRIMWAREINFO;
    static const String PRINTER_GETRECENTACTIVITY;
    static const String PRINTER_GETPRINTERSETTINGS;
    static const String PRINTER_SETPRINTERSETTINGS;
    static const String PRINTER_GETPRINTERINFO;
    static const String TEMPLATES_GETACTIVETEMPLATE;
    static const String TEMPLATES_GETALLTEMPLATES;
    static const String TEMPLATES_GETTEMPLATESETTINGS;
    static const String TEMPLATES_SETTEMPLATESETTINGS;
    static const String TEMPLATES_EXPORTTEMPLATE;
    static const String TEMPLATES_IMPORTTEMPLATE;
    static const String TEMPLATES_SETACTIVETEMPLATE;
    static const String TEMPLATES_SAVETEMPLATE;
    static const String TEMPLATES_PREVIEWTEMPLATE;
    static const String TEMPLATES_LOADTEMPLATE;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(RECENTACTIVITIES_CREATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(RECENTACTIVITIES_UPDATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(RECENTACTIVITIES_DELETE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(RECENTACTIVITIES_GET, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETPRINTERSTATUS, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETACTIVEWIFI, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETFRIMWAREINFO, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETRECENTACTIVITY, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETPRINTERSETTINGS, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_SETPRINTERSETTINGS, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(PRINTER_GETPRINTERINFO, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_GETACTIVETEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_GETALLTEMPLATES, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_GETTEMPLATESETTINGS, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_SETTEMPLATESETTINGS, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_EXPORTTEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_IMPORTTEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_SETACTIVETEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_SAVETEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_PREVIEWTEMPLATE, "InkjetPrinter Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPLATES_LOADTEMPLATE, "InkjetPrinter Permissions");

}

const String Permissions::RECENTACTIVITIES_CREATE = "recentactivities_create";
const String Permissions::RECENTACTIVITIES_UPDATE = "recentactivities_update";
const String Permissions::RECENTACTIVITIES_DELETE = "recentactivities_delete";
const String Permissions::RECENTACTIVITIES_GET = "recentactivities_get";
const String Permissions::PRINTER_GETPRINTERSTATUS = "printer_getprinterstatus";
const String Permissions::PRINTER_GETACTIVEWIFI = "printer_getactivewifi";
const String Permissions::PRINTER_GETFRIMWAREINFO = "printer_getfrimwareinfo";
const String Permissions::PRINTER_GETRECENTACTIVITY = "printer_getrecentactivity";
const String Permissions::PRINTER_GETPRINTERSETTINGS = "printer_getprintersettings";
const String Permissions::PRINTER_SETPRINTERSETTINGS = "printer_setprintersettings";
const String Permissions::PRINTER_GETPRINTERINFO = "printer_getprinterinfo";
const String Permissions::TEMPLATES_GETACTIVETEMPLATE = "templates_getactivetemplate";
const String Permissions::TEMPLATES_GETALLTEMPLATES = "templates_getalltemplates";
const String Permissions::TEMPLATES_GETTEMPLATESETTINGS = "templates_gettemplatesettings";
const String Permissions::TEMPLATES_SETTEMPLATESETTINGS = "templates_settemplatesettings";
const String Permissions::TEMPLATES_EXPORTTEMPLATE = "templates_exporttemplate";
const String Permissions::TEMPLATES_IMPORTTEMPLATE = "templates_importtemplate";
const String Permissions::TEMPLATES_SETACTIVETEMPLATE = "templates_setactivetemplate";
const String Permissions::TEMPLATES_SAVETEMPLATE = "templates_savetemplate";
const String Permissions::TEMPLATES_PREVIEWTEMPLATE = "templates_previewtemplate";
const String Permissions::TEMPLATES_LOADTEMPLATE = "templates_loadtemplate";


#endif // PERMISSIONS_H
