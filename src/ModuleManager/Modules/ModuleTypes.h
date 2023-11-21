#ifndef MODULETYPES_h
#define MODULETYPES_h

enum LCDTypes {OLED_LCD, LCD_16X2};

class ModuleTypes {
public:
    static const String BUTTON;
    static const String RELAY;
    static const String SOILMOISTURE;
    static const String LCD;
    static const String DHT;
    static const String RGB;
    static const String PHOTORESISTOR;
};

const String ModuleTypes::BUTTON = "Button";
const String ModuleTypes::RELAY = "Relay";
const String ModuleTypes::SOILMOISTURE = "SoilMoisture";
const String ModuleTypes::LCD = "LCD";
const String ModuleTypes::DHT = "DHT";
const String ModuleTypes::RGB = "RGB";
const String ModuleTypes::PHOTORESISTOR = "PhotoResistor";

#endif