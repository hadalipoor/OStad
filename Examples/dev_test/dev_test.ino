#include <OStad_dev.h>

OStad_dev* ostad;
long saved_millis = 0;
void setup()
{
    Serial.begin(115200);
    LittleFS.begin(true);

    ostad = new OStad_dev(StorageType::SPIFFS_TYPE);
    ostad->begin();
    saved_millis = millis();
}
void loop()
{
    ostad->update();
    if (millis() - saved_millis > 1000)
    {
        // Serial.println("getFreeHeap = " + String(ostad->getContext()->getSystemMonitor()->getFreeHeap()));
        // Serial.println("getFreePsram = " + String(ostad->getContext()->getSystemMonitor()->getFreePsram()));
        // Serial.println("getFreeSketchSpace = " + String(ostad->getContext()->getSystemMonitor()->getFreeSketchSpace()));
        // Serial.println("getHeapSize = " + String(ostad->getContext()->getSystemMonitor()->getHeapSize()));
        // Serial.println("getMinHeapSize = " + String(ESP.getMinFreeHeap()));
        saved_millis = millis();
    }
    

}