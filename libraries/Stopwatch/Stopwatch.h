#ifndef Stopwatch_h
#define Stopwatch_h

#include "Arduino.h"

class Stopwatch{
  private :
    unsigned int _elapsed;
    unsigned int _started;
  public :
    unsigned int start();
    unsigned int stop();
    unsigned int reset();
    unsigned int elapsed();
};

#endif
