#include<SoftwareSerial.h>
#include"Arduino.h"
class time_s{
public:
    time_s():
        year(0),
        month(0),
        day(0),
        hour(0),
        minute(0),
        second(0)
    {}
    uint16_t& Year(){return year;}
    uint8_t& Month(){return month;}
    uint8_t& Day(){return day;}
    uint8_t& Hour(){return hour;}
    uint8_t& Minute(){return minute;}
    uint8_t& Second(){return second;}
private:
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};
class esp32WifiClock{
public:
    esp32WifiClock(uint8_t rx,uint8_t tx);
    void begin(uint32_t);
    time_s getTime();
private:
    SoftwareSerial mySerial;
    time_s t;
};
