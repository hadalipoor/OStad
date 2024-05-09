#ifndef USERRESETPASSCONTROLLER_H
#define USERRESETPASSCONTROLLER_H

#include "../../Entities/Security/UserResetPassEntity.h"
#include "../../../Context.h"

class UserResetPassController : public MainController<UserResetPassEntity> {
public:
    Context* context;
    UserResetPassController(Context* context, StorageType _storageType) : MainController<UserResetPassEntity>(context ,"userresetpass", _storageType), context(context) {}
};

#endif // USERRESETPASSCONTROLLER_H