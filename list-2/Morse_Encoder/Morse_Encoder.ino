const int outPin = 4;
const int beepPin = 9;

const int translation_table[36][5] {
  {0, 1, -1, -1, -1},   //A
  {1, 0, 0, 0, -1}, //B
  {1, 0, 1, 0, -1}, //C
  {1, 0, 0, -1, -1}, //D
  {1, -1, -1, -1, -1}, //E
  {0, 0, 1, 0, -1}, //F
  {1, 1, 0, -1, -1}, //G
  {0, 0, 0, 0, -1}, //H
  {0, 0, -1, -1, -1}, //I
  {0, 1, 1, 1, -1}, //J
  {1, 0, 1, -1, -1}, //K
  {0, 1, 0, 0, -1}, //L
  {1, 1, -1, -1, -1}, //M
  {1, 0, -1, -1, -1}, //N
  {1, 1, 1, -1, -1}, //O
  {0, 1, 1, 0, -1}, //P
  {1, 1, 0, 1, -1}, //Q
  {0, 1, 0, -1, -1}, //R
  {0, 0, 0, -1, -1}, //S
  {1, -1, -1, -1, -1}, //T
  {0, 0, 1, -1, -1}, //U
  {0, 0, 0, 1, -1}, //V
  {0, 1, 1, -1, -1}, //W
  {1, 0, 0, 1, -1}, //X
  {1, 0, 1, 1, -1}, //Y
  {1, 1, 0, 0, -1}, //Z
  {1, 1, 1, 1, 1}, //0
  {0, 1, 1, 1, 1}, //1
  {0, 0, 1, 1, 1}, //2
  {0, 0, 0, 1, 1}, //3
  {0, 0, 0, 0, 1}, //4
  {0, 0, 0, 0, 0}, //5
  {1, 0, 0, 0, 0}, //6
  {1, 1, 0, 0, 0}, //7
  {1, 1, 1, 0, 0}, //8
  {1, 1, 1, 1, 0}}; //9

const int unit = 200;
const int freq = 440;

void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
}

void loop() {
  String buff = Serial.readStringUntil('\n');
  Serial.println(buff);
  for(int i=0; i < buff.length(); i++) {
    if (buff[i] == ' ') {
      digitalWrite(outPin, LOW);
      noTone(beepPin);
      delay(7 * unit);
    } else {
      int index = buff[i] > '9' ? buff[i] - 'A' : buff[i] + 26 - '0';
      int curr;
      for(int j=0; (j < 5) && ((curr = translation_table[index][j]) != -1); j++) {
        //space between parts of the same letter:
        digitalWrite(outPin, LOW);
        noTone(beepPin);
        delay(unit);
        digitalWrite(outPin, HIGH);
        tone(beepPin, freq);
        if(curr == 0) 
          delay(unit);
        else 
          delay(3 * unit);
      }
      //space between letters:
      digitalWrite(outPin, LOW);
      noTone(beepPin);
      delay(3 * unit);
    }
  }
}

