int  scan[3]={10,9,8};
int  recieve[5]={7,6,5,4,3};
byte pin=13;
#include"char.h"
#include<easyTimer.h>
#include<Wire.h>
byte x[95];
bool ena=1;
void setup() {
  Serial.begin(9600);
  Wire.begin(0x11);
  Wire.onReceive(receiveEvent);
  for(int i=0;i<3;i++)
    pinMode(scan[i],OUTPUT);
  for(int i=0;i<5;i++)
    pinMode(recieve[i],OUTPUT);
  for(int i=0;i<=127-0x20;i++)
    x[i]=i+0x20;
  pinMode(pin,1);
}
void placeDot(short x,uint8_t y){
  for(int i=0;i<3;i++)
    digitalWrite(scan[i],x&1<<i);
  for(int j=0;j<5;j++)
    digitalWrite(recieve[j],y&1<<j);
}
void display(uint8_t ASCII,byte cc){
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      if((code_[ASCII-0x20][i])&1<<j){
        placeDot(i,j+cc+((ASCII>'Z')|ASCII=='@')-(ASCII==' ')*2+24);
        delayMicroseconds(300);
      }
}
void print(char str[],char len){
    char i;
    int j;
    for(j=0;j<len*6+32;j++){
      if(ena==1)
      mdelay(60)
        for(i=0;i<len;i++){
          if((-j+i*6)>-32&&(-j+i*6)<0)
            display(str[i],(-j+i*6));
        }
      else{
        break;
      }
    }
}
void screen(int now_time){
  display(now_time/1000+0x30,-26);
  display((now_time/100)%10+0x30,-21);
  display(':',-18);
  display((now_time/10)%10+0x30,-13);
  display(now_time%10+0x30,-8);
}
int time_mod=0;
byte I2C_bus[100];
void receiveEvent(int bytes) {
  int i=0;
    while(Wire.available()){
      I2C_bus[i]=Wire.read();
      if(I2C_bus[0]==0xAA){
        ena=0;
        break;
      }
      i++;
    }
    if(I2C_bus[0]!=0xAA)time_mod=1000*I2C_bus[0]+100*I2C_bus[1]+10*I2C_bus[2]+I2C_bus[3];
}
void event(int doki,char st[]){
  byte len=strlen(st);
  char ti[5]={time_mod/1000+0x30,(time_mod/100)%10+0x30,':',(time_mod/10)%10+0x30,time_mod%10+0x30};
  int endt=doki;
    endt=endt+10;
    if(endt%100==60){
      endt+=40;
    }
    if(endt>2359)endt=0;
  if(time_mod>=doki && time_mod<endt &&ena==1){
    print(st,len);
    print(ti,5);
  }
  else if(time_mod==endt&&ena==0)ena=1;
}
byte data[100];
int clk=0,debounce=0,hp;
void loop(){
  screen(time_mod);
  event(600,"good moring! wake up!");
  event(630,"prepare for go to school");
  event(1200,"now is lunch time,have lunch!");
  event(1230,"take a nap");
  event(1655,"ichini no gakoni owari");
  event(1730,"dinner time!");
  event(2230,"sugoshi yasumi kudasai i");
  event(2230,"It's time to sleep!");
}
