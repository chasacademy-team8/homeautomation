#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "wifi_handler.h"

void setupWifi(const char* ssid, const char* password)
{
    byte attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < WIFI_ATTEMPTS)
    {
        Serial.print("Connecting to ");
        showStatusMessage("Connecting to WiFi");
        Serial.println(ssid);

        WiFi.begin(ssid, password);

        delay(1000);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("Connected to ");
        Serial.println(ssid);
        showStatusMessage("Connected to WiFi");
    }
    else
    {
        Serial.println("Failed to connect to WiFi");
        showStatusMessage("Failed to connect to WiFi");
    }
}