#include <Servo.h>

Servo propeller;
int pos=0;
char buf[20];
uint8_t cbuf=0;

void setup() {
  propeller.attach(9);
  propeller.write(0);
  Serial.begin(115200);
  Serial.println("Bereit:");
}

void loop() 
{
uint16_t result=parse();

if(result !=-1)
{
  Serial.println(result);
  if((result>=0) && (result<=180)) {
    propeller.write(result);
    Serial.println("Propeller gestzt");
  }
}
 
}

int16_t parse()
{
  
  if(Serial.available()>0) {
    buf[cbuf]=Serial.read();
    
    if(buf[cbuf]==0x0A) {
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

