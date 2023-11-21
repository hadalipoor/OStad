#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include "Arduino.h"
#include "PCF8574.h"

class SevenSegment {
  private:
    PCF8574 &pcf;

    // Definitions for numbers 0-9 on a 7-segment display
    // Each sub-array contains the pins to be turned ON for that number
    const uint8_t numbers[10][7] = {
      {P0, P1, P2, P6, P7, P5},    // 0
      {P5, P2},                   // 1
      {P6, P7, P4, P2, P1},       // 2
      {P0, P1, P4, P7, P6},       // 3
      {P0, P4, P5, P7},           // 4
      {P0, P1, P5, P4, P6},       // 5
      {P0, P2, P6, P4, P5, P1},   // 6
      {P0, P7, P6},               // 7
      {P0, P1, P2, P6, P4, P5, P7}, // 8
      {P0, P1, P4, P7, P5, P6}    // 9
    };
    const uint8_t numSegments[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

  public:
    SevenSegment(PCF8574 &pcf8574) : pcf(pcf8574) {}

    void begin() {
      for (int i = 0; i <= 7; i++) {
        pcf.pinMode(i, OUTPUT);
        pcf.digitalWrite(i, LOW);  // Initialize all segments to OFF
      }
      pcf.begin();
    }

    void displayNumber(uint8_t num) {
      if (num > 9) return; // Only numbers between 0 and 9 are allowed
      
      // First turn all segments off
      for (int i = 0; i <= 7; i++) {
        pcf.digitalWrite(i, LOW);
      }

      // Then turn on the required segments
      for (int i = 0; i <= numSegments[num]; i++) {
        pcf.digitalWrite(numbers[num][i], HIGH);
      }
    }
};

#endif