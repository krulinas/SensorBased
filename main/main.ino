#include "wifi_manager.h"
#include "display_manager.h"

WiFiManager wifiManager(2, 0);

void setup() {
  Serial.begin(115200);
  DisplayManager::begin();  
  DisplayManager::showStatus("Connecting WiFi...");

  wifiManager.begin();

  DisplayManager::showInfo("WiFi Connected!", WiFi.localIP().toString());
}

void loop() {
  wifiManager.handleClient();
}