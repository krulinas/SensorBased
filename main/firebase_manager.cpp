#include "firebase_manager.h"
#include "display_manager.h"
#include <WiFi.h>

// Replace with your Firebase project credentials
#define API_KEY        "AIzaSyCJjRDf8ehydZ6WOBUxZfF8eLdO9R6TCv0"
#define USER_EMAIL     "testing@gmail.com"  // ← as shown from your Firebase Auth
#define USER_PASSWORD  "Testing@123"  // 🔒 put your password here
#define DATABASE_URL   "https://sensor-based-e1324-default-rtdb.asia-southeast1.firebasedatabase.app"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String firebasePath = "/device_data/message";
String lastMessage = "";

namespace FirebaseManager {

  void begin(const String& path) {
    firebasePath = path;  // override default if passed
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    DisplayManager::showStatus("Firebase Ready");
  }

  void update() {
    if (Firebase.ready()) {
      if (Firebase.RTDB.getString(&fbdo, firebasePath)) {
        String newMsg = fbdo.stringData();
        if (newMsg != lastMessage) {
          lastMessage = newMsg;
          Serial.println("Firebase data: " + lastMessage);
          DisplayManager::showInfo("Firebase Says:", newMsg);
        }
      } else {
        Serial.println("Firebase update failed: " + fbdo.errorReason());  // ← PUT IT HERE
      }
    }
  }

  String getLastMessage() {
    return lastMessage;
  }

  bool sendString(const String& subPath, const String& value) {
    String fullPath = firebasePath + subPath;

    if (Firebase.ready()) {
      if (Firebase.RTDB.setString(&fbdo, fullPath, value)) {
        Serial.println("Sent to Firebase: " + fullPath + " = " + value);
        return true;
      } else {
        Serial.println("Send failed: " + fbdo.errorReason());
      }
    }
    return false;
  }
}
