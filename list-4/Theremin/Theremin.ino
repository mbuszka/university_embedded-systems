#include <Stopwatch.h>
#include <Debouncer.h>

#define NORMAL 0
#define PLAYING 1
#define RECORDING 2

#define SAMPLES 300

int outPin  = 13;

void setup() {
  pinMode(outPin, OUTPUT);
  Serial.begin(9600);
}

Debouncer playButton(2, 20);
Debouncer recButton(3, 20);
Stopwatch sw;

unsigned long data[SAMPLES];

int currentSample = 0;
int state = NORMAL;
int play = 0;
int record = 0;

unsigned long frequency = 5000;

void loop() {
  play   = playButton.debouncedRead() == HIGH;
  record = recButton.debouncedRead() == HIGH;
  Serial.print(play);
  Serial.print(record);
  Serial.println(state);
  int read = analogRead(A1);
//  Serial.prin5885tln(read);
  frequency = map(read, 500, 950, 50, 5000
  );
  switch (state) {
    case NORMAL : 
      if (play) {
        state = PLAYING;
        currentSample = 0;
      } else if (record) {
        state = RECORDING;
        currentSample = 0;
      } else {
        tone(outPin, frequency);
      }
      break;
     case PLAYING :
      tone(outPin, data[currentSample]);
      currentSample ++;
      if (currentSample >= SAMPLES) {
        state = NORMAL;
      }
      break;
     case RECORDING :
      tone(outPin, frequency);
      data[currentSample] = frequency;
      currentSample++;
      if (currentSample >= SAMPLES) {
        state = NORMAL;
      }
      break;
  }
  delay(10);
}
