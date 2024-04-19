#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String FLOOR_CREATE;
    static const String FLOOR_UPDATE;
    static const String FLOOR_DELETE;
    static const String FLOOR_GET;
    static const String ELEVATOR_CREATE;
    static const String ELEVATOR_UPDATE;
    static const String ELEVATOR_DELETE;
    static const String ELEVATOR_GET;
    static const String REQUESTLOG_CREATE;
    static const String REQUESTLOG_UPDATE;
    static const String REQUESTLOG_DELETE;
    static const String REQUESTLOG_GET;
    static const String ELEVATORLOG_CREATE;
    static const String ELEVATORLOG_UPDATE;
    static const String ELEVATORLOG_DELETE;
    static const String ELEVATORLOG_GET;
    static const String ELEVATORCONTROL_MOVEUPMANUAL;
    static const String ELEVATORCONTROL_MOVEDOWNMANUAL;
    static const String ELEVATORCONTROL_STOPMANUAL;
    static const String ELEVATORCONTROL_FLOORREQUESTED;
    static const String ELEVATORCONTROL_CALIBRATIONREQUESTED;
    static const String ELEVATORCONTROL_EMSSTOPREQUESTED;
    static const String ELEVATORCONTROL_SETMOVEMENTMETHOD;
    static const String ELEVATORCONTROL_GETMOVEMENTMETHOD;
    static const String ELEVATORCONTROL_GETSTATE;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(FLOOR_CREATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(FLOOR_UPDATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(FLOOR_DELETE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(FLOOR_GET, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATOR_CREATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATOR_UPDATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATOR_DELETE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATOR_GET, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(REQUESTLOG_CREATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(REQUESTLOG_UPDATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(REQUESTLOG_DELETE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(REQUESTLOG_GET, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORLOG_CREATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORLOG_UPDATE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORLOG_DELETE, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORLOG_GET, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_MOVEUPMANUAL, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_MOVEDOWNMANUAL, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_STOPMANUAL, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_FLOORREQUESTED, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_CALIBRATIONREQUESTED, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_EMSSTOPREQUESTED, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_SETMOVEMENTMETHOD, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_GETMOVEMENTMETHOD, "ElevatorControl Permissions");
    context->getSecurity()->addPermissionForAdmin(ELEVATORCONTROL_GETSTATE, "ElevatorControl Permissions");

}

const String Permissions::FLOOR_CREATE = "floor_create";
const String Permissions::FLOOR_UPDATE = "floor_update";
const String Permissions::FLOOR_DELETE = "floor_delete";
const String Permissions::FLOOR_GET = "floor_get";
const String Permissions::ELEVATOR_CREATE = "elevator_create";
const String Permissions::ELEVATOR_UPDATE = "elevator_update";
const String Permissions::ELEVATOR_DELETE = "elevator_delete";
const String Permissions::ELEVATOR_GET = "elevator_get";
const String Permissions::REQUESTLOG_CREATE = "requestlog_create";
const String Permissions::REQUESTLOG_UPDATE = "requestlog_update";
const String Permissions::REQUESTLOG_DELETE = "requestlog_delete";
const String Permissions::REQUESTLOG_GET = "requestlog_get";
const String Permissions::ELEVATORLOG_CREATE = "elevatorlog_create";
const String Permissions::ELEVATORLOG_UPDATE = "elevatorlog_update";
const String Permissions::ELEVATORLOG_DELETE = "elevatorlog_delete";
const String Permissions::ELEVATORLOG_GET = "elevatorlog_get";
const String Permissions::ELEVATORCONTROL_MOVEUPMANUAL = "elevatorcontrol_moveupmanual";
const String Permissions::ELEVATORCONTROL_MOVEDOWNMANUAL = "elevatorcontrol_movedownmanual";
const String Permissions::ELEVATORCONTROL_STOPMANUAL = "elevatorcontrol_stopmanual";
const String Permissions::ELEVATORCONTROL_FLOORREQUESTED = "elevatorcontrol_floorrequested";
const String Permissions::ELEVATORCONTROL_CALIBRATIONREQUESTED = "elevatorcontrol_calibrationrequested";
const String Permissions::ELEVATORCONTROL_EMSSTOPREQUESTED = "elevatorcontrol_emsstoprequested";
const String Permissions::ELEVATORCONTROL_SETMOVEMENTMETHOD = "elevatorcontrol_setmovementmethod";
const String Permissions::ELEVATORCONTROL_GETMOVEMENTMETHOD = "elevatorcontrol_getmovementmethod";
const String Permissions::ELEVATORCONTROL_GETSTATE = "elevatorcontrol_getstate";


#endif // PERMISSIONS_H
