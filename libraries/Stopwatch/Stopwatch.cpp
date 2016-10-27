#include "Stopwatch.h"

unsigned int Stopwatch::start() {
  return _started = millis();
}

unsigned int Stopwatch::stop() {
  return _elapsed += millis() - _started;
}

unsigned int Stopwatch::reset() {
  unsigned int e = stop();
  _elapsed = 0;
  return e;
}

unsigned int Stopwatch::elapsed() {
  return millis() - _started + _elapsed;
}
