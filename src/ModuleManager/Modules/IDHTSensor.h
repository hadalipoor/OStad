#ifndef IDHTSENSOR_H
#define IDHTSENSOR_H

#include "../../Database/Entities/Modules/DHTFullEntity.h"
#include "BaseModule.h"

class IDHTSensor: public BaseModule {
public:
    IDHTSensor(int module_id, int serverId, String name, String moduleType, int device_id):
        BaseModule(module_id, serverId, name, moduleType, device_id){}
        
    virtual void update() = 0;
    virtual String getName() = 0;
    virtual float getHumidity() = 0;
    virtual float getTemperatureC() = 0;
    virtual float getTemperatureF() = 0;
    virtual int getPinNumber() = 0;
    virtual String getType() = 0;
    virtual bool isDataValid() = 0;
    virtual DHTFullEntity* getEntity() = 0;
};



#endif //IDHTSENSOR_H