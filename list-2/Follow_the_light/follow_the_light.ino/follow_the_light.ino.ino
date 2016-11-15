
const int pins[4] = {2, 4, 5, 3}; //led pins
const int x_pin = A0; //joystick x
const int y_pin = A1; //joystick y

int curr_dir;
int pointRatio;

unsigned long long time_from_start = 0; //time at game start
unsigned long long time1; 
unsigned long long  time2;
unsigned long long max_time; //one game duration

int delta = 200; //treeshold
int epsilon = 100; //tolerance

int x = 0;
int y = 0;

bool in_start = true;
int anti_cheat_epsilon = 100;

bool won = true; 
int started = 0; //game started?

unsigned int points = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for(int i = 0; i < 4; i++)
    pinMode(pins[i], OUTPUT);
}

void loop() {
  if (started) {
    if(won) {
      curr_dir = random(0, 4);
      digitalWrite(pins[curr_dir], HIGH);
      won = false;
      time1 = millis();
      in_start = false;
    }
    
    if (millis() - time_from_start >= max_time) {
      Serial.println("Zakończono rozgrywkę. Wynik: ");
      Serial.println(points);  
      started = 0;
      digitalWrite(pins[curr_dir], LOW);
      points = 0;
      won = 1;
    }
    
    x = analogRead(x_pin);
    y = analogRead(y_pin);
    if (x <= 512 + anti_cheat_epsilon && x >= 512 - anti_cheat_epsilon && y <= 512 + anti_cheat_epsilon && y >= 512 - anti_cheat_epsilon)
      in_start = true;
      
    if(in_start && get_direction(x,y) == curr_dir) {
      digitalWrite(pins[curr_dir], LOW);
      won = 1;
      time2 = millis(); 
      points += get_points(time2 - time1);
      //Serial.print("Liczba punktów: ");
      //Serial.println(points);
    }
  } else {
    if(Serial.available()) {
      max_time = Serial.parseInt() * 1000;
      started = 1;  
      time_from_start = millis(); 
    }
  }
}

int get_direction(int x, int y) {
  if (x > 512 + delta && y < 512 + epsilon && y > 512 - epsilon)
    return 1;
  if (x < 512 - delta && y < 512 + epsilon && y > 512 - epsilon)
    return 3;
  if (y > 512 + delta && x < 512 + epsilon && x > 512 - epsilon)
    return 0;
  if (y < 512 - delta && x < 512 + epsilon && x > 512 - epsilon)
    return 2;
  else
    return -1;
}

int get_points(int time_delta) {
  if (1000 - time_delta > 0)
    return 0.01 * (1000 - time_delta);
  return 0;
}

