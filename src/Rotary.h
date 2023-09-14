#ifndef ROTARY_H
#define ROTARY_H

class Rotary
{
private:
  // Rotary Encoder Module connections
  int _PinSW;  // Rotary Encoder Switch
  int _PinCLK; // CLOCK signal
  int _PinDT;  // DATA signal

  volatile int OldCLK, OldDT;
  volatile int NewCLK, NewDT;

  volatile int counter; // Store current counter value

  // Variables to debounce Rotary Encoder
  long TimeOfLastDebounce;
  int DelayofDebounce;

public:
  void init(int PinSW, int PinCLK, int PinDT);
  void update();
  int value();
  int buttonvalue();
  void reset();
};

#endif