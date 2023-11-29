#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
// #define OSTAD_NETWORK_DISABLE
// #define OSTAD_MODULES_DISABLE

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
