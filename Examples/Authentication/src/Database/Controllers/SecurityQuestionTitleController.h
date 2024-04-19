#ifndef SECURITYQUESTIONTITLECONTROLLER_H
#define SECURITYQUESTIONTITLECONTROLLER_H

#include <OStad.h>
#include "../Entities/SecurityQuestionTitleEntity.h"
#include "../../AppContext.h"

class SecurityQuestionTitleController : public MainController<SecurityQuestionTitleEntity> {
public:
    AppContext* appContext;
    SecurityQuestionTitleController(AppContext* appContext, StorageType _storageType) : MainController<SecurityQuestionTitleEntity>(appContext->systemContext ,"securityquestiontitle", _storageType), appContext(appContext) {}
};

#endif // SECURITYQUESTIONTITLECONTROLLER_H