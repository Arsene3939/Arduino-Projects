#define setT 837
#define baud 5
byte pinOut[10]={2,3,4,5,7,8,9,10,11};
byte digit[4]={7,8,9,10};
byte BCD[4]={5,2,3,4};
byte bz=11;
byte timeButton[3]={A1,A0,A2};
byte m,h;
uint64_t Min=setT%100;
uint64_t hour=setT/100;
bool state=1,Val=0,v=1;
byte mode=0,val=0;
uint64_t cou=0;
void setup(){
  Serial.begin(115200);
  for(int i=0;i<10;i++){
    if(i<6)pinMode(timeButton[i],INPUT);
    pinMode(pinOut[i],OUTPUT);
  }
  digitalWrite(bz,0);
}
bool buttonBf[3][2];
bool tuckBf[2];
bool rising_trigger(byte button){
  if(buttonBf[button][1]==1)
    buttonBf[button][0]=digitalRead(timeButton[button]);
  else 
    buttonBf[button][0]=buttonBf[button][1];
  buttonBf[button][1]=digitalRead(timeButton[button]);
  if(buttonBf[button][1]!=buttonBf[button][0]&&buttonBf[button][0]==0)
    return 1;
  return 0;
}
void number(short N){
  
  char _clock[5]={'0','0','0','0','i'};
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      byte digitN=(int(N/pow(10,i)))%10;
      _clock[3-i]=digitN;
      digitalWrite(BCD[j],digitN&1<<j);
    }
    digitalWrite(digit[i],1);
    delay(3);
    digitalWrite(digit[i],0);
  }
  for(int i=0;i<5;i++)
    if(mode==i&val){
      val=0;
      Serial.write(_clock[i]);
    }
  if(cou%baud==0)mode++,val=1;
  if(mode>4)mode=0;
}
uint64_t getsec=0xFFFFFFFFFFFFFFFF;
bool long_press(byte button){
  if(rising_trigger(button)){
    getsec=millis();
    return 1;
  }
  if(buttonBf[button][0])
    if(millis()-getsec>100)return 1;
  return 0;
}
bool k=0;
void remind(byte Hr,byte minute,byte ifc=60){  
  k=digitalRead(timeButton[1]);
  if(h==Hr&&m>=minute&&m<ifc-1){
    if(k&h==Hr&&m>=minute&v)v=0,Min--; 
    if(cou%30<15&Val&v)
      analogWrite(11,220);
    else digitalWrite(11,0);
    if(cou%90==0)Val=!Val;
  }
  else digitalWrite(11,0);
  if(h==Hr&&m==minute-1)v=1;
}
void Main(){
  cou++;
  if(long_press(2))hour++;
  if(long_press(1))Min++;
  if(long_press(0))Min--;
  if(state){
    uint32_t _time=millis()/60000;
    m=(_time+Min)%60;
    h=(((_time+Min-(_time+Min)%60))/60+hour)%24;
    number(h*100+m);
  }
}
void loop(){
  Main();
  remind(6,10); 
}
