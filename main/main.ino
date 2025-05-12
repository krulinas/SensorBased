#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "wifi_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define I2C_SDA       21
#define I2C_SCL       22

TwoWire oledWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &oledWire, OLED_RESET);

// Your manager: LED = GPIO2, Button = GPIO0
WiFiManager wifiManager(2, 0);

void setup() {
  Serial.begin(115200);

  // Start OLED
  oledWire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("WiFi Connecting...");
  display.display();

  // Start WiFi Manager
  wifiManager.begin();

  delay(1000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.println(WiFi.localIP());
  display.display();
}

void loop() {
  wifiManager.handleClient();  // Handles AP Mode Web UI if triggered
}