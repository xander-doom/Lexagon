#include <Arduino.h>
#include "Rotary.h"

void Rotary::init(int PinSW, int PinCLK, int PinDT)
{
    OldCLK = -1;
    OldDT = -1;
    NewCLK = -1;
    NewDT = -1;

    counter = 0;

    TimeOfLastDebounce = 0;
    DelayofDebounce = 0.05;

    // Put current pins state in variables
    _PinSW = PinSW;
    _PinCLK = PinCLK;
    _PinDT = PinDT;

    // Set the Switch pin to use Arduino PULLUP resistors
    pinMode(PinSW, INPUT_PULLUP);

    // Initalize old values
    OldCLK = digitalRead(_PinCLK);
    OldDT = digitalRead(_PinDT);
}

void Rotary::update()
{
    // If enough time has passed check the rotary encoder
    if ((millis() - TimeOfLastDebounce) > DelayofDebounce)
    if (true)
    {
        //TimeOfLastDebounce = millis(); // Set variable to current millis() timer

        NewCLK = digitalRead(_PinCLK);
        NewDT = digitalRead(_PinDT);

        if ((OldCLK == 0 && OldDT == 1 && NewCLK == 1 && NewDT == 0) ||
            (OldCLK == 1 && OldDT == 0 && NewCLK == 0 && NewDT == 1) ||
            (OldCLK == 1 && OldDT == 1 && NewCLK == 0 && NewDT == 1) ||
            (OldCLK == 0 && OldDT == 0 && NewCLK == 1 && NewDT == 0))
            counter--;

        else if ((OldCLK == 0 && OldDT == 1 && NewCLK == 1 && NewDT == 1) ||
                 (OldCLK == 1 && OldDT == 0 && NewCLK == 0 && NewDT == 0) ||
                 (OldCLK == 1 && OldDT == 1 && NewCLK == 0 && NewDT == 0) ||
                 (OldCLK == 0 && OldDT == 0 && NewCLK == 1 && NewDT == 1))
            counter++;

        OldCLK = NewCLK;
        OldDT = NewDT;
    }
}

int Rotary::value()
{
    return counter/2;
}

int Rotary::buttonvalue()
{
    return digitalRead(_PinSW);
}

void Rotary::reset()
{
    counter = 0;
}