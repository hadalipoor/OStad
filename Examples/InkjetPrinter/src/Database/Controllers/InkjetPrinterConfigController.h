
#ifndef INKJETPRINTERCONFIGCONTROLLER_H
#define INKJETPRINTERCONFIGCONTROLLER_H

#include "../../AppContext.h"

class InkjetPrinterConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    InkjetPrinterConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"inkjetprinter_config", _storageType), appContext(appContext) {}

};

#endif //INKJETPRINTERCONFIGCONTROLLER_H
    