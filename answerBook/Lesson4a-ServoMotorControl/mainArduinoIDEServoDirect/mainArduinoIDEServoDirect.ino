#include <ESP32Servo.h>

static const int servoPin = 26; // Physical pin 5, GPIO26 aka A0

Servo servo1;

void setup() {

  Serial.begin(115200);
  servo1.attach(servoPin);
}

void loop() {
  for(int posDegrees = 70; posDegrees <= 110; posDegrees++) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for(int posDegrees = 110; posDegrees >= 70; posDegrees--) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}