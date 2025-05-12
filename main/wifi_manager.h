#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>

class WiFiManager{  
  public:
    WiFiManager(int ledPin = 2, int buttonPin = 0);
    void begin();
    void handleClient();

  private:
    int _ledPin, _buttonPin;
    String _ssid, _pass, _devid, _scannedNetworks;
    bool _apMode, _scanComplete;
    WebServer _server;

    void _readData();
    void _writeData(const String& ssid, const String& pass, const String& devid);
    void _clearData();
    void _apModeInit();
    bool _testWifi();
    void _startWebServer();
    void _defineRoutes();
};

#endif