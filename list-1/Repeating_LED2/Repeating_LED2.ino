int ledPin = 8;
int buttonPin = 2;

bool timeline[1000];
int pos = 1;
int prev_state;

int curr_state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  for(int i=0; i < 1000; i++)
    timeline[i] = false;  
}

void loop() {
  delay(1);
  int state = digitalRead(buttonPin);
  if(timeline[pos]) {
    timeline[pos] = false;
    change_state();
  }
  if(state != prev_state) {
    timeline[pos] = true;
    prev_state = state;
  }
  pos = (pos + 1) % 1000;
}

void change_state() {
  if(curr_state == LOW) {
    digitalWrite(ledPin, HIGH);
    curr_state = HIGH;
  } else {
    digitalWrite(ledPin, LOW);
    curr_state = LOW;
  }
}
