#include <Arduino.h>

const int smokePin = A0; // Analog pin for sensor
const int ledPin = 4;    // LED to indicate smoke presence
const int buzzerPin = 5; // Buzzer for an alarm

int smokeThreshold = 100; // Default threshold

void setup()
{
    pinMode(smokePin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);

    Serial.println("Gas Sensor Warming Up...");
    delay(2000); // Allow sensor to stabilize
}

void loop()
{
    gasAlarm();
    gasLight();
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
