#include <Arduino.h>
#include "BlinkingLED.h"

const int ledPin = 2;

BlinkingLED blinkingLED(ledPin, 500); // Blink the built-in LED every 500 ms

void setup()
{
  Serial.begin(9600);
  blinkingLED.begin();
}

void loop()
{
  // Do other tasks in the loop
  Serial.println("Main loop running...");
  //delay(1000);
}