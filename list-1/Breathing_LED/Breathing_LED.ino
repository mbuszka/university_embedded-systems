
double pi = 3.1415;
//PIN ids
int red_pin = 11;
int green_pin = 10;
int blue_pin = 9;

//Current color
int red;
int green;
int blue;

int fadeAmount = 2; //step
int brightness = 0;
int interval = 11;

void setup() // this function runs once when the sketch starts up
{
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);  
  randColor();
}

void loop() // this function runs repeatedly after setup() finishes
{
  brightness += fadeAmount;
  setColor(red, green, blue, brightness);
  delay(interval);
  
  if (brightness >= 255)
    fadeAmount *= -1;
  if (brightness <= 0) {
    randColor();
    fadeAmount *= -1;
  }
  
}

void setColor(int red, int green, int blue, int brightness) {
  analogWrite(red_pin, 255 - red * sin(0.5 * pi * brightness / 255));
  analogWrite(green_pin, 255 - green *  sin(0.5 * pi * brightness / 255));
  analogWrite(blue_pin, 255 - blue * sin(0.5 * pi * brightness / 255));
}

void randColor() {
  red = random(255);
  green = random(255);
  blue = random(255);
}

