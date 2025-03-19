#include <Arduino.h>
#include "led.h"
#include "config.h"

void initLED()
{
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
}

void controlLED(uint8_t brightness)
{
    analogWrite(LED_PIN_1, brightness);
}