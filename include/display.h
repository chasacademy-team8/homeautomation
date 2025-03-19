#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal.h>

void initDisplay();
void showHomeScreen(const String &currenTime);
void showStatusMessage(const String& message);
void showCustomMessage(const String& message, uint8_t col, uint8_t row, bool clear = true);

#endif