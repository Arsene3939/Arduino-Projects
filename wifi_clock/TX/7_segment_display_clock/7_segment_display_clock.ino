#define t 5
#define baud 20
int hour =2;
int Min=17;
uint64_t _time;
uint8_t mode=0;
uint8_t Switch[3]={A0,A1,A2};
uint8_t COM[4]={7,8,9,10};
uint8_t bin[4]={5,2,3,4};
boolean V=1,v=1,val=1,Val=1,sw[3];
uint8_t x,y;
int Pow(int base,int n){
  int re=1;
  for(int i=0;i<n;i++)
    re=re*base;
  return re;
}
void turndec( int c,int dec)
{
  digitalWrite(COM[c],1);
  for(int i=0;i<4;i++)
    if(dec&1<<i) digitalWrite(bin[i],1);
    else digitalWrite(bin[i],0);
  delay(1);
  digitalWrite(COM[c],0);
}
void Time(int numbers,int numberm)
{
  char _clock[5]={'0','0','0','0','i'};
  _clock[3]=char(numbers%10);
  _clock[2]=char((numbers%100-_clock[3])/10);
  _clock[1]=char(numberm%10);
  _clock[0]=char((numberm%100-_clock[1])/10);  
  for(int i=3;i>-1;i--)
    turndec(i,_clock[3-i]);
  for(int i=0;i<5;i++)
    if(mode==i&val){
      val=0;
      Serial.write(_clock[i]);
    }
  if(_time%baud==0)mode++,val=1;
  if(mode>4)mode=0;
}
void TurnFourDigital(int number)
{
  uint8_t Number[4];
  for(int i=0;i<4;i++){
    Number[i]=((number-(number%Pow(10,3-i)))/Pow(10,3-i))%10;
    turndec(3-i,Number[i]);
  }
}
 void setup() {
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  for(int i=0;i<4;i++)
  {
    if(i<=3)
      pinMode(Switch[i],INPUT);
    pinMode(COM[i], OUTPUT);
    digitalWrite(COM[i],0);
    pinMode(bin[i], OUTPUT);
    digitalWrite(bin[i],1);
  }
}
void remind(byte Hr,byte minute,byte ifc=60){
  if(y==Hr&&x>=minute&&x<ifc-1){
    if(sw[0]&y==Hr&&x>=minute)v=0,Min--; 
    if(_time%50<25&Val&v)analogWrite(11,200);
    else digitalWrite(11,0);
    if(_time%150==0)Val=!Val;
  }
  if(y==Hr&&x==minute-1)v=1;
}
void loop() {
  uint32_t TIME=millis()/60000;
  for(int i=0;i<3;i++)
    sw[i]=digitalRead(Switch[i]);
  remind(6,10,40); 
  /*
   * 
  remind(6,40); 
  remind(9,1);
  remind(11,30);
  remind(13,1);
  remind(17,30);
  remind(19,1,45);
  remind(19,45);
  remind(21,30);
  remind(22,1);
   */
  for(int i=0;i<3;i++){
    if(sw[i]){
      if(i==0)Min++;
      if(i==2)hour++;
      if(sw[2]&sw[1])V=!V,hour--,Min--;
      if(i==1){
        Min--;
        if(x<0)Min+=60;
      }
      delay(70);
    }
  }
  x=(TIME+Min)%60;
  if(V) y=(((TIME+Min-(TIME+Min)%60))/60+hour)%24;
  else  y=(((TIME+Min-(TIME+Min)%60))/60+hour)%12+1;
  Time(x,y);
  _time++;
}
