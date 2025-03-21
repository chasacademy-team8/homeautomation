#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "buzzer.h"
#include "config.h"
#include "display.h"
#include "led.h"
#include "matrix.h"
#include "smoke_sensor.h"

#include "wifi_settings.h"
#include "wifi_handler.h"

WiFiClient client;
WiFiUDP udpClient;
NTPClient ntpClient(udpClient, NTP_SERVER, 3600.0);

uint16_t ambientLight = 0;
uint8_t lightBrightness = 0;
long previousLightBrightness = -1;
uint8_t currentHour = 0;
bool smokeAlarm = false;

void setup()
{
    Serial.begin(9600);

    setupWifi(WIFI_SSID, WIFI_PASSWORD);

    initDisplay();
    initMatrix();
    initBuzzer();
    initLED();
    initSmokeSensor();
}

void loop()
{
    ntpClient.update();
    String getCurrentTime = ntpClient.getFormattedTime();

    if (!smokeAlarm)
    {
        showHomeScreen(getCurrentTime);
    }

#if DEBUG
    Serial.print("Smoke sensor value: ");
    Serial.println(analogRead(SMOKE_SENSOR_PIN_A));
#endif

    if (isSmokeDetected())
    {
        if (!smokeAlarm)
        {
            Serial.println("Smoke detected!");
            smokeAlarm = true;
            showStatusMessage("SMOKE DETECTED!");
        }
        controlLED(255);
        soundBuzzer();
    }
    else if (smokeAlarm)
    {
        Serial.println("Smoke cleared!");
        smokeAlarm = false;
    }

    if (smokeAlarm)
    {
        delay(1000);
        return;
    }

    currentHour = ntpClient.getHours();
    if (currentHour >= TURN_ON_HOUR && currentHour < TURN_OFF_HOUR)
    {
        ambientLight = analogRead(PHOTORESISTOR_PIN);

#if DEBUG
        Serial.print("Diode sensor value: ");
        Serial.println(ambientLight);
#endif

        if (ambientLight < 256)
        {
            lightBrightness = LIGHT_HIGH;
            if (lightBrightness != previousLightBrightness)
            {
                Serial.println("HIGH LIGHT");
                showStatusMessage("HIGH LIGHT");
            }
        }
        else if (ambientLight < 512)
        {
            lightBrightness = LIGHT_MEDIUM;
            if (lightBrightness != previousLightBrightness)
            {
                Serial.println("MEDIUM LIGHT");
                showStatusMessage("MEDIUM LIGHT");
            }
        }
        else if (ambientLight < 768)
        {
            lightBrightness = LIGHT_LOW;
            if (lightBrightness != previousLightBrightness)
            {
                Serial.println("LOW LIGHT");
                showStatusMessage("LOW LIGHT");
            }
        }
        else
        {
            lightBrightness = LIGHT_OFF;
            if (lightBrightness != previousLightBrightness)
            {
                Serial.println("LIGHT OFF");
                showStatusMessage("LIGHT OFF");
            }
        }

        if (lightBrightness != previousLightBrightness)
        {
            previousLightBrightness = lightBrightness;
            controlLED(lightBrightness);
        }
    }
    else
    {
        controlLED(0);
    }

    delay(1000);
}