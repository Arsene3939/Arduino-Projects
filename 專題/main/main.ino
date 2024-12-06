#include<BluetoothSerial.h>
#include<Wire.h>//A4:SDA A5:SCL;
#include"image.h"
#define time_addr   0x11
#define LCD_addr    0x09
#define SD178_addr  0x20
byte cntl[5]={32,26,27,13,25};
byte num[5]={12,33,35,34,14};
byte speeds=60;
BluetoothSerial espBT;
void setup() {
  // put your setup code here, to run once:
  espBT.begin("esp32");
  Serial.begin(115200);
  Wire.begin();
  for(int i=0;i<5;i++){
    pinMode(cntl[i],INPUT_PULLUP);
    pinMode(num[i],INPUT_PULLUP);
  }
  delay(10); // waits 10ms
}
byte BT_bus[100];
byte busindex=0;
void access(){
   if(espBT.available()){
    int value=espBT.read();
    Serial.print("BT ");
    Serial.print(value);
    Serial.println(',');
    if(value==0xFF){
      for(int i=0;i<busindex;i++)
        BT_bus[i]=0;
      busindex=0;
    }
    else{
      BT_bus[busindex]=value;
      busindex++;
    }
  }
}
int time_mod=0;
int clk=0;
byte timebus[4]={0,0,0,0};
void timef(int time_mod){
  timebus[0]=time_mod/1000;
  timebus[1]=(time_mod/100)%10;
  timebus[2]=(time_mod/10)%10;
  timebus[3]=time_mod%10;
  Serial.println(timebus[3]);
  Wire.beginTransmission(time_addr); // transmit to device #9
  Wire.write(timebus,4);                   // sends x
  Wire.endTransmission();             // stop transmitting
}
byte play[29]={0xB0,0x5F,0xA7,0xC9,0xAE,0xC9,0xB6,0xA1,0xA8,0xEC,0xA9,0xF1,0xA4,0xE2,0xAD,0xF4,0xB2,0x4D,0xBF,0xF4,0xA9,0x79,0xA4,0x55,0x88,0x00,0x00,0x00,0x01};
byte play2[5]={0x88,0x00,0x00,0x00,0x01};
byte vol[2]={0x86,0x00};
byte stopf[2]={0x40,0x80};
byte SD178ram[][10]={
  {0x20,0x20,0xA6,0x59,0xA6,0xAD,0xC0,0x5C,0xC5,0x6F,},// 吃早餐囉
  {0x20,0x20,0xA4,0xC8,0xC0,0x5C,0xAE,0xC9,0xB6,0xA1,},// 午餐時間
  {0x20,0x20,0xA4,0xC8,0xBA,0xCE,0xAE,0xC9,0xB6,0xA1,},// 午睡時間
  {0x20,0x20,0x20,0x20,0x20,0x20,0xA9,0xF1,0xBE,0xC7,},//   放學
  {0x20,0x20,0xB1,0xDF,0xC0,0x5C,0xAE,0xC9,0xB6,0xA1,},// 晚餐時間
  {0x20,0x20,0xC5,0xAA,0xAE,0xD1,0xAE,0xC9,0xB6,0xA1,},// 讀書時間
  {0x20,0x20,0xA5,0xF0,0xAE,0xA7,0xAE,0xC9,0xB6,0xA1,},// 休息時間
  {0x20,0x20,0xBA,0xCE,0xA5,0x73,0xAE,0xC9,0xB6,0xA1,},// 睡覺時間
};
void soundf(byte ins){
  Serial.print("ins=");
  Serial.println(ins,HEX);
  Wire.beginTransmission(SD178_addr);
  Wire.write(stopf,2);// sends x
  Wire.endTransmission();
  delay(20);
  if(ins<0x10){
    vol[1]=ins<<4;
    Wire.beginTransmission(SD178_addr);
    Wire.write(vol,2);// sends x
    Wire.endTransmission();
  }
  else if(ins<0x20){
    play[26]=ins&0xF;
    Wire.beginTransmission(SD178_addr); 
    Wire.write(play,29);// sends x
    Wire.endTransmission();
  }
  else if(ins<0x30){
    Wire.beginTransmission(SD178_addr); 
    Wire.write(SD178ram[ins&0xF],10);// sends x
    Wire.endTransmission();
  }
  else if(ins<0x40){
    play2[2]=ins&0xF;
    Wire.beginTransmission(SD178_addr); 
    Wire.write(play2,5);// sends x
    Wire.endTransmission();
  }
}
void imagef(byte frame){
  Wire.beginTransmission(LCD_addr); 
  Wire.write(0xF1);
  Wire.endTransmission();
  delay(100);
  for(int i=0;i<1024;i++){
    Wire.beginTransmission(LCD_addr);
    Wire.write(image[frame][i]);
    Wire.endTransmission();
    //delayMicroseconds(2000);
  }
}
bool buttonBf[5][2];
bool tuckBf[2];
bool rising_trigger(byte button){
  if(buttonBf[button][1]==0)
    buttonBf[button][0]=digitalRead(cntl[button]);
  else 
    buttonBf[button][0]=buttonBf[button][1];
  buttonBf[button][1]=digitalRead(cntl[button]);
  if(buttonBf[button][1]!=buttonBf[button][0]&&buttonBf[button][0]==1)
    return 1;
  return 0;
}
bool gate=1;
void remind(int when,byte sd178,byte lcd){
  int endt=when;
  endt=endt+10;
  if(endt%100>=60)
    endt+=40;
  if(time_mod==when && gate==1){
    soundf(sd178);
    imagef(lcd);
    gate=0;
  }
  else if(time_mod==endt&gate==0){
    gate=1;
    imagef(4);
  }
}
uint64_t getsec=0xFFFFFFFFFFFFFFFF;
bool long_press(byte button){
  if(rising_trigger(button)){
    getsec=millis();
    return 1;
  }
  if(!buttonBf[button][0])
    if(millis()-getsec>100)return 1;
  return 0;
}
void loop(){
  access();
  remind( 600,0x10,0);
  remind( 630,0x20,2);
  remind(1200,0x21,1);
  remind(1230,0x22,2);
  remind(1655,0x23,3);
  remind(1730,0x24,2);
  remind(1830,0x25,4);
  remind(2200,0x26,5);
  remind(2230,0x27,6);
  if(BT_bus[0]!=0x00){
    soundf(0x30|BT_bus[0]);
    BT_bus[0]=0x00;
  }
  if(clk!=millis()/60000){
    time_mod++;
    clk=millis()/60000;
    if(time_mod%100==60){
      time_mod+=40;
    }
    if(time_mod>2359)time_mod=0;
    timef(time_mod);
  }
    if(rising_trigger(3)){
      time_mod++;
      if(time_mod%100==60)time_mod+=40;
      if(time_mod>2359)time_mod=0;
      timef(time_mod);
    }
    if(rising_trigger(4)){
      time_mod--;
      if(time_mod%100>60)time_mod-=40;
      if(time_mod<0)time_mod+=2400;
      timef(time_mod);
    }
    if(rising_trigger(1)){
      time_mod+=100;
      if(time_mod>2359)time_mod-=2400;
      timef(time_mod);
    }
    if(rising_trigger(2)){
      time_mod-=100;
      if(time_mod<0)time_mod+=2400;
      timef(time_mod);
    }
    if(rising_trigger(0)){
      soundf(0x90);
      Wire.beginTransmission(time_addr); // transmit to device #9
      Wire.write(0xAA);                   // sends x
      Wire.endTransmission();             // stop transmitting
    }
}
