#ifndef RFID125KH_H
#define RFID125KH_H

#include <Wiegand.h>
#include "../../Database/Entities/Modules/RFIDFullEntity.h"
#include "ModuleTypes.h"

class RFID125Kh
{
public:
    using RFIDCallback = std::function<void(String)>;
private:
    RFIDCallback onNewTag;
    WIEGAND wg;
public:
    RFID125Kh(String name, int pin0, int pin1);
    void setOnNewTag(RFIDCallback function);
    RFIDFullEntity* getEntity();
    void update();

    String name;
    String connectionType;
    int nodeId;
    int Pin0;
    int Pin1;
    ~RFID125Kh();
};

RFID125Kh::RFID125Kh(String name, int pin0, int pin1)
{
    name = name;
    Pin0 = pin0;
    Pin1 = pin1;

    wg.begin(pin0, pin1);
}

void RFID125Kh::setOnNewTag(RFIDCallback function)
{
    onNewTag = function;
}

void RFID125Kh::update()
{
    if(wg.available())
	{
		// Serial.print("Wiegand HEX = ");
		// Serial.print(wg.getCode(),HEX);
		// Serial.print(", DECIMAL = ");
		// Serial.print(wg.getCode());
		// Serial.print(", Type W");
		// Serial.println(wg.getWiegandType());
        onNewTag(String(wg.getCode()));
	}

}

RFIDFullEntity* RFID125Kh::getEntity()
{
    return new RFIDFullEntity(0, 0, name, ModuleTypes::RFID125KH, connectionType, nodeId, Pin0, Pin1);
}

RFID125Kh::~RFID125Kh()
{
}


#endif //RFID125KH_H