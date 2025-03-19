#include <Arduino.h>
#include "smoke_sensor.h"
#include "config.h"

void initSmokeSensor()
{
    pinMode(SMOKE_SENSOR_PIN_A, INPUT);
}

bool isSmokeDetected()
{
    return analogRead(SMOKE_SENSOR_PIN_A) > SMOKE_THRESHOLD;
}