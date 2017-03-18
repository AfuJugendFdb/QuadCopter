int trigPin = 13;
int echoPin = 12;

void setup() {
  Serial.begin(115200);

}

void loop() {
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

  Serial.println(cm, DEC);

  delay(100);

}

long MicrosecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

