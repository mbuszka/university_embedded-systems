#include <PCM.h>

#include "data.h"

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  if (analogRead(1) < 500) {
    setSampleRate(random(6000, 1000));
    setAmp(((double) random(5000, 1500)) / 1000.0 );
    startPlayback(sample, sizeof(sample));
    delay(1000);
  }
}
