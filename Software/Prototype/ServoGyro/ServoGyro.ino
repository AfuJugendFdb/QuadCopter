#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"

Servo schwarz; //erzeuge servo-objekt
Servo blau;
Servo gross;
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;


void setup() {
  schwarz.attach(9); //servo an pin9
  blau.attach(8); //servo an pin8
    gross.attach(10); //servo an pin8
  schwarz.write(90); //servo auf 90 grad gefahren
  blau.write(90);
  Serial.begin(115200); //serielle schnittstelle mit der baud rate 115200 initialisieren
  Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  Serial.println("Bereit"); //controller bereit
}

void loop() {
  delay(10);
 
 accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

uint8_t schwarzpos=90+int8_t(ax/190);
uint8_t blaupos=90+int8_t(ay/190);
uint8_t grosspos=90+int8_t(az/190);
  schwarz.write(schwarzpos);
   blau.write(blaupos);
gross.write(grosspos);
}
