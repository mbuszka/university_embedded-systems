#include <Stopwatch.h>
#include <Morse.h>

#define DEBOUNCE_DELAY 2

Stopwatch sw;
Stopwatch debounce;
Morse dict;

static unsigned int dot = 3;
static unsigned int dash = 3 * dot;
int prevReading = LOW;
int state;
int code = 1;
int raw_read;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
  debounce.start();
}

void onEdge(int state) {
//  Serial.println(raw_read);
  unsigned int elapsed = sw.reset();
  if (state == HIGH) {
    sw.start();
  } else {
//    Serial.println(elapsed);
    if (elapsed < 2*dot) {
//       Serial.print('.');
      code *= 2;
    } else {
//       Serial.print('-');
      code *= 2;
      code ++;
    }
    sw.start();
  }
}

int reading;
int awaitingNewWord = 0;

void loop() {
  raw_read = analogRead(A1);
  reading = raw_read < 900 ? LOW : HIGH;
//  Serial.println(raw_read);
//  if (reading != prevReading) {
//    debounce.reset();
//  }
//  if (debounce.elapsed() > DEBOUNCE_DELAY) {
    if (reading != state) {
      state = reading;
      onEdge(state);
    }
//  }
  if (state == LOW && sw.elapsed() > dash) {
    sw.stop();
    sw.reset();
//    debounce.reset();
//    debounce.start();
    Serial.print(dict.decode(code));
    code = 1;
//    awaitingNewWord = 1;
  }
//  if (awaitingNewWord == 1 && debounce.elapsed() > 4*dot ) {
//    debounce.reset();
//    debounce.stop();
//    Serial.println();
//    awaitingNewWord = 0;
//  }
//  prevReading = reading;
}
