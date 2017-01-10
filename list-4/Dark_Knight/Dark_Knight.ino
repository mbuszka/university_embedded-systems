#include <PCM.h>

#include "sound.h"

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void scanner() {
  for (int i=2; i<9; i++) {
    digitalWrite(i, HIGH);
    delay(71);
    digitalWrite(i, LOW);
  }
  for (int i=8; i>1; i--) {
    digitalWrite(i, HIGH);
    delay(71);
    digitalWrite(i, LOW);
  }
}

void loop()
{
  startPlayback(sample, sizeof(sample));
  scanner();
}


