

#include "config.hpp"

#ifndef DEVMODE
#include <Arduino.h>
#include "coreapp/coreapp.hpp"

CoreApp g_coreapp = CoreApp();
bool CoreApp::m_shouldsaveconfig;

void setup()
{
    g_coreapp.setup();
}

void loop()
{
    g_coreapp.loop();
}

#endif
