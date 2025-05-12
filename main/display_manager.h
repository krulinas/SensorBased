#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

namespace DisplayManager {
  void begin(int sda = 21, int scl = 22);
  void showStatus(const String& message);
  void showInfo(const String& line1, const String& line2);
}

#endif