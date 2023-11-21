#ifndef INTERNALCLOCK_h
#define INTERNALCLOCK_h

#include "time.h"

class InternalClock {
private:
  const char* ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 12600; // Tehran is GMT+3:30
  const int daylightOffset_sec = 0; // Adjust if daylight saving is used

public:
  InternalClock() {
    // Constructor could initialize the Wi-Fi connection if desired
    // WiFi.begin(ssid, password);
  }

  // Synchronize the local time with the NTP server
  bool synchronize_ntp() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    return waitForSync();
  }

  // Synchronize the local clock with a given time_t value
  void synchronize(time_t time_) {
    struct timeval now = {.tv_sec = time_};
    settimeofday(&now, NULL);
  }

  // Get the current time as a time_t value
  time_t now() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      // Serial.println("Failed to obtain time");
      return 0;
    }
    return mktime(&timeinfo);
  }

  // Get the current time as a formatted string
  String now_string(char* time_format) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      return "Time not set";
    }
    char buffer[64];
    strftime(buffer, sizeof(buffer), time_format, &timeinfo);
    return String(buffer);
  }

  // Print the current time to the serial port at the specified baud rate
  void print_now_serial(unsigned long baud_rate) {
    Serial.begin(baud_rate);
    while (!Serial) continue; // Wait for serial port to connect
    Serial.println(now_string((char*)"%A, %B %d %Y %H:%M:%S"));
  }

private:
  // Wait for time to be synchronized
  bool waitForSync() {
    // Serial.print("Waiting for NTP time sync: ");
    time_t nowSecs = now();
    int repea_time = 0;
    while (nowSecs < 24 * 3600) {
      if(++repea_time < 6) return false;
      delay(500);
      // Serial.print(".");
      nowSecs = now();
    }
    return true;
  }
};

#endif //INTERNALCLOCK_h