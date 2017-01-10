#include <Arduino.h>
#include "Stopwatch.h"

#define ROW_COUNT 30

int led[ROW_COUNT][5] = { 
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  HIGH, LOW,  HIGH,
  LOW,  LOW,  HIGH, LOW,  HIGH,
  LOW,  LOW,  HIGH, LOW,  HIGH,
  LOW,  LOW,  HIGH, LOW,  HIGH,
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  LOW,  LOW,  HIGH, LOW,  LOW,
  HIGH, HIGH, HIGH, HIGH, HIGH,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
  LOW,  LOW,  LOW, LOW,  LOW,
                   };

int row = 0;

unsigned int latency = 50;



Stopwatch sw;
Stopwatch delayS;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // pinMode(A0, INPUT);
  Serial.begin(9600);
  sw.start();
}

void loop() {
  char c = Serial.read();
  if (c == ',') {
    latency += 5;
  } else if (c == '.') {
    latency -= 5;
  } else if (c == 'p') {
    Serial.println(latency);
  }/*
  if (digitalRead(A0) == HIGH) {
    delayS.start();
    Serial.println('a');
  } else {
    latency = delayS.elapsed();
    delayS.reset();
    delayS.stop();
  }*/
  if (sw.elapsed() > latency / ROW_COUNT) {
    sw.reset();
    row ++;
    row %= ROW_COUNT;
    for (int i = 0; i < 5; i++) {
      digitalWrite(2+i, led[row][4-i]);
    }
  }
}
