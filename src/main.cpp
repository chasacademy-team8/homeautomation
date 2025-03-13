#include <Arduino.h>
#include <WiFiS3.h>
#include <LiquidCrystal.h>
#include "config.h"

void ledControl(uint8_t ledPin, uint8_t state)
{
    analogWrite(ledPin, state);
}

void processLogic()
{
}

void setup()
{
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    processLogic();

    delay(1000);
}
