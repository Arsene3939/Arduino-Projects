#include <WiFi.h>
//#include "time.h"

const char* ssid     = "CHT7400";
const char* password = "035545175";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200;//格林威治時間,一格3600,GMT+8就是8*3600=28800
const int   daylightOffset_sec = 3600;
byte BCD[4]={21,18,19,25};
byte digit[2]={22,23};
void setup(){
  Serial.begin(115200);
  for(int i=0;i<4;i++)
    pinMode(BCD[i],OUTPUT);
  for(int i=0;i<2;i++)
    pinMode(digit[i],OUTPUT);
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);//連上拿到時間資料後就切斷連線
  WiFi.mode(WIFI_OFF);
}
void sn(int n){
  for(int i=0;i<4;i++)
    digitalWrite(BCD[i],n&(1<<i));
}
void dig(int n){
  for(int i=0;i<2;i++)
    digitalWrite(digit[i],n&(1<<i));
}
void num(int n){
  for(int i=0;i<4;i++){
    dig(i);
    sn(int(n/pow(10,i))%10);
    delay(2);
  }
}
int n=0;
void loop(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
    Serial.println("Failed to obtain time");
  num(timeinfo.tm_hour*100+timeinfo.tm_min);
}
void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");//參考C++的strftime語法就會知道為甚麼這樣寫
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("TEST variables");//抓取時間資料裡的"小時"存成字串做測試,以便後續應用
  char myHour[3];
  strftime(myHour,3, "%H", &timeinfo);
  Serial.println(myHour);
  String A = String(myHour);
  Serial.println(A);
}
