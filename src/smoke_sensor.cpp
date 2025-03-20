#include <Arduino.h>
#include "smoke_sensor.h"
#include "config.h"

//volatile bool smokeAlarm = false;

void initSmokeSensor()
{
    pinMode(SMOKE_SENSOR_PIN_A, INPUT);
    pinMode(SMOKE_SENSOR_PIN_D, INPUT);
    //attachInterrupt(digitalPinToInterrupt(SMOKE_SENSOR_PIN_D), smokeInterrupt, CHANGE);
}

bool isSmokeDetected()
{
    //return analogRead(SMOKE_SENSOR_PIN_A) > SMOKE_THRESHOLD;
    return digitalRead(SMOKE_SENSOR_PIN_D) == LOW;
}

void smokeInterrupt()
{
    Serial.println("Smoke interrupt detected");
    //smokeAlarm = true;
}

uint16_t getSmokeValue()
{
    return analogRead(SMOKE_SENSOR_PIN_A);
}