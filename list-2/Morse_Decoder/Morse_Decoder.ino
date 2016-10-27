#include <Stopwatch.h>

Stopwatch timer;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  timer.start();
}

void loop() { 
  if(timer.elapsed()%1000 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }

}
