#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../../Entities/Security/UserEntity.h"
#include "../../../Context.h"

class UserController : public MainController<UserEntity> {
public:
    Context* context;
    UserController(Context* context, StorageType _storageType) : MainController<UserEntity>(context ,"user", _storageType), context(context) {}
};

#endif // USERCONTROLLER_H