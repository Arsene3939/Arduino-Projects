#ifndef __ledAray
	#define __ledAray
#endif
#ifndef __CHAR
	#include "CHAR.h"
#endif

typedef struct{
	char LED[8];
}LEDARAY;
typedef struct{
	bool MAP[8][8];
}LEDARAY_MAP;

#define Delay(msec) for(long long int __msec=millis();millis()-__msec;) 

class ledAray{
  private:
  	
    int LEDC[8],LEDL[8];
    int scanningSpeed;
    
    LEDARAY CodeChanger(long long int x){
		LEDARAY Changer;
		for(int g=0;g<8;g++)Changer.LED[g]=0;
		for(int g=0;g<8;g++)
	        for(int gg=0;gg<8;gg++)
	        	Changer.LED[g]+=((x>>(gg*8+g))&1)<<gg;
	    return Changer;
	}
	LEDARAY_MAP LEDARAYtoMAP(LEDARAY x){
		LEDARAY_MAP final;
		for(int g=0;g<8;g++)
			for(int gg=0;gg<8;gg++)
				final.MAP[g][gg]=(x.LED[7-g]>>(7-gg))&1;
		return final;
	}
	
	LEDARAY leftMove(int Move,LEDARAY x,LEDARAY y){
		for(int g=0;g<8;g++)
			for(int gg=1;gg<=Move;gg++){
				x.LED[g]<<=1;
				x.LED[g]|=(y.LED[g]>>(8-gg))&1;
			}
		return x;
	}
	
	
  public:
  	
  	void setLEDC(int C1,int C2,int C3,int C4,int C5,int C6,int C7,int C8){
      LEDC[0]=C1;
      LEDC[1]=C2;
      LEDC[2]=C3;
      LEDC[3]=C4;
      LEDC[4]=C5;
      LEDC[5]=C6;
      LEDC[6]=C7;
      LEDC[7]=C8;
    }
    void setLEDL(int L1,int L2,int L3,int L4,int L5,int L6,int L7,int L8){
      LEDL[0]=L1;
      LEDL[1]=L2;
      LEDL[2]=L3;
      LEDL[3]=L4;
      LEDL[4]=L5;
      LEDL[5]=L6;
      LEDL[6]=L7;
      LEDL[7]=L8;
    }
    
    void OFF(){
      for(int g=0;g<8;g++){
        digitalWrite(LEDL[g],LOW);
        digitalWrite(LEDC[g],HIGH);
      }
    }
    
    void ON(LEDARAY x){
      for(int g=0;g<8;g++){
        OFF();
        digitalWrite(LEDL[g],HIGH);
        for(int gg=0;gg<8;gg++){
          digitalWrite(LEDC[gg],((~x.LED[g])>>gg)&1);
        }
        delay(scanningSpeed);
      }
    }
    void ON(long long int x){
    	ON(CodeChanger(x));
	}
	void ON(LEDARAY_MAP X){
		LEDARAY FINAL;
		for(int g=0;g<8;g++)FINAL.LED[g]=0;
		for(int g=0;g<8;g++)
			for(int gg=0;gg<8;gg++,FINAL.LED[g]<<=1)
				FINAL.LED[g]+=(X.MAP[7-g][7-gg])&1;
		ON(FINAL);
	}
	
	void marquee(long long int wait,int times,char x[]){
	    for(;times>0;times--)
	      for(int g=0;x[g]!=0;g++)
	        for(int gg=0;gg<8;gg++){
	            Delay(wait)
	              if(x[g+1]!=0)ON(leftMove(gg,CodeChanger(Alphabet(x[g])),CodeChanger(Alphabet(x[g+1]))));
	              else ON(leftMove(gg,CodeChanger(Alphabet(x[g])),CodeChanger(Alphabet(' '))));
	        }
	}
	void marquee(int wait,char x[]){
		marquee(wait,1,x);
	}
	
    void begin(int __scanningSpeed){
      scanningSpeed=__scanningSpeed;
      for(int g=0;g<8;g++){
        pinMode(LEDC[g],OUTPUT);
        pinMode(LEDL[g],OUTPUT);
      }
      OFF();
    }
    void begin(){
    	begin(2);
	}
	
};
