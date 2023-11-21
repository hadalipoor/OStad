#include "src/Runtime.h"

Runtime* runtime;

void setup() {
  Serial.begin(115200);
  SD.begin();
  LittleFS.begin();
  // LittleFS.format();
  runtime = new Runtime();
}
void loop() {
  runtime->update();
}
