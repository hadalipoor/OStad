#ifndef IRFIDPN_H
#define IRFIDPN_H

#include "ModuleTypes.h"
#include "BaseModule.h"
#include "../../Database/Entities/Modules/RFIDFullEntity.h"

class IRFIDPN532: public BaseModule
{
public:
    using RFIDCallback = std::function<void(String)>;
    IRFIDPN532(int module_id, int server_id, String name, String moduleType, int device_id):
        BaseModule(module_id, server_id, name, moduleType, device_id) {}
    
    virtual void setOnNewTag(RFIDCallback function) = 0;
    virtual bool checkModule() = 0;
    virtual uint32_t getVersionData() = 0;
    virtual RFIDFullEntity* getEntity() = 0;
    virtual void update() = 0;

};


#endif