#include "display_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

TwoWire oledWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &oledWire, OLED_RESET);

namespace DisplayManager {

  void begin(int sda, int scl) {
    oledWire.begin(sda, scl);
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
      Serial.println("OLED init failed!");
      return;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OLED Ready");
    display.display();
  }

  void showStatus(const String& message) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(message);
    display.display();
  }

  void showInfo(const String& line1, const String& line2) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(line1);
    display.println(line2);
    display.display();
  }
}