#include <Debouncer.h>

Debouncer::Debouncer(int p, int del) {
  pinMode(p, INPUT);
  pin = p;
  delay = del;
  debounce = Stopwatch();
  debounce.start();
}

int Debouncer::debouncedRead() {
  reading = digitalRead(pin);
  if (reading != prevReading) {
    debounce.reset();
  }
  if (debounce.elapsed() > delay) {
    state = reading;
  }
  prevReading = reading;
  return state;
}
