#ifndef SECURITYQUESTIONTITLECONTROLLER_H
#define SECURITYQUESTIONTITLECONTROLLER_H

#include "../../Entities/Security/SecurityQuestionTitleEntity.h"
#include "../../../Context.h"

class SecurityQuestionTitleController : public MainController<SecurityQuestionTitleEntity> {
public:
    Context* context;
    SecurityQuestionTitleController(Context* context, StorageType _storageType) : MainController<SecurityQuestionTitleEntity>(context ,"securityquestiontitle", _storageType), context(context) {}
};

#endif // SECURITYQUESTIONTITLECONTROLLER_H