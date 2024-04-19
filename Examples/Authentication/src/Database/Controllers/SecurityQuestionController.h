#ifndef SECURITYQUESTIONCONTROLLER_H
#define SECURITYQUESTIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/SecurityQuestionEntity.h"
#include "../../AppContext.h"

class SecurityQuestionController : public MainController<SecurityQuestionEntity> {
public:
    AppContext* appContext;
    SecurityQuestionController(AppContext* appContext, StorageType _storageType) : MainController<SecurityQuestionEntity>(appContext->systemContext ,"securityquestion", _storageType), appContext(appContext) {}
};

#endif // SECURITYQUESTIONCONTROLLER_H