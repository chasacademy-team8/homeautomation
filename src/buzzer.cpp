#include <Arduino.h>
#include "buzzer.h"
#include "config.h"

void initBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

void soundBuzzer()
{
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
}