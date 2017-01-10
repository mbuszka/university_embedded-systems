#include <Stopwatch.h>

Stopwatch sw;

int ledNpin = 1;
int ledSpin = 2;
int ledEpin = 3;
int ledWpin = 4;

void setup() {
  pinMode(ledNpin, OUTPUT);
  pinMode(ledSpin, OUTPUT);
  pinMode(ledEpin, OUTPUT);
  pinMode(ledWpin, OUTPUT);
  sw.start();
}
int n = 0;

void loop() {
  if (sw.elapsed() > 500) {
    sw.reset();
    digitalWrite(n+1, LOW);
    n++;
    n = n % 4;
  } else {
    digitalWrite(n+1, HIGH);
  }
}
