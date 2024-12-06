#define setT 217
byte pinOut[10]={2,3,4,5,7,8,9,10,12,11};
byte digit[4]={5,4,3,2};
byte BCD[4]={7,10,9,8};
byte tuckOut=12;
byte bz=11;
byte timeButton[6]={A3,A1,A2,A0,A4,A5};
byte m,h,a=6,b=10;
uint64_t Min=setT%100;
uint64_t hour=setT/100;
bool state=1,Val=0,v=1;
uint64_t cou=0;
void setup(){
  Serial.begin(115200);
  for(int i=0;i<10;i++){
    if(i<6)pinMode(timeButton[i],INPUT);
    pinMode(pinOut[i],OUTPUT);
  }
  for(int i=0;i<2;i++){
    analogWrite(bz,220);
    delay(10);
    digitalWrite(bz,1);
    delay(120);
  }
}
bool buttonBf[5][2];
bool tuckBf[2];
bool rising_trigger(byte button){
  if(buttonBf[button][1]==0)
    buttonBf[button][0]=digitalRead(timeButton[button]);
  else 
    buttonBf[button][0]=buttonBf[button][1];
  buttonBf[button][1]=digitalRead(timeButton[button]);
  if(buttonBf[button][1]!=buttonBf[button][0]&&buttonBf[button][0]==1)
    return 1;
  return 0;
}
void number(short N){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++)
      digitalWrite(BCD[j],((int(N/pow(10,i)))%10)&1<<j);
    digitalWrite(digit[i],1);
    delay(3);
    digitalWrite(digit[i],0);
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
bool k=0;
void remind(byte Hr,byte minute,byte ifc=60){  
  k=!digitalRead(timeButton[2]);
  if(h==Hr&&m>=minute&&m<ifc-1){
    if(k&h==Hr&&m>=minute&v)v=0,Min--; 
    if(!(cou%20<10&Val&v))
      digitalWrite(11,0);
    else analogWrite(11,220);
    if(cou%60==0)Val=!Val;
  }
  else digitalWrite(11,0);
  if(h==Hr&&m==minute-1)v=1;
}
void Main(){
  cou++;
  if(rising_trigger(4))
    while(1){
      if(rising_trigger(4))break;
      if(long_press(0))a++;
      if(long_press(1))a--;
      if(long_press(2))b++;
      if(long_press(3))b--;
      number(a*100+b);
    }
  if(long_press(0))hour++;
  if(long_press(1))hour--;
  if(long_press(2))Min++;
  if(long_press(3))Min--;
  if(state){
    uint32_t _time=millis()/60000;
    m=(_time+Min)%60;
    h=(((_time+Min-(_time+Min)%60))/60+hour)%24;
    number(h*100+m);
  }
}
void loop(){
  Main();
  remind(a,b);
}
