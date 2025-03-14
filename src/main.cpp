#include <Arduino.h>
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <NtpClient.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

WiFiClient client;
WiFiUDP udpClient;
NTPClient ntpClient(udpClient, NTP_SERVER, 3600.0);

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

void wifiControl(const char* ssid, const char* password)
{
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    Serial.print("Connected to ");
    Serial.println(ssid);
}

void setupNTP() {
    ntpClient.begin();
}

String getCurrentFormattedTime() {
    ntpClient.update();
    return ntpClient.getFormattedTime();
}

void processLogic()
{
    lcdControl(lcd, 0, 0, "Example status");

#if WIFI_ENABLED
    ntpClient.update();
    uint8_t currentHour = ntpClient.getHours();

    if (currentHour == TURN_ON_HOUR) {
        ledControl(LED_PIN, HIGH);
        lcdControl(lcd, 0, 0, "LED ON");
    } else if (currentHour == TURN_OFF_HOUR) {
        ledControl(LED_PIN, LOW);
        lcdControl(lcd, 0, 0, "LED OFF");
    }
#endif

}

void gasAlarm()
{
    float smokeLevel = analogRead(smokePin); // Read gas sensor value
    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel); // Values for debugging

    if (smokeLevel > smokeThreshold)
    {
        Serial.println(" Warning! Smoke detected!");
        digitalWrite(buzzerPin, LOW);
    }
    else
    {
        Serial.println(" No Smoke Detected.");
        digitalWrite(buzzerPin, HIGH);
    }
}

void gasLight()
{
    float smokeLevel = analogRead(smokePin);

    if (smokeLevel > smokeThreshold)
    {
        digitalWrite(ledPin, LOW);
    }
    else
    {
        digitalWrite(ledPin, HIGH);
    }

    delay(1000);
}


void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 2);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

#if WIFI_ENABLED
    wifiControl(client, WIFI_SSID, WIFI_PASSWORD);
    setupNTP();
#endif
}

void loop()
{
    processLogic();

    delay(1000);
}
