#ifndef TELNETBRIDGE_HPP
#define TELNETBRIDGE_HPP

#include <Arduino.h>
#include <vector>
#include <memory>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <appdebug.hpp>

#define TELNETPORT 23
#define UART_DATA_TIMEOUT 50
#define MAXSENDBUFFERSIZE 1024
#define UARTMAXREADBUFFER 1024
#define DEFAULT_BOUDREATE 115200

class TelnetBridge
{
private:
    std::unique_ptr<WiFiServer> m_telnet_uptr;
    WiFiClient m_telnetclient;

public:
    TelnetBridge(unsigned int a_port = TELNETPORT, size_t a_uartrxbuffersize = UARTMAXREADBUFFER, unsigned int a_boudrate = DEFAULT_BOUDREATE);

    ~TelnetBridge();

    void begin();
    void sendToSerial(const std::vector<unsigned char> &a_data);
    void sendDataToNetPort(const std::vector<unsigned char> &a_data);
    void sendStringToNetPort(const String &a_msg);
    void loop();

protected:
    void serialWatcher();
    void telnetWatcher();
    void acceptConnection();
    void manageConnected();

private:
    inline bool isHaveClient()
    {
        return m_telnetclient && m_telnetclient.connected() ? true : false;
    };
};

#endif
