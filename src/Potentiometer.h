#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer
{
public:
  void init(int pin);
  void update();
  int value();

private:
  int _pin; // I/O Pin of the potentiometer
  int level; // Current level of the potentiometer
  int levels; // Number of levels of the potentiometer
  int debounceThreshold; // Threshold for a movement to be considered a change in level
  int reading, readingWhenValueSet; // For calculating the average
};

#endif