#include <Arduino.h>

int photoDiodePin = A0; // used for reading
int ledPin = 9; // needs to be 9 as it can PWM enabled
int photoDiodeValue = 0; 

// GND > Potentiometer > resistor > > A0 > potentiometer > 5V 

// 5V > Resistor > Led light > 9

void photoDiodeReadValue();

void setup() {
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);
}

void loop() {
  photoDiodeReadValue();
}

void photoDiodeReadValue() 
// used to read the electricity current flowing through photoDiodeReadValue
{
    photoDiodeValue = analogRead(photoDiodePin);  
  	Serial.println(photoDiodeValue);  
  	delay(500);  
  	setLedLight(photoDiodeValue);
}

// sets the led light brightness
void setLedLight(int photoDiodeValue)
{
  // formula to calculate brightness, where dark and high resistance equals low brightness
  int brightness = map(photoDiodeValue, 0, 1023, 0, 255);
  analogWrite(ledPin, brightness);  // Set LED brightness
}