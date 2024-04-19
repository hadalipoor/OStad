#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String TANKER_GET_CAPACITY;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(TANKER_GET_CAPACITY, "SabooraTanker Permissions");

}

const String Permissions::TANKER_GET_CAPACITY = "tanker_get_capacity";


#endif // PERMISSIONS_H
