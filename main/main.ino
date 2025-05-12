#include "wifi_manager.h"
#include "display_manager.h"
#include "firebase_manager.h"

WiFiManager wifiManager(2, 0);

void setup() {
  Serial.begin(115200);
  
  DisplayManager::begin();
  DisplayManager::showStatus("Connecting WiFi...");

  wifiManager.begin();
  DisplayManager::showStatus("WiFi Connected","Launched AP Mode","IP: 192.168.4.1");
  String deviceID = wifiManager.getDeviceID();
  FirebaseManager::begin("/devices/" + deviceID + "/text");
  DisplayManager::showStatus("Firebase Ready");
}

void loop() {
  wifiManager.handleClient();
  FirebaseManager::update();  
  static unsigned long lastPush = 0;
  if (millis() - lastPush > 10000) {
    FirebaseManager::sendString("/status", "I'm alive at " + String(millis()));
    lastPush = millis();
  }
}