#include "telnetbridge/telnetbrdige.hpp"

TelnetBridge::TelnetBridge(unsigned int a_port, size_t a_uartrxbuffersize, unsigned int a_boudrate)
{
    m_telnet_uptr = std::unique_ptr<WiFiServer>(new WiFiServer(a_port));

    Serial.setRxBufferSize(a_uartrxbuffersize);
    Serial.flush();
    Serial.begin(a_boudrate);
}

TelnetBridge::~TelnetBridge()
{
    m_telnet_uptr->stop();
}

void TelnetBridge::TelnetBridge::begin()
{
    m_telnet_uptr->begin();
    m_telnet_uptr->setNoDelay(true);
}

void TelnetBridge::sendToSerial(const std::vector<unsigned char> &a_data)
{
    Serial.write(a_data.data(), a_data.size());
}

void TelnetBridge::sendDataToNetPort(const std::vector<unsigned char> &a_data)
{
    if (m_telnetclient && m_telnetclient.connected())
    {
        m_telnetclient.write(a_data.data(), a_data.size());
    }
}

void TelnetBridge::sendStringToNetPort(const String &a_msg)
{
    if (m_telnetclient && m_telnetclient.connected())
    {
        m_telnetclient.println(a_msg.c_str());
    }
}

void TelnetBridge::loop()
{
    serialWatcher();
    telnetWatcher();
}

void TelnetBridge::serialWatcher()
{
    //update current millies

    if (isHaveClient())
    {
        size_t rxlen = Serial.available();
        if (rxlen > 0)
        {
            uint8_t sbuf[rxlen];
            Serial.readBytes(sbuf, rxlen);
            m_telnetclient.write(sbuf, rxlen);
        }
    }
}

void TelnetBridge::telnetWatcher()
{
    if (m_telnet_uptr->hasClient())
        acceptConnection();
    else if (isHaveClient())
        manageConnected();
}

void TelnetBridge::acceptConnection()
{
    if (isHaveClient())
        m_telnetclient.stop();

    m_telnetclient = m_telnet_uptr->available();
}

void TelnetBridge::manageConnected()
{
    size_t rxlen = m_telnetclient.available();
    if (rxlen > 0)
    {
        uint8_t sbuf[rxlen];
        m_telnetclient.readBytes(sbuf, rxlen);
        Serial.write(sbuf, rxlen);
    }
}