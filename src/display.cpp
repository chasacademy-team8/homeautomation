#include <Arduino.h>
#include <LiquidCrystal.h>
#include "display.h"
#include "config.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void initDisplay()
{
    lcd.begin(16, 2);
    lcd.clear();
}

void showHomeScreen(const String &currentTime)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Home Automation");

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(currentTime);
}

void showStatusMessage(const String& message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status:");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void showCustomMessage(const String& message, uint8_t col, uint8_t row, bool clear)
{
    if (clear)
    {
        lcd.clear();
    }
    lcd.setCursor(col, row);
    lcd.print(message);
}