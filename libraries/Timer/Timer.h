#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer {
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
