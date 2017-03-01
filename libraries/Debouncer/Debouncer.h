#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>
#include <Stopwatch.h>

class Debouncer {
private:
  int pin;
  int prevReading = LOW;
  int reading  = LOW;
  int state = LOW;
  int delay;
  Stopwatch debounce;
public:
  int debouncedRead();
  Debouncer(int, int);
};

#endif
