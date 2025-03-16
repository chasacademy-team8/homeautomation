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

const float smokeThreshold = 200.0;
const int wifiAttempts = 3;

void ledControl(uint8_t ledPin, int state);
void lcdControl(LiquidCrystal lcd, uint8_t col, uint8_t row, uint8_t clear, String message);
void buzzerControl(uint8_t buzzerPin, int state);
#ifdef WIFI_ENABLED
void wifiControl(const char* ssid, const char* password);
void setupNTP();
#endif
void gasAlarm();
void gasLight();
void processLogic();

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

    lcdControl(lcd, 0, 0, 1, "Home Automation");
}

void loop()
{
    gasAlarm();

#ifdef WIFI_ENABLED
    ntpClient.update();
    uint8_t currentHour = ntpClient.getHours();

    if (currentHour == TURN_ON_HOUR)
    {
        ledControl(LED_PIN, 255);
        lcdControl(lcd, 0, 0, 1, "LED ON");
    }
    else if (currentHour == TURN_OFF_HOUR)
    {
        ledControl(LED_PIN, 0);
        lcdControl(lcd, 0, 0, 1, "LED OFF");
    }
#endif
        delay(1000);
}

void ledControl(uint8_t ledPin, int state)
{
    analogWrite(ledPin, state);
}

void lcdControl(LiquidCrystal lcd, uint8_t col, uint8_t row, uint8_t clear, String message)
{
    if (clear)
    {
        lcd.clear();
    }
    lcd.setCursor(col, row);
    lcd.print(message);
}

void buzzerControl(uint8_t buzzerPin, int state)
{
    analogWrite(buzzerPin, state);
}

#ifdef WIFI_ENABLED
void wifiControl(const char* ssid, const char* password)
{
    Serial.print("Connecting to ");
    lcdControl(lcd, 0, 0, 1, "Connecting to ");
    lcdControl(lcd, 0, 1, 0, ssid);
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    uint8_t attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < wifiAttempts)
    {
        delay(1000);
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("Connected to ");
        Serial.println(ssid);
        lcdControl(lcd, 0, 0, 1, "Connected to ");
        lcdControl(lcd, 0, 1, 0, ssid);
    }
    else
    {
        Serial.println("Failed to connect to WiFi");
    }
}

void setupNTP()
{
    ntpClient.begin();
}
#endif

void gasAlarm()
{
    static bool alarmActive = false;
    static unsigned long lastCheckTime = 0;
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN); // Read gas sensor value
    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel); // Values for debugging

    if (smokeLevel > smokeThreshold)
    {
        if (!alarmActive)
        {
            alarmActive = true;
            buzzerControl(BUZZER_PIN, LOW);
            ledControl(LED_PIN, 255);
            lcdControl(lcd, 0, 0, 1, "Smoke Detected");
            lcdControl(lcd, 0, 1, 0, "Alarm ON");
        }

        // Check if smoke level is still high after 5 seconds
        if (millis() - lastCheckTime >= 5000)
        {
            lastCheckTime = millis();
            smokeLevel = analogRead(SMOKE_SENSOR_PIN);
            Serial.print("warning! Smoke detected! ");
            Serial.println(smokeLevel);
        }
    }
    else if (alarmActive)
    {
        alarmActive = false;
        Serial.println(" No Smoke Detected.");
        buzzerControl(BUZZER_PIN, HIGH);
        ledControl(LED_PIN, 0);
        lcdControl(lcd, 0, 0, 1, "No Smoke Detected");
        lcdControl(lcd, 0, 1, 0, "Alarm OFF");
    }
}

void gasLight()
{
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN); // Read gas sensor value

    if (smokeLevel > smokeThreshold)
    {
        ledControl(LED_PIN, 0);
    }
    else
    {
        ledControl(LED_PIN, 255);
    }

    delay(1000);
}
