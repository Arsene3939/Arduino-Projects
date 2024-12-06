#include <NewPing.h>
#define A 0
#define B 1
#define C 2
byte Echo[3]={7,8,9};
byte Trigger[3]={4,3,2};
byte directionLED[3]={11,10,12};
byte Switch=A2;
uint32_t away=0,access=0;
uint8_t MAX_DISTANCE=200;
NewPing partA(Trigger[0],Echo[0], MAX_DISTANCE);
NewPing partB(Trigger[1],Echo[1], MAX_DISTANCE);
NewPing partC(Trigger[2],Echo[2], MAX_DISTANCE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Switch,1);
  for(int i=0;i<3;i++){
    pinMode(directionLED[i],1);
    digitalWrite(directionLED[i],1);
  }
}
byte recognize(byte part){
  if(!part)
    return partA.ping_cm();
  else if(part)
    return partB.ping_cm();
  else return partC.ping_cm();
}
void light(byte offset){
  byte k=recognize(0);  
  if(k==0||k>offset){
    away+=1;
    access=0;
    digitalWrite(directionLED[0],1);
  }
  if(away>10){
    digitalWrite(Switch,0);
    away=0;
    access=0;
    return;
  }
  else if((k<offset)&&k!=0){
    digitalWrite(directionLED[0],0);
    access++;
    away=0;
  }
  if(access>10){
    access=0;
    digitalWrite(Switch,1);
  }
  Serial.print("away=");
  Serial.print(away);
  Serial.print(',');
  Serial.print("access=");
  Serial.print(access);
  Serial.print(',');
  Serial.println(k);
}
bool a=0;
void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  light(90);
}
