#ifndef IBUTTON_H
#define IBUTTON_H

#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/ButtonFullEntity.h"
#include "BaseModule.h"

enum class ButtonType { PIN, PCF8574 };
enum class ClickType { None, Clicked, LongPressClicked };

class IButton: public BaseModule
{
public:
    using ButtonCallback = std::function<void(IButton*)>;

    IButton(int module_id, int serverId, String name, String moduleType, int device_id): BaseModule(module_id, serverId, name, moduleType,device_id){}
    
    virtual void setOnClick(ButtonCallback function) = 0;
    virtual void setOnLongPress(ButtonCallback function) = 0;
    virtual void setDebounceDelay(unsigned long delay) = 0;
    virtual long getLongPressTime() = 0;
    virtual long getDebounceDelay() = 0;
    virtual void setLongPressTime(unsigned long time) = 0;
    virtual bool getState() = 0;
    virtual String getName() = 0;
    virtual ButtonFullEntity* getEntity() = 0;
    virtual void update() = 0;
    virtual int getPinNumber() = 0;
    virtual bool getActiveHigh() = 0;
    virtual bool getPullUpActive() = 0;
};

#endif
