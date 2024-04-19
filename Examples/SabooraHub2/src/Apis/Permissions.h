#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String LIGHT_SWITCH_GARDEN_LIGHTS;
    static const String LIGHT_SWITCH_GAZEBO_LIGHTS;
    static const String TAGCONTROLLER_OPENDOOR;

    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(LIGHT_SWITCH_GARDEN_LIGHTS, "SabooraHub2 Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHT_SWITCH_GAZEBO_LIGHTS, "SabooraHub2 Permissions");
    context->getSecurity()->addPermissionForAdmin(TAGCONTROLLER_OPENDOOR, "Darboon Permissions");

}

const String Permissions::LIGHT_SWITCH_GARDEN_LIGHTS = "light_switch_garden_lights";
const String Permissions::LIGHT_SWITCH_GAZEBO_LIGHTS = "light_switch_gazebo_lights";
const String Permissions::TAGCONTROLLER_OPENDOOR = "tagcontroller_opendoor";


#endif // PERMISSIONS_H
