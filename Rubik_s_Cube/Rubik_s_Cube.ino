#include <PS2X_lib.h>  //for v1.6
#include <FastLED.h>
#define NUM_LEDS 62
#define brightness 100
#define white 56
#define blue 57
#define orange 58
#define green 59
#define red 60
#define yellow 61
#define default_delay 100
#define turn_delay 100
PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte vibrate = 0;
byte pssr;
bool read_ENABLE=0;
//白藍橘綠紅黃
byte sixcolor[6][3]={{0, 0, 105},{170, 255, 100},{8,225,145},{78, 245, 35},{251,255,60},{47, 230, 155}};

CRGBArray<NUM_LEDS> leds;
uint8_t colorConv(uint8_t R,uint8_t G,uint8_t B,uint8_t type){
  long int h,s,v,MIN=255,MAX=0,r[3]={R,G,B};
  for(int i=0;i<3;i++){
    if (r[i]>MAX)MAX=r[i];
    if (r[i]<MIN)MIN=r[i];
  }
  if(MAX==MIN)h=0;
  else if(MAX==R&&G>=B)h=60/(MAX-MIN)*(G-B);
  else if(MAX==R&&G< B)h=60/(MAX-MIN)*(G-B)+360;
  else if(MAX==G)h=60/(MAX-MIN)*(B-R)+120;
  else if(MAX==B)h=60/(MAX-MIN)*(R-G)+240;
  else{
    Serial.print(R);Serial.print(',');Serial.print(G);Serial.print(',');Serial.print(B);
    Serial.println("color error");
    return 255;
  }
  if(MAX==0) s=0;
  else s=1-MIN/MAX;
  v=MAX;
  if(type==0)     return h*255/360;
  else if(type==1)return s*255;
  else if(type==2)return v;
}

