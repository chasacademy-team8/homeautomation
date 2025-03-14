#include <Arduino.h>


int gasPin = A0; 
int b2Pin = 0; 
int gasLevel = 0;  



void setup() {
  Serial.begin(9600);
}

void loop() {
  readGasValue();
}

void readGasValue()
{
  gasLevel = analogRead(gasPin); 
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);  
  
  delay(1000);  
}
