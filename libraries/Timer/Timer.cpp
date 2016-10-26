#include "Timer.h"

unsigned int Timer::start() {
  return _started = millis();
}

unsigned int Timer::stop() {
  return _elapsed += millis() - _started;
}

unsigned int Timer::reset() {
  unsigned int e = stop();
  _elapsed = 0;
  return e;
}

unsigned int Timer::elapsed() {
  return millis() - _started + _elapsed;
}
