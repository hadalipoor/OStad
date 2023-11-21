#include "GFXcanvasSerialDemo.h"
#include <Arduino.h>

GFXcanvas1SerialDemo::GFXcanvas1SerialDemo(int16_t w, int16_t h)
    : GFXcanvas1(w, h) {}

void GFXcanvas1SerialDemo::print(bool rotated) {
  char pixel_buffer[8];
  int16_t width, height;

  if (rotated) {
    width = this->width();
    height = this->height();
  } else {
    width = this->WIDTH;
    height = this->HEIGHT;
  }
  
  for (int16_t y = 0; y < height; y++) {
    for (int16_t x = 0; x < width; x++) {
      bool pixel;
      if (rotated) {
        pixel = this->getPixel(x, y);
      } else {
        pixel = this->getRawPixel(x, y);
      }
      sprintf(pixel_buffer, " %d", pixel);
      Serial.print(pixel_buffer);
    }
    Serial.print("\n");
  }
}

// GFXcanvas8SerialDemo::GFXcanvas8SerialDemo(): GFXcanvas8(){
  
// }

GFXcanvas8SerialDemo::GFXcanvas8SerialDemo(int16_t w, int16_t h)
    : GFXcanvas8(w, h) {}

void GFXcanvas8SerialDemo::print(bool rotated) {
  char pixel_buffer[8];
  int16_t width, height;

  if (rotated) {
    width = this->width();
    height = this->height();
  } else {
    width = this->WIDTH;
    height = this->HEIGHT;
  }

  for (int16_t y = 0; y < height; y++) {
    for (int16_t x = 0; x < width; x++) {
      uint8_t pixel;
      if (rotated) {
        pixel = this->getPixel(x, y);
      } else {
        pixel = this->getRawPixel(x, y);
      }
      sprintf(pixel_buffer, "%02x", pixel);
      Serial.print(pixel_buffer);
    }
    Serial.print("\n");
  }
}

GFXcanvas16SerialDemo::GFXcanvas16SerialDemo(int16_t w, int16_t h)
    : GFXcanvas16(w, h) {}

void GFXcanvas16SerialDemo::print(bool rotated) {
  char pixel_buffer[8];
  int16_t width, height;

  if (rotated) {
    width = this->width();
    height = this->height();
  } else {
    width = this->WIDTH;
    height = this->HEIGHT;
  }

  for (int16_t y = 0; y < height; y++) {
    for (int16_t x = 0; x < width; x++) {
      int16_t pixel;
      if (rotated) {
        pixel = this->getPixel(x, y);
      } else {
        pixel = this->getRawPixel(x, y);
      }
      sprintf(pixel_buffer, " %04x", pixel);
      Serial.print(pixel_buffer);
    }
    Serial.print("\n");
  }
}
