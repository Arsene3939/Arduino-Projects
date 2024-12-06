#include"esp32WifiClock.h"

esp32WifiClock::esp32WifiClock(uint8_t rx,uint8_t tx):mySerial(rx,tx){}
void esp32WifiClock::begin(uint32_t baud){
    mySerial.begin(baud);
    t=time_s();
}
time_s esp32WifiClock::GetDateTime(){
    while(mySerial.available() > 0)
        mySerial.read();
    mySerial.write('S');
    Serial.println("attaching");
    bool error=0;
    uint64_t timeout_timer=millis();
    while(1){
        if(millis()-timeout_timer>5000){
            error=1;
            Serial.println("time out, error occured");
            break;
        }
        char ch;
        uint16_t r;
        if(mySerial.available()>1){
            ch=mySerial.read();
            r=mySerial.read();
            Serial.print(ch);
            Serial.print(',');
            Serial.println(r);
            if(ch=='e'&&r=='e'&&mySerial.available()==0)break;
            switch(ch){
            case 'y':
                t.Year()=r;
            break;
            case 'o':
                t.Month()=r;
            break;
            case 'd':
                t.Day()=r;
            break;
            case 'h':
                t.Hour()=r;
            break;
            case 'm':
                t.Minute()=r;
            break;
            case 's':
                t.Second()=r;
            break;
            default:
                error=1;
                Serial.println("error occured.");
            break;
            }
        }
    }
    if(error==1){
      while(mySerial.available() > 0)
        mySerial.read();
      delay(1000);
      return GetDateTime();
    }
    return t;
}
