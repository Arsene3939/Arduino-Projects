#include"esp32WifiClock.h"

esp32WifiClock::esp32WifiClock(uint8_t rx,uint8_t tx):mySerial(rx,tx){}
void esp32WifiClock::begin(uint32_t baud){
    mySerial.begin(baud);
    t=time_s();
}
time_s esp32WifiClock::getTime(){
    mySerial.write('s');
    bool error=0;
    while(1){
        char ch;
        uint16_t r;
        if(mySerial.available()>1){
            ch=mySerial.read();
            r=mySerial.read();
            Serial.print(ch);
            Serial.print(',');
            Serial.println(r);
            if(ch=='e'&&r=='e')break;
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
    if(error==1)
        return getTime();
    return t;
}
