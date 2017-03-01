const int buzzer = 13;
const int t = 110;
const int N = 15;

#define ais 233
#define h 247
#define his 262
#define c 262
#define cis 277
#define d 294

int A[15] = {cis, d, cis, cis, d, cis, cis, d, cis, cis, cis, his, cis, cis, cis};
int B[15] = {h, c, h, h, c, h, h, c, h, h, h, ais, h, h, h};
int leds[4] = {5, 6, 9, 10};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

double z = -PI/2 - PI/4;
double s = 1;

void loop() {
  for (int p = 0; p < 2; p++) {
    for (int i = 0; i < 15; i++) {
      tone(buzzer, A[i], i != 0 ? t : 2*t);
      
      Serial.println(A[i]);
      
      int cnt = 1;
      if (i == 0) cnt = 2;
      for (int l = 0; l < cnt; l++) {
        for (int j = 0; j < 4; j++) {
          analogWrite(leds[j], 155 * max(sin(PI * j/3.0 + z), 0));
          //Serial.println(255 * max(sin(PI * j/4.0 + z), 0));
        }       
        z += PI*s/6;
        delay(1.2 * t);
      }
      if (i == 6) s *= -1;
    }
    s *= -1;
  }


  for (int p = 0; p < 2; p++)
  {
    for (int i = 0; i < 15; i++)
    {
      tone(buzzer, B[i], i != 0 ? t : 2*t);
      int cnt = 1;
      if (i == 0) cnt = 2;
      for (int l = 0; l < cnt; l++)
      {
        for (int j = 0; j < 4; j++)
        {
          analogWrite(leds[j], 155 * max(sin(PI * j/3.0 + z), 0));
        }
        z += PI*s/6;
        delay(1.2 * t);
      }
      if (i == 6) s *= -1;
    }
    s *= -1;
  }
}


