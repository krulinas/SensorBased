#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Firebase_ESP_Client.h>

namespace FirebaseManager {
  void begin(const String& path);
  void update();
  String getLastMessage();
  bool sendString(const String& subPath, const String& value);
}

#endif