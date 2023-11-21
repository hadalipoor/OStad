#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "InkjetPrinter/IInkjetPrinter.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* inkjetprinterConfig;
    IInkjetPrinter* inkjetprinter;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getInkjetPrinterConfig() { return inkjetprinterConfig; }
    void setInkjetPrinterConfig(IConfig* config) { inkjetprinterConfig = config; }
    
    IInkjetPrinter* getInkjetPrinter() { return inkjetprinter; }
    void setinkjetprinter(IInkjetPrinter* _inkjetprinter) { inkjetprinter = _inkjetprinter; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
