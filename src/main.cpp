#include <Arduino.h>
#include <WiFiS3.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

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

void processLogic()
{
    lcdControl(lcd, 0, 0, "Example status");
}

void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 2);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    processLogic();

    delay(1000);
}
