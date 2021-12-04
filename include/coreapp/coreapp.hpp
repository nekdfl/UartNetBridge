#ifndef COREAPP_HPP
#define COREAPP_HPP

#include <Arduino.h>
#include <appconf.hpp>
#include <LittleFS.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>

#include "telnetbridge/telnetbrdige.hpp"

#include "config.hpp"
#ifndef DEVMODE

#ifdef DEBUG_TO_SERIAL
#undef DEBUG_TO_SERIAL
#define DEBUG_TO_SERIAL 1
#endif

class CoreApp
{
private:
    const String WIFISETTINGS_FILES = "wifi.json";
    const String WIFILISTLP = "/wifilist/";
    const unsigned int WIFICHECKINTERVAL_MS = 1000;
    const uint8 WIFITRY = 3;
    const uint8 CONNECT_TIMEOUT = 10;
    const uint8 CONFIG_PORTAL_TIMEOUT = 1;
    WiFiManager m_wifimanger;
    std::unique_ptr<TelnetBridge> m_telnetbridge_uptr;

public:
    CoreApp();
    ~CoreApp();

    void setup();
    void loop();
    static void setSaveFlag()
    {
        m_shouldsaveconfig = true;
    };

    static bool m_shouldsaveconfig;

private:
    void resetWifiOnBoot();
    void startWifi(AppConf &a_appconf);
    bool readWifiSettingsAndConnect(AppConf &a_appconf, unsigned int a_tries, unsigned int a_timeout);
    void resetWifiSettings();
    void configViaAPWifiManager(unsigned int a_timeout = 0);
    void saveCurrentWifi();
};

#endif

#endif