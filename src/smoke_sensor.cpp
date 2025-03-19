#include <Arduino.h>
#include "smoke_sensor.h"
#include "config.h"

void initSmokeSensor()
{
    pinMode(SMOKE_SENSOR_PIN, INPUT);
}

bool isSmokeDetected()
{
    return analogRead(SMOKE_SENSOR_PIN) > SMOKE_THRESHOLD;
}