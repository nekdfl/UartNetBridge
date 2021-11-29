#include "coreapp/coreapp.hpp"

#ifndef DEVMODE

CoreApp::CoreApp()
{
    delay(5000);
    m_telnetbridge_uptr = std::unique_ptr<TelnetBridge>(new TelnetBridge(23, 1024, 115200));
}

CoreApp::~CoreApp()
{
}

void CoreApp::setup()
{
    AppConf v_appconf;
    LittleFS.begin();

    Serial.begin(115200);
    Serial.println("\r\n\r\n\r\n;Boot complete");

    //if gpio2 is down when reset wifi settings
    resetWifiOnBoot();

    startWifi(v_appconf);

    Serial.println(";\n;run main program...");

    m_telnetbridge_uptr->begin();
}

void CoreApp::loop()
{
    m_telnetbridge_uptr->loop();
}

void CoreApp::resetWifiOnBoot()
{
    pinMode(2, INPUT_PULLUP);
    if (digitalRead(2) == 0)
    {
        resetWifiSettings();
    }
}

void CoreApp::startWifi(AppConf &a_appconf)
{
    m_wifimanger.setDebugOutput(false);
    m_wifimanger.setSaveConfigCallback(
        []()
        { CoreApp::setSaveFlag(); });
    WiFi.setSleepMode(WIFI_NONE_SLEEP);

    if (a_appconf.isFileExist(WIFISETTINGS_FILES))
    {
        Serial.println(";Start with timeout wifimanager...");
        configViaAPWifiManager(CONFIG_PORTAL_TIMEOUT);
        Serial.println(";try connect...");
        readWifiSettingsAndConnect(a_appconf, WIFITRY, CONNECT_TIMEOUT);
    }
    else if (!readWifiSettingsAndConnect(a_appconf, WIFITRY, CONNECT_TIMEOUT))
    {
        Serial.println(";Start wifimanager...");
        configViaAPWifiManager();
    }
}

bool CoreApp::readWifiSettingsAndConnect(AppConf &a_appconf, unsigned int a_tries, unsigned int a_timeout)
{
    std::list<String> wifilist = a_appconf.getLPChildList(WIFISETTINGS_FILES, "/wifilist");
    bool connected = false;

    for (unsigned int v_try = 0; v_try < a_tries; v_try++)
    {
        for (auto &wifiname : wifilist)
        {
            String longpath = WIFILISTLP + wifiname;
            String wifipass = a_appconf.getLPValue(WIFISETTINGS_FILES, longpath);
            WiFi.begin(wifiname.c_str(), wifipass.c_str());
            unsigned int count = 0;
            while (WiFi.status() != WL_CONNECTED and count < a_timeout)
            {
                Serial.print(";.");
                delay(WIFICHECKINTERVAL_MS);
                count++;
            }
            connected = true;
            break;
        }
        if (connected)
            break;
    }
    return connected;
}

void CoreApp::resetWifiSettings()
{
    Serial.println(";\n;reser wifi settings...");
    AppConf v_appconf;
    v_appconf.deleteConfigFile(WIFISETTINGS_FILES);
}

void CoreApp::configViaAPWifiManager(unsigned int a_timeout)
{
    String chipid_str = String(ESP.getChipId());
    String ap_ssid = "SerialToWebsock-" + chipid_str;
    String ap_pass = "STW-" + chipid_str;

    m_wifimanger.setTimeout(a_timeout);

    if (m_wifimanger.startConfigPortal(ap_ssid.c_str(), ap_pass.c_str()))
    {
        if (m_shouldsaveconfig)
        {
            saveCurrentWifi();
        }
    }
}

void CoreApp::saveCurrentWifi()
{
    AppConf v_appconf;
    String current_wifi_ssid = WiFi.SSID();
    String current_wifi_passwd = WiFi.psk();
    String longpath = WIFILISTLP + current_wifi_ssid;
    //create file  /config/[WIFISETTINGS_FILES]
    if (!v_appconf.isFileExist(WIFISETTINGS_FILES))
        v_appconf.createConfFile(WIFISETTINGS_FILES);

    v_appconf.setLPValue(WIFISETTINGS_FILES, longpath, current_wifi_passwd);
}

#endif