byte init_color[54]={0,0,0,0,0,0,0,0,0, 4,4,4,3,3,3,2,2,2,1,1,1, 4,4,4,3,3,3,2,2,2,1,1,1 , 4,4,4,3,3,3,2,2,2,1,1,1,5,5,5,5,5,5,5,5,5};
void setup(){
  FastLED.addLeds<NEOPIXEL,A3>(leds, NUM_LEDS);
  Serial.begin(57600);
  randomSeed(analogRead(A0));
  for(int i=0;i<54;i++){
    leds[i]=CHSV(sixcolor[init_color[i]][0],sixcolor[init_color[i]][1],sixcolor[init_color[i]][2]);
  }
  for(int i=56;i<62;i++)
    leds[i]=CHSV(sixcolor[i-56][0],sixcolor[i-56][1],sixcolor[i-56][2]);
  for(int i=62;i<68;i++)
    leds[i]=CHSV(sixcolor[i-62][0],sixcolor[i-62][1],sixcolor[i-62][2]);
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  error = ps2x.config_gamepad(5,3,4,2, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
   
  if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  FastLED.delay(50);
}
void teleport(char x,byte mode=0){
  //FBRLUD MN
  byte delay_time=turn_delay,times=3;
  if(mode)delay_time=0,times=1;
  if(x>10)x+=0x30;
  if(x!='M'&&x!='m'&&x!='N'&&x!='n'&&x!='O'&&x!='o'){
    byte sort[10]={1,2,3,7,8,9,4,10,5,11};
    byte index;
    if(x=='D')index=5;
    else if(x=='d')index=11;
    else if(x<=10)index=sort[x-1]-1;
    byte order1[6][12]={
      { 1, 2, 3,12,24,36,52,53,54,40,28,16},//順時針
      {16,17,18,19,20,21,10,11,12,13,14,15},//順時針
      { 7, 6, 1,15,27,39,54,49,48,43,31,19},//順時針
      { 7, 8, 9,10,22,34,46,47,48,42,30,18},//逆時針
      { 9, 4, 3,13,25,37,52,51,46,45,33,21},//逆時針
      {34,35,36,37,38,39,40,41,42,43,44,45} //逆時針
    };
    byte order2[6][ 8]={
      {15,14,13,25,37,38,39,27},//順時針
      { 1, 6, 7, 8, 9, 4, 3, 2},//順時針
      {18,17,16,28,40,41,42,30},//順時針
      {19,20,21,33,45,44,43,31},//逆時針
      {10,11,12,24,36,35,34,22},//逆時針
      {51,52,53,54,49,48,47,46},//逆時針
    };
    if(index<6){
      for(int j=0;j<times;j++){
        leds[54]=leds[order1[index][0]-1];
        for(int i=0;i<11;i++)
          leds[order1[index][i]-1]=leds[order1[index][i+1]-1];
        leds[order1[index][11]-1]=leds[54];
        if(j>0 ||mode>1){
          leds[55]=leds[order2[index][0]-1];
          for(int i=0;i<7;i++)
            leds[order2[index][i]-1]=leds[order2[index][i+1]-1];
          leds[order2[index][7]-1]=leds[55];
        }
        //FastLED.delay(delay_time);
      }
    }
    else if(index<12){
      index-=6;
      for(int j=0;j<times;j++){
        leds[54]=leds[order1[index][11]-1];
        for(int i=11;i>0;i--)
          leds[order1[index][i]-1]=leds[order1[index][i-1]-1];
        leds[order1[index][0]-1]=leds[54];
        if(j>0||mode>1){
        leds[55]=leds[order2[index][7]-1];
        for(int i=7;i>0;i--)
          leds[order2[index][i]-1]=leds[order2[index][i-1]-1];
        leds[order2[index][0]-1]=leds[55];
        }
        //FastLED.delay(delay_time);
      }
    }
  }
  else{//中橫
    byte index=0;
    byte order[3][12]={
      { 6, 5, 4,11,23,35,51,50,49,41,29,17},
      { 8, 5, 2,14,26,38,53,50,47,44,32,20},
      {22,23,24,25,26,27,28,29,30,31,32,33}
    };
    if(x=='M'||x=='m')index=0;
    if(x=='N'||x=='n')index=1;
    if(x=='O'||x=='o')index=2;
    if(x<0x60){
      for(int j=0;j<times;j++){
        leds[54]=leds[order[index][0]-1];
        for(int i=0;i<11;i++)
          leds[order[index][i]-1]=leds[order[index][i+1]-1];
        leds[order[index][11]-1]=leds[54];
        //FastLED.delay(delay_time);
      }
    }
    else if(x<0x60+26){
      for(int j=0;j<times;j++){
        leds[54]=leds[order[index][11]-1];
        for(int i=11;i>0;i--)
          leds[order[index][i]-1]=leds[order[index][i-1]-1];
        leds[order[index][0]-1]=leds[54];
        //FastLED.delay(delay_time);
      }
    }
  }
  FastLED.delay(0);
}
int steps=0;
void formula(char* str,int delay_time=default_delay,byte mode=0){
  int len=strlen(str);
  for(int i=0;i<len;i++){
         if(str[i]=='F')str[i]='3';
    else if(str[i]=='f')str[i]='6';
    else if(str[i]=='B')str[i]='9';
    else if(str[i]=='b')str[i]=':';
    else if(str[i]=='R')str[i]='1';
    else if(str[i]=='r')str[i]='4';
    else if(str[i]=='L')str[i]='7';
    else if(str[i]=='l')str[i]='8';
    else if(str[i]=='U')str[i]='2';
    else if(str[i]=='u')str[i]='5';
    teleport(str[i]-0x30,mode);
    delay(delay_time);
  }
  if(!mode)
    steps+=len;
}
void flip(byte rotation,int delay_time=default_delay){
  char rout[4][4]={"17M","2OD","48m","5od"};
  //char* reg=rout[rotation-1];
  //Serial.println(reg);
  for(int i=0;i<3;i++){
    formula(rout[rotation-1],0,i+1);
    delay(default_delay);
  }
/*
 *   for(int i=0;i<3;i++){
    if(rotation==1)
      formula("17M",0,i+1);
    else if(rotation==2)
      formula("2DU",0,i+1);
    else if(rotation==3)
      formula("48m",0,i+1);
    else if(rotation==4)
      formula("5du",0,i+1);
    delay(50);
  }
 */
}
void monit(){
  Serial.print("pss_RX=");
  Serial.print(ps2x.Analog(PSS_RX));
  Serial.print(",");
  Serial.print("pss_RY=");
  Serial.print(ps2x.Analog(PSS_RY));
  Serial.print(",");
  Serial.print("pss_LX=");
  Serial.print(ps2x.Analog(PSS_LX));
  Serial.print(",");
  Serial.print("pss_LY=");
  Serial.println(ps2x.Analog(PSS_LY));
}
void pssx_access(){
  if(ps2x.Analog(PSS_RX)==128&&ps2x.Analog(PSS_RY)==127&&ps2x.Analog(PSS_LX)==128&&ps2x.Analog(PSS_LY)==127){
    read_ENABLE=1;
    pssr=0;
  }
  else{
    if     (ps2x.Analog(PSS_RY)>127)pssr=1;
    else if(ps2x.Analog(PSS_RY)<127)pssr=4;
    if     (ps2x.Analog(PSS_RX)>128)pssr=2;
    else if(ps2x.Analog(PSS_RX)<128)pssr=5;
    if     (ps2x.Analog(PSS_LY)>127)pssr=7;
    else if(ps2x.Analog(PSS_LY)<127)pssr=8;
    if     (ps2x.Analog(PSS_LX)>128)pssr=6;
    else if(ps2x.Analog(PSS_LX)<128)pssr=3;
  }
}
byte pssx_read(){
  if(pssr&&read_ENABLE){
    read_ENABLE=0;
    Serial.println(pssr);
    return pssr;
  }
  else return 0;
}
void search_center_block(int delay_time=default_delay){
  byte rout[9]={2,2,2,2,1,2,2,2,2};
  for(int i=0;i<9;i++){
    if(leds[31]==leds[white])
      break;
    else flip(rout[i],delay_time);
  }
}
void cross(int delay_time=default_delay){
  for(int i=0;i<4;i++){
    for(int g=0;g<4;g++){
      int type=0;
      bool flag=1;
           if(leds[13]==leds[white]&&leds[1]==leds[57+i])type=0;
      else if(leds[1]==leds[white]&&leds[13]==leds[57+i])type=1;
      else if(leds[10]==leds[white]&&leds[3]==leds[57+i])type=2;
      else if(leds[3]==leds[white]&&leds[10]==leds[57+i])type=3;
      else if(leds[16]==leds[white]&&leds[5]==leds[57+i])type=4;
      else if(leds[5]==leds[white]&&leds[16]==leds[57+i])type=5;
      else if(leds[19]==leds[white]&&leds[7]==leds[57+i])type=6;
      else if(leds[7]==leds[white]&&leds[19]==leds[57+i])type=7;
      else flag=0;
      char rout[6][4]={"55","2M5","2","M5","5","m2"};
      if(!flag){
        flip(1,delay_time);
      }
      else{
        if(type>5)teleport(5),type-=4;
        for(int j=0;j<g;j++)teleport(8);
        formula(rout[type],delay_time);
        flip(1,delay_time);
        break;
      }
    }
  }
  for(int i=0;i<4;i++){
    if(leds[4]==leds[blue])break;
    else flip(3,delay_time);
  }
  for(int i=0;i<4;i++){
    if(leds[7]==leds[blue])break;
    else teleport(8);
  }
  flip(1);
}
void layer1(int delay_time=default_delay){
  //formula("215"); formula("643");
  //formula("21543562");
  for(int i=0;i<4;i++){
    for(int g=0;g<4;g++){
      //delay(5000);
      //21154211542154
      int type=0;
      bool flag=1;
      if(i==3)leds[54]=leds[yellow],leds[yellow]=leds[blue];
           if(leds[ 6]==leds[58+i]&&leds[17]==leds[57+i]&&leds[18]==leds[white]) type=0;
      else if(leds[14]==leds[58+i]&&leds[15]==leds[57+i]&&leds[ 0]==leds[white]) type=1;
      else if(leds[17]==leds[58+i]&&leds[18]==leds[57+i]&&leds[ 6]==leds[white]) type=2;
      else if(leds[15]==leds[58+i]&&leds[ 0]==leds[57+i]&&leds[14]==leds[white]) type=3;
      else if(leds[18]==leds[58+i]&&leds[ 6]==leds[57+i]&&leds[17]==leds[white]) type=4;
      else if(leds[ 0]==leds[58+i]&&leds[14]==leds[57+i]&&leds[15]==leds[white]) type=5;
      else flag=0;
      if(i==3)leds[yellow]=leds[54];
      if(!flag){
        flip(1,delay_time);
        
      }
      else{
        
        if(type%2==0){
          formula("2154",delay_time);
          type--;
          if(type<0)type+=6;
          //delay(3000);
        }
        for(int j=0;j<g;j++)formula("8m",delay_time);
        for(int i=0;i<type;i++)
          formula("2154",delay_time);
        flip(1,delay_time);
        break;
      }
    }
  }
  flip(3,delay_time);
  flip(2,delay_time);
  flip(1,delay_time);
}
void layer2(int delay_time=default_delay){
  for(int i=0;i<4;i++){
    for(int g=0;g<4;g++){
      int type=0;
      bool flag=1;
      if(i==3)leds[54]=leds[yellow],leds[yellow]=leds[blue];
           if(leds[ 5]==leds[58+i]&&leds[16]==leds[57+i])type=0;
      else if(leds[16]==leds[58+i]&&leds[ 5]==leds[57+i])type=1;
      else if(leds[29]==leds[58+i]&&leds[30]==leds[57+i])type=2;
      else if(leds[30]==leds[58+i]&&leds[29]==leds[57+i])type=3;
      else flag=0;
      if(i==3)leds[yellow]=leds[54];
      char rout[2][10]={"28573768","556237386"};//54216132
      if(!flag){
        flip(2,delay_time);
        //delay(5000);
      }
      else{
        if(type>1){
          formula("2857376822",delay_time);
          type-=2;
         //delay(5000);
        }
        for(int j=0;j<g;j++)
          flip(4,delay_time);
        for(int j=0;j<g;j++)
          teleport(2);
        formula(rout[type],delay_time);
        flip(2,delay_time);
        break;
      }
    }
  }
}
bool oll_detect(byte a,byte b,byte c,byte d){
  return leds[a]==leds[yellow]&&leds[b]==leds[yellow]&&leds[c]==leds[yellow]&&leds[d]==leds[yellow];
}
void OLL(int delay_time){
  byte fx=0;
  for(int i=0;i<4;i++){
    if(leds[7]==leds[yellow]&&leds[3]==leds[yellow])     formula("123564",delay_time),fx=1;
    else if(leds[5]==leds[yellow]&&leds[3]==leds[yellow])formula("132654",delay_time),fx=2;
    else if(oll_detect(10,13,16,19))                     formula("1235645132654",delay_time),fx=3;
    else teleport(2);
    if(oll_detect( 1, 3, 5, 7))                     break;

  }
//
  for(int i=0;i<4;i++){
         if(oll_detect(12,14,18,20))formula("451542154221",delay_time),fx+=10;
    else if(oll_detect(11,15,18,20))formula("42244244244224",delay_time),fx+=20;
    else if(oll_detect( 6, 0, 9,11))formula("11d4551D4554",delay_time),fx+=30;
    else if(oll_detect( 6, 0,12,20))formula("134:1649",delay_time),fx+=40;
    else if(oll_detect( 0, 8,18,11))formula("4515421542154221",delay_time),fx+=50;
    else if(oll_detect(17,14,11, 8))formula("12421554",delay_time),fx+=60;
    else if(oll_detect(15,12, 9, 6))formula("45154221",delay_time),fx+=70;
    else teleport(2);
  }
  Serial.print("OLL:");
  Serial.println(fx);
}
void PLL(int delay_time){
  byte fx=0;
  for(int i=0;i<4;i++){
    if(leds[17]==leds[15]&&leds[14]==leds[12])break;
    else if(leds[17]==leds[15])formula("158554215547",delay_time),fx=1;
    else if(leds[17]!=leds[15]&&leds[14]!=leds[12]&&leds[11]!=leds[9]&&leds[20]!=leds[18])formula("64212451345121643",delay_time),fx=2;
    else teleport(2);
  }
  //delay(1000);
  for(int j=0;j<4;j++){
    for(int i=0;i<4;i++){
      if (leds[15]==leds[16]&&leds[15]==leds[17]&&leds[15]==leds[28]){
        flip(2);
        flip(2);
        if(leds[13]==leds[28])formula("mm2M55m2mm",delay_time),fx+=10;
        else formula("mm5M55m5mm",delay_time),fx+=20;
        Serial.print("PLL:");
        Serial.println(fx);
        return;
      }
      else if(leds[18]==leds[16]&&leds[19]==leds[17]&&leds[17]==leds[28]){
        formula("45154215422154515421542212",delay_time),fx+=30;
        Serial.print("PLL:");
        Serial.println(fx);
        return;
      }
      else if(leds[16]==leds[11]&&leds[14]==leds[19]&&leds[17]==leds[28]){
        formula("mm5mm55mm5mm",delay_time),fx+=40;
        Serial.print("PLL:");
        Serial.println(fx);
        return;
      }
      else teleport(2);
    }
    flip(2);
  }

}
byte n=0;
byte program_counter=0;
bool Blink=0;
long long int start_time;
bool mode=0;
void loop(){
/*
 *   ps2x.read_gamepad();
  if(pssx_read()==1)teleport(1);
  pssx_access();
  
 */
  if(mode==0){
    for(int i=0;i<54;i++)
      leds[i]=CHSV(sixcolor[init_color[i]][0],sixcolor[init_color[i]][1],sixcolor[init_color[i]][2]);
  
    for(int i=0;i<50;i++){
      byte nnn=random(9)+1;
      Serial.print(nnn);
      //Serial.print(',');
      teleport(nnn);
    }
   
    //formula("87169477688333249761635185579154473197536782587555",0);
    delay(1000);
    start_time=millis();
    search_center_block(100);
    delay(1500);
    cross(100);
    delay(1500);
    layer1(100);
    delay(1500);
    layer2(100);
    delay(1500);
    OLL(100);
    delay(1500);
    PLL(100);
    Serial.print("Total time consumed:");
    double aaa=(millis()-start_time)*1.0/1000;
    Serial.println(aaa);
    Serial.print("Total steps consumed:");
    Serial.println(steps);
    steps=0;
    for(int i=0;i<12;i++){
      flip(2);
      delay(500);
    }
  }
  else{
    
  }
}
