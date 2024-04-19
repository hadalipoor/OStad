#include "src/Runtime.h"

Runtime* runtime;

void setup() {
  Serial.begin(115200);
  LittleFS.begin(true);
  runtime = new Runtime();
}
void loop() {
  runtime->update();
}
