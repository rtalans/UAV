#include "BlinkingLED.h"

BlinkingLED::BlinkingLED(uint8_t pin, uint32_t intervalMs)
    : ledPin(pin), interval(intervalMs) {
}

void BlinkingLED::begin() {
  pinMode(ledPin, OUTPUT);

  // Attach the static class method 'onTickerEvent' to the ticker event
  ticker.attach_ms(interval, onTickerEvent, this);
}

// Static function to be used as a callback
void BlinkingLED::onTickerEvent(BlinkingLED* instance) {
  instance->toggleLed();
}

void BlinkingLED::toggleLed() {
  // Toggle the LED state
  digitalWrite(ledPin, !digitalRead(ledPin));
}
