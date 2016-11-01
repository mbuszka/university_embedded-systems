#include <Stopwatch.h>
#include <Morse.h>

#define DEBOUNCE_DELAY 20

Stopwatch sw;
Stopwatch debounce;
Morse dict;

static unsigned int dot = 200;
static unsigned int dash = 3 * dot;
int prevReading = LOW;
int state;
int code = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
  debounce.start();
}

void onEdge(int state) {
  unsigned int elapsed = sw.reset();
  if (state == HIGH) {
    sw.start();
  } else {
    if (elapsed < dot) {
      Serial.print('.');
      code *= 2;
    } else {
      Serial.print('-');
      code *= 2;
      code ++;
    }
    sw.start();
  }
}

void loop() { 
  int reading = digitalRead(9);
  if (reading != prevReading) {
    debounce.reset();
  }
  if (debounce.elapsed() > DEBOUNCE_DELAY) {
    if (reading != state) {
      state = reading;
      onEdge(state);
    }
  }
  if (state == LOW && sw.elapsed() > dash) {
    sw.stop();
    sw.reset();
    Serial.println(dict.decode(code));
    code = 1;
  }
  prevReading = reading;
}
