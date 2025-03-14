#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "config.h"

#if __has_include("wifi_settings.h")
#include "wifi_settings.h"
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#endif

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#ifdef WIFI_ENABLED
WiFiClient client;
WiFiUDP udpClient;
NTPClient ntpClient(udpClient, NTP_SERVER, 3600.0);
#endif

const float smokeThreshold = 400.0;

void ledControl(uint8_t ledPin, uint8_t state)
{
    analogWrite(ledPin, state);
}

void lcdControl(LiquidCrystal lcd, uint8_t col, uint8_t row, String message)
{
    lcd.setCursor(col, row);
    lcd.print(message);
}

void buzzerControl(uint8_t buzzerPin, uint8_t state)
{
    analogWrite(buzzerPin, state);
}

#ifdef WIFI_ENABLED
void wifiControl(const char* ssid, const char* password)
{
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    Serial.print("Connected to ");
    Serial.println(ssid);
}

void setupNTP()
{
    ntpClient.begin();
}

String getCurrentFormattedTime()
{
    ntpClient.update();
    return ntpClient.getFormattedTime();
}
#endif

void processLogic()
{
    lcdControl(lcd, 0, 0, "Example status");

#ifdef WIFI_ENABLED
    ntpClient.update();
    uint8_t currentHour = ntpClient.getHours();

    if (currentHour == TURN_ON_HOUR)
    {
        ledControl(LED_PIN, HIGH);
        lcdControl(lcd, 0, 0, "LED ON");
    }
    else if (currentHour == TURN_OFF_HOUR)
    {
        ledControl(LED_PIN, LOW);
        lcdControl(lcd, 0, 0, "LED OFF");
    }
#endif
}

void gasAlarm()
{
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN); // Read gas sensor value
    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel); // Values for debugging

    if (smokeLevel > smokeThreshold)
    {
        Serial.println(" Warning! Smoke detected!");
        buzzerControl(BUZZER_PIN, LOW);

    }
    else
    {
        Serial.println(" No Smoke Detected.");
        buzzerControl(BUZZER_PIN, HIGH);
    }
}

void gasLight()
{
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN); // Read gas sensor value

    if (smokeLevel > smokeThreshold)
    {
        ledControl(LED_PIN, LOW);
    }
    else
    {
        ledControl(LED_PIN, HIGH);
    }

    delay(1000);
}


void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 2);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

#ifdef WIFI_ENABLED
    wifiControl(WIFI_SSID, WIFI_PASSWORD);
    setupNTP();
#endif
}

void loop()
{
    processLogic();

    delay(1000);
}
