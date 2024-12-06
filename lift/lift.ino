#include <Servo.h>
Servo servo0;
void setup(){
 Serial.begin(9600);
 servo0.attach(12,950,2300);//1550;
 pinMode(A4,INPUT_PULLUP);
 pinMode(10,INPUT_PULLUP);
 pinMode(9,INPUT_PULLUP);
 pinMode(11,INPUT);
}
int r=1540;
char x;
void writeled(char val){
  if(val=='1'){
    pinMode(11,OUTPUT);
    digitalWrite(11,1);
    Serial.println(1);
  }
  else if(val=='0'){
    pinMode(11,OUTPUT);
    digitalWrite(11,0);
    Serial.println(0);
  }
  else if(val=='z')
    pinMode(11,INPUT);
  else return;
}
void ver1(){
  if(x=='u'){
    r+=100;
    x=' ';
    Serial.println(r);
  }
  if(x=='d'){
    r-=100;
    Serial.println(r);
    x=' ';
  }
  servo0.writeMicroseconds(r);
}
void ver2(){
  int Step=200;
  if(x=='u'){
    Serial.println('u');
    x=' ';
    servo0.writeMicroseconds(1700);
    delay(Step);
    servo0.writeMicroseconds(1540);
  }
  if(x=='d'){
    Serial.println('d');
    servo0.writeMicroseconds(1300);
    delay(Step);
    servo0.writeMicroseconds(1540);
    x=' ';
  }
}
void loop(){
  
  if(Serial.available()){
    x=Serial.read();
    Serial.println(x);
    
  }
  //ver1();
   if(!digitalRead(9)){
    servo0.writeMicroseconds(2000);
    writeled('1');
  }
  else if(!digitalRead(10)){
    
    servo0.writeMicroseconds(1400);
    writeled('0');
  }
  else {
    servo0.writeMicroseconds(1550);
    writeled('z');
  }
  
  Serial.print(digitalRead(10));
  Serial.print(',');
  Serial.print(digitalRead(9));
  Serial.print(',');
  Serial.println(analogRead(A4));
}
