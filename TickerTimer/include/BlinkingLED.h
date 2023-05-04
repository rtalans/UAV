#ifndef BLINKINGLED_H
#define BLINKINGLED_H

#include <Arduino.h>
#include "TickerTimer.h"

class BlinkingLED {
public:
    BlinkingLED(uint8_t pin, uint32_t intervalMs);
    void begin();

private:
    static void onTickerEvent(BlinkingLED* instance);
    void toggleLed();

    uint8_t ledPin;
    uint32_t interval;
    Ticker ticker;
};

#endif // BLINKINGLED_H
