#ifndef SECURITYQUESTIONCONTROLLER_H
#define SECURITYQUESTIONCONTROLLER_H

#include "../../Entities/Security/SecurityQuestionEntity.h"
#include "../../../Context.h"

class SecurityQuestionController : public MainController<SecurityQuestionEntity> {
public:
    Context* context;
    SecurityQuestionController(Context* context, StorageType _storageType) : MainController<SecurityQuestionEntity>(context ,"securityquestion", _storageType), context(context) {}
};

#endif // SECURITYQUESTIONCONTROLLER_H