#ifndef RFID125Kh_H
#define RFID125Kh_H

#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/RFIDFullEntity.h"
#include "BaseModule.h"

class IRFID125Kh: public BaseModule
{
public:
    using RFIDCallback = std::function<void(String)>;

public:
    IRFID125Kh(int module_id, int server_id, String name, String moduleType, int device_id):
        BaseModule(module_id, server_id, name, moduleType, device_id) {}
    
    
    virtual void setOnNewTag(RFIDCallback function) = 0;
    virtual RFIDFullEntity* getEntity() = 0;
    virtual void update() = 0;

};

#endif