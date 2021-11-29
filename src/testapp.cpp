#include "config.hpp"
#ifdef DEVMODE

// #include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

// #include <ESPAsyncWebServer.h>
// #include <ESPAsyncWiFiManager.h> //https://github.com/tzapu/WiFiManager

// AsyncWebServer server(80);
// DNSServer dns;

// void printboardinfo()
// {
//     auto bootVersion = String(ESP.getBootVersion());
//     auto bootmode = String(ESP.getBootMode());
//     auto corever = String(ESP.getCoreVersion());
//     auto chiphsize = String(ESP.getFlashChipSize());
//     auto chiprealsize = String(ESP.getFlashChipRealSize());
//     auto freeheap = String(ESP.getFreeHeap());

//     auto checkflashconfig = String(ESP.checkFlashConfig());
//     auto cpufreq = String(ESP.getCpuFreqMHz());

//     Serial.println("Board info");

//     Serial.print("bootVersion: ");
//     Serial.println(bootVersion.c_str());

//     Serial.print("boot mode: ");
//     Serial.println(bootmode.c_str());

//     Serial.print("CoreVersion: ");
//     Serial.println(corever.c_str());

//     Serial.print("chip size: ");
//     Serial.println(chiphsize.c_str());

//     Serial.print("chip real size: ");
//     Serial.println(chiprealsize.c_str());

//     Serial.print("free ram: ");
//     Serial.println(freeheap.c_str());

//     Serial.print("check config: ");
//     Serial.println(checkflashconfig.c_str());

//     Serial.print("cpu freq: ");
//     Serial.println(cpufreq.c_str());
// }

// void setup()
// {

//     Serial.begin(115200);
//     Serial.println();
//     Serial.println();
//     Serial.println("Boot complete");

//     // printboardinfo();

//     AsyncWiFiManager wifiManager(&server, &dns);
//     String chipid_str = String(ESP.getChipId());
//     String ap_ssid = "SerialToWebsock-" + chipid_str;
//     String ap_pass = chipid_str;

//     wifiManager.setTimeout(180);

//     // wifiManager.setConnectTimeout(15);
//     // wifiManager.setRemoveDuplicateAPs(true);

//     if (!wifiManager.autoConnect(ap_ssid.c_str(), ap_pass.c_str(), 3, 3000))
//     {
//         Serial.println("failed to connect and hit timeout");
//         ESP.reset();
//     }

//     Serial.println("connected...yeey :)");

//     Serial.print("current ssid: ");
//     Serial.println(WiFi.SSID());
//     Serial.print("current pass: ");
//     Serial.println(WiFi.psk());
// }

// void loop()
// {
//     // put your main code here, to run repeatedly:
// }

//*************************************************************************//
// /*********
//   Rui Santos
//   Complete project details at http://randomnerdtutorials.com
// *********/
// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
// #include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
// #include <LittleFS.h>

// //flag for saving data
// bool shouldSaveConfig = false;

// //callback notifying us of the need to save config
// void saveConfigCallback()
// {
//     Serial.println("Should save config");
//     shouldSaveConfig = true;
// }

// void wifiManagerExample()
// {

//     WiFiManager wifiManager;

//     wifiManager.setSaveConfigCallback(saveConfigCallback);
//     wifiManager.autoConnect("AutoConnectAP");
//     Serial.println("Connected.");
//     //save the custom parameters to FS
//     if (shouldSaveConfig)
//     {
//         Serial.println("saving config");
//         Serial.print("current ssid: ");
//         Serial.println(WiFi.SSID());
//         Serial.print("current pass: ");
//         Serial.println(WiFi.psk());

//         Serial.println("save data to file");

//         //end save
//     }
// }

// unsigned long previousMillis = 0;
// unsigned long interval = 30000;

// void setup()
// {
//     Serial.begin(115200);
//     LittleFS.begin();
//     WiFi.mode(WIFI_STA);

//     String fileflag = "/flag";
//     if (!LittleFS.exists(fileflag.c_str()))
//     {

//         Serial.print("Connecting to WiFi ..");
//         WiFi.begin("Mastermind", "362514789");
//         while (WiFi.status() != WL_CONNECTED)
//         {
//             Serial.print('.');
//             delay(1000);
//         }
//         File vfile = LittleFS.open(fileflag.c_str(), "w");
//         vfile.close();
//     }
//     else
//     {
//         Serial.println("try connect last wifi");
//         WiFi.begin();
//         while (WiFi.status() != WL_CONNECTED)
//         {
//             Serial.print('.');
//             delay(500);
//         }
//         Serial.println("connected wifi");
//     }
// }

// void loop()
// {
//     unsigned long currentMillis = millis();
//     if (currentMillis - previousMillis >= interval)
//     {
//         switch (WiFi.status())
//         {
//         case WL_NO_SSID_AVAIL:
//             Serial.println("Configured SSID cannot be reached");
//             break;
//         case WL_CONNECTED:
//             Serial.println("Connection successfully established");
//             break;
//         case WL_CONNECT_FAILED:
//             Serial.println("Connection failed");
//             break;
//         default:
//             break;
//         }
//         Serial.printf("Connection status: %d\n", WiFi.status());
//         Serial.print("RRSI: ");
//         Serial.println(WiFi.RSSI());
//         previousMillis = currentMillis;
//     }
// }

#include <Arduino.h>
#include <LittleFS.h>
// #include <ESP8266WiFi.h>
#include <appconf.hpp>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws

const char *ssid = "your-ssid";
const char *password = "your-pass";

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    //Handle WebSocket event
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    // attach AsyncWebSocket
    ws.onEvent(onEvent);
    server.addHandler(&ws);

    server.begin();
}

void loop()
{
}

#endif