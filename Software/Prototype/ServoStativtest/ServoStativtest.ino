#include <Servo.h>

Servo horizontal;
Servo vertikal;

int trigPin = 13;
int echoPin = 12;

void setup() {
  horizontal.attach(10);
  vertikal.attach(11);
  horizontal.write(0);
  vertikal.write(0);
  Serial.begin(115200);
}

void loop() {
  delay(500);
  for(uint8_t vert=0; vert<90; vert=vert+5) {
    vertikal.write(vert);
    for(uint8_t hor=0; hor<180; hor=hor+5) {
      horizontal.write(hor);
      delay(500);
      long duration, cm;
      pinMode(trigPin, OUTPUT);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      cm = MicrosecondsToCentimeters(duration);
      Serial.print(hor);
      Serial.print(",");
      Serial.print(vert);
      Serial.print(",");
      Serial.println(cm, DEC);
      
    }
  }
}

long MicrosecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
