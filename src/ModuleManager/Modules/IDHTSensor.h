#ifndef IDHTSENSOR_H
#define IDHTSENSOR_H

#include "../../Database/Entities/Modules/DHTFullEntity.h"

class IDHTSensor
{
public:
    virtual void update() = 0;
    virtual String getName() = 0;
    virtual float getHumidity() = 0;
    virtual float getTemperatureC() = 0;
    virtual float getTemperatureF() = 0;
    virtual bool isDataValid() = 0;
    virtual int getServerId() = 0;
    virtual void setServerId(int serverId) = 0;
    virtual DHTFullEntity* getEntity() = 0;
};



#endif //IDHTSENSOR_H