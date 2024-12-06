/*
LCD  Arduino
PIN1 = GND
PIN2 = 5V
RS(CS) = 8; 
RW(SID)= 9; 
EN(CLK) = 3;
PIN15 PSB = GND;
*/

#include "LCD12864RSPI.h"
#include <Wire.h>//A4_SDA  A5_SCL
int LED = 13;
int x = 0;
bool flag,flage_last=0;
byte I2C_bus;
byte image[1024],str[16];
void setup()
{
  LCDA.Initialise(); // INIT SCREEN
  delay(100);
  pinMode (LED, OUTPUT);
  Serial.begin(57600);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  int i=0;
  if(flag==0)
    while(Wire.available()){
      I2C_bus=Wire.read();
      if(I2C_bus==0xF1)
        flag=1,x=0;
      flage_last=flag;    }
  else{
    while(Wire.available()){
      if(flag==1){
        image[x]=Wire.read();
        x++;
        if(x>1023){
          x=0,flag=0;
          LCDA.DrawFullScreen(image);
        }
      }
    }
  }
  digitalWrite(13,flag);
}
void loop()
{ 
   
}
/*
 * LCDA.CLEAR();//����
delay(100);
LCDA.DisplayString(0,0,en_char1,16);//
delay(10);
LCDA.DisplayString(1,0,en_char2,16);//
delay(10);
LCDA.DisplayString(2,0,en_char3,16);//
delay(10);
LCDA.DisplayString(3,0,wangzhi,16);//
delay(5000);
LCDA.CLEAR();//����
delay(100);
LCDA.DisplayString(0,0,show1,16);//
delay(10);
LCDA.DisplayString(1,0,show2,16);//
delay(10);
LCDA.DisplayString(2,0,show3,16);//
delay(10);
LCDA.DisplayString(3,0,wangzhi,16);//LOGO
delay(5000);
 */
