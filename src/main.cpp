#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
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
ArduinoLEDMatrix matrix;

#ifdef WIFI_ENABLED
WiFiClient client;
WiFiUDP udpClient;
NTPClient ntpClient(udpClient, NTP_SERVER, 3600.0);
#endif

const float smokeThreshold = 200.0;
const uint8_t wifiAttempts = 3;
bool alarmActive = false;

void ledControl(uint8_t ledPin, uint8_t state);
void lcdControl(uint8_t col, uint8_t row, String message, bool clear = false);
void buzzerControl(uint8_t buzzerPin, uint8_t state);
#ifdef WIFI_ENABLED
void wifiControl(const char* ssid, const char* password);
void setupNTP();
#endif
void gasAlarm();
void gasLight();

void setup()
{
    Serial.begin(9600);

    matrix.loadSequence(LEDMATRIX_ANIMATION_HEARTBEAT_LINE);
    matrix.begin();
    matrix.play(true);

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
    gasAlarm();

#ifdef WIFI_ENABLED
    ntpClient.update();
    uint8_t currentHour = ntpClient.getHours();
    if (!alarmActive)
    {
        lcdControl(0, 0, "Home Automation", 1);
        lcdControl(0, 1, "Time: " + ntpClient.getFormattedTime());
    }

    if (currentHour == TURN_ON_HOUR)
    {
        ledControl(LED_PIN, 255);
        lcdControl(0, 0, "LED ON", 1);
    }
    else if (currentHour == TURN_OFF_HOUR)
    {
        ledControl(LED_PIN, 0);
        lcdControl(0, 0, "LED OFF", 1);
    }
#endif
    delay(1000);
}

void ledControl(uint8_t ledPin, uint8_t state)
{
    analogWrite(ledPin, state);
}

void lcdControl(uint8_t col, uint8_t row, String message, bool clear)
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
    lcdControl(0, 0, "Connecting to ", 1);
    lcdControl(0, 1, ssid);
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
        lcdControl(0, 0, "Connected to ", 1);
        lcdControl(0, 1, ssid);
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
    //static unsigned long lastCheckTime = 0;
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN);
    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel);

    if (smokeLevel > smokeThreshold)
    {
        if (!alarmActive)
        {
            alarmActive = true;
            buzzerControl(BUZZER_PIN, LOW);
            ledControl(LED_PIN, 255);
            lcdControl(0, 0, "Smoke Detected", 1);
            lcdControl(0, 1, "Alarm ON");
        }
    }
    else if (alarmActive)
    {
        alarmActive = false;
        Serial.println("No Smoke Detected.");
        buzzerControl(BUZZER_PIN, HIGH);
        ledControl(LED_PIN, 0);
        lcdControl(0, 0, "No Smoke Detected", 1);
        lcdControl(0, 1, "Alarm OFF");
        delay(1000);
    }
}

void gasLight()
{
    float smokeLevel = analogRead(SMOKE_SENSOR_PIN);

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
