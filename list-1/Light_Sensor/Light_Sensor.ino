
int ledPin = 9;
int sensorPin = A0;
int minPin = 4;
int maxPin = 2;

int currMin = 0;
int currMax = 1023;

int minState;
int maxState;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(maxPin, INPUT);
  pinMode(minPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = constrain(1023 - analogRead(sensorPin), currMin, currMax);
  maxState = digitalRead(maxPin);
  minState = digitalRead(minPin);
  char str[50];
  sprintf(str, "min=%d max=%d val=%d val_sent=%d", currMin, currMax, val, map(val, currMin, currMax, 0, 255));
  Serial.println(str);
  if (maxState == HIGH) { 
    currMax = val;
  //  currMin = 0;
  }
  if (minState == HIGH) {
    currMin = val;
  //  currMax = 1023;
  }
  analogWrite(ledPin, map(val, currMin, currMax, 0, 255));
}
