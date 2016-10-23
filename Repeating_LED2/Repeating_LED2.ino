int ledPin = 8;
int buttonPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ledPin, digitalRead(buttonPin));
}
