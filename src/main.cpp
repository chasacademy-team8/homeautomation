#include <Arduino.h>

int pirPin = 2; 
int ledPin = 13; 

void setup() {
  pinMode(pirPin, INPUT);  
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);     
}

void loop() {
  readMotion();
}

// Reads the motion from a Pir Sensor turning a led light either on or off
void readMotion()
{
  delay(500); // just a small delay, can be removed
  int motionDetected = digitalRead(pirPin); 
  if (motionDetected == HIGH) { 
    digitalWrite(ledPin, HIGH); 
    Serial.println("Motion Detected!"); 
  } else {  
    digitalWrite(ledPin, LOW);  
  }
}