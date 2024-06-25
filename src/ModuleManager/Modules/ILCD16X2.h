#ifndef ILCD16X2_H
#define ILCD16X2_H

#include <Arduino.h>
#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/LCDFullEntity.h"
#include "BaseModule.h"

class ILCD16X2: public BaseModule {
public:
    ILCD16X2(int module_id, int serverId, String name, String moduleType, int device_id):
        BaseModule(module_id, serverId, name, moduleType, device_id){}

    virtual void drawText(String text, int textSize) = 0;  // Method to draw text on the LCD
    virtual void Clean() = 0;                              // Method to clear the LCD display
    virtual LCDFullEntity* getEntity() = 0;                // Method to retrieve the entity representation of the LCD
    virtual int getWidth() = 0; 
    virtual int getHeight() = 0;

    // Static methods to convert between LCD type enums and strings
    virtual String getLCDType(LCDTypes lcdType) = 0;
    virtual LCDTypes getLCDType(String lcdTypeStr) = 0;
};

#endif // ILCD16X2_H
