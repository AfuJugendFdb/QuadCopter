#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"

Servo propeller;
int pos=0;
char buf[20];
uint8_t cbuf=0;
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
uint8_t drehzahl = 100;
uint8_t reglerOn = 0;

void setup() {
  propeller.attach(9);
  propeller.write(0);
  Serial.begin(115200); //serielle schnittstelle mit der baud rate 115200 initialisieren
  Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  Serial.println("Bereit"); //controller bereit
}

void loop() 
{
int16_t result=parse();

if(result > 0)
{
  Serial.println(result);
  if((result>=0) && (result<=180)) {
    propeller.write(result);
    drehzahl = result;
    Serial.println("Propeller gestzt");
  }
}
else if(result == -2)
{
  if(reglerOn == 0)
  {
    reglerOn = 1;
    Serial.println("GyroRegler an");
  }
  else
  {
    reglerOn = 0;
    Serial.println("GyroRegler aus");
  }
  
}
if(reglerOn == 1) {
   
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
    uint8_t drehGyro = 90+int8_t(ax/190);
    Serial.println(drehzahl + 0.7*drehGyro);
    propeller.write(drehzahl + 0.7*drehGyro);

    delay(50);
  }

}

int16_t parse()
{
  
  if(Serial.available()>0) {
    buf[cbuf]=Serial.read();

    if(buf[cbuf] == 'a')
    {
      return -2;
    }
    
    else if(buf[cbuf]==0x0A) {
      //zahl lesewn
      //Serial.println("Neue Zeile erkannt:");
      buf[cbuf]=0x00;
      int16_t paresei=atoi(buf);
      //Serial.println(paresei);
      clearbuf();
      cbuf=0; 
      return(paresei);
    }
    
    else{
    cbuf++;
    if(cbuf>=20) {
      clearbuf();
      cbuf=0;
      Serial.println("Ueberlauf");
    }
    }
    
  } 
  return(-1);
}


void clearbuf() {
  for(uint8_t cnt=0; cnt<20; cnt++) {
    buf[cnt]=0;
  }
}
