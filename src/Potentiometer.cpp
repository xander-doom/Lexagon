#include <Arduino.h>
#include "Potentiometer.h"

void Potentiometer::init(int pin)
{
    _pin = pin;

    // Read the current state of the potentiometer to init the ring buffer
    reading = analogRead(_pin);

    debounceThreshold = 8; // Change required to update the state
    levels = 256; // Number of levels of the potentiometer
}
void Potentiometer::update()
{
    reading = analogRead(_pin);

    // If the reading is substantially different from the last time value was set, update the level
    if (reading > readingWhenValueSet + debounceThreshold || reading < readingWhenValueSet - debounceThreshold)
    {
        level = reading * levels / 1024;
        readingWhenValueSet = reading;
    }
}

int Potentiometer::value()
{
    return level;
}