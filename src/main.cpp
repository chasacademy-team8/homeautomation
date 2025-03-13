#include <Arduino.h>

int photoDiodePin = A0; // used for reading
int photoDiodeValue = 0; 

// GND > Potentiometer > resistor > > A0 > potentiometer > 5V 

void photoDiodeReadValue();

void setup() {
  Serial.begin(9600);  
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
}
