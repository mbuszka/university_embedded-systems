#include "Stopwatch.h"

unsigned int Stopwatch::start() {
  _running = true;
  return _started = millis();
}

unsigned int Stopwatch::stop() {
  _running = false;
  return _elapsed += millis() - _started;
}

unsigned int Stopwatch::reset() {
  unsigned int e;
  if (_running) {
    e = stop();
    start();
  } else {
    e = _elapsed;
  }
  _elapsed = 0;
  return e;
}

unsigned int Stopwatch::elapsed() {
  if (_running) {
    return millis() - _started + _elapsed;
  } else {
    return _elapsed;
  }
}
