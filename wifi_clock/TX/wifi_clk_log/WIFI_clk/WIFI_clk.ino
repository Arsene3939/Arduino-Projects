void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
}
void loop(){
  if(Serial2.available()>0)
    Serial.println(Serial2.read());
}
/*

#if defined(ESP32)         // 當前目標板子是 ESP32
  #include <WiFi.h>
#elif defined(ESP8266)     // 當前目標板子是 ESP8266
  #include <ESP8266WiFi.h>
#else                      // 其他板子提示錯誤
  #error "板子必須是 ESP8266 或 ESP32."
#endif

#include <TimeLib.h>
#include <WiFiUdp.h> 
#include <HTTPClient.h>
#include<HardwareSerial.h>
#include <string>
#define newline 1
//const char ssid[] = "KAMITACHI";  //你的WIFI
//const char pass[] = "035545175";  //你的WIFI密碼

const char ssid[] = "113N5F";  //你的WIFI
const char pass[] = "53942557";  //你的WIFI密碼

//HardwareSerial Serial2(2);//TX:17,RX:16;
// NTP Servers:
static const char ntpServerName[] = "time1.aliyun.com";//阿里雲的時間服務器
String request = "http://192.168.0.5:3000/log/?log=";
const int timeZone = 8;     // 時區

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

time_t getNtpTime();
char *num_week(uint8_t dayofweek,int Mode);//計算星期
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
bool isServerOn = 1;
void send();
void printAndLog(char str,bool ln = 0);
void printAndLog(int str,bool ln = 0);
void printAndLog(String str,bool ln = 0);
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(250);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  printAndLog("IP number assigned by DHCP is ");
  printAndLog(WiFi.localIP().toString().c_str(),newline);
  printAndLog("Starting UDP",newline);
  Udp.begin(localPort);
  printAndLog("Local port = ");
#if defined(ESP32)         // 當前目標板子是 ESP32
  printAndLog(String(Udp.remotePort()),newline);
#elif defined(ESP8266)     // 當前目標板子是 ESP8266
  printAndLog(Udp.localPort(),newline);
#endif
  printAndLog("waiting for sync",newline);
  setSyncProvider(getNtpTime);
  setSyncInterval(3500);
  now();
}
 
void loop()
{
  now();
  send();
  //digitalClockDisplay();
}
void send(){
  Serial.println("waiting for signal");
  while(Serial2.available()>1){
    Serial.println(Serial2.read());

  }
  if(Serial2.available()){
    char cmd = Serial2.read();
    printAndLog(cmd);
    printAndLog("  attached",1);
    if(cmd!='S')
      return;
    if(year()-2000<0)
      Serial2.write('r');
    write_time('y',year()-2000);
    write_time('o',month());
    write_time('d',day());
    write_time('h',hour());
    write_time('m',minute());
    write_time('s',second());
    write_time('e','e');
  }
  Serial.println("received nothing.");
}
void write_time(char symbol, int value){
  Serial2.write(symbol);
  Serial2.write(value);
  printAndLog(symbol);
  printAndLog(value,newline);
}

String makeURL(String request,String value){
  while(value.indexOf(' ') >= 0)
    value.replace(" ","%20");
  while(value.indexOf(':') >= 0)
    value.replace(":","%3A");
  while(value.indexOf('=') >= 0)
    value.replace("=","%3D");
  return request+value;
}
void printAndLog(char str,bool ln){
  if(ln) Serial.println(str);
  else   Serial.print(str);
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String url = makeURL(request, String(str));
    http.begin(url.c_str());
    http.setConnectTimeout(100);
    int responseCode = http.GET();
    if(responseCode < 0)
      Serial.println("http error");
  }
}
void printAndLog(int str,bool ln){
  if(ln) Serial.println(str);
  else   Serial.print(str);
  if(WiFi.status()== WL_CONNECTED){
    
    HTTPClient http;
    String url = makeURL(request, String(str));
    http.begin(url.c_str());
    http.setConnectTimeout(400);
    int responseCode = http.GET();
    if(responseCode < 0)
      Serial.println("http error");
    http.end();
  }
}
void printAndLog(String str,bool ln){
  if(ln) Serial.println(str);
  else   Serial.print(str);
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String url = makeURL(request, String(str));
    http.begin(url.c_str());
    http.setConnectTimeout(400);
    int responseCode = http.GET();
    if(responseCode < 0)
      Serial.println("http error");
  }
}
char week1[10],week2[8],week3[2],week4[4];
char *num_week(uint8_t dayofweek,int Mode){
  switch(dayofweek)
  {
    case 1: 
    strcpy(week1,"Sunday");
    strcpy(week2,"週日");
    strcpy(week3,"Su");
    strcpy(week4,"日"); 
      break;
    case 2: 
    strcpy(week1,"Monday");
    strcpy(week2,"週一");
    strcpy(week3,"Mo");
    strcpy(week4,"一"); 
      break;
    case 3: 
    strcpy(week1,"Tuesday");
    strcpy(week2,"週二");
    strcpy(week3,"Tu");
    strcpy(week4,"二"); 
      break;
    case 4: 
    strcpy(week1,"Wednesday");
    strcpy(week2,"週三"); 
    strcpy(week3,"We");
    strcpy(week4,"三"); 
      break;
    case 5: 
    strcpy(week1,"Thursday");
    strcpy(week2,"週四"); 
    strcpy(week3,"Th");
    strcpy(week4,"四"); 
      break;
    case 6: 
    strcpy(week1,"Friday");
    strcpy(week2,"週五");
    strcpy(week3,"Fr"); 
    strcpy(week4,"五");
      break;
    case 7: 
    strcpy(week1,"Saturday");
    strcpy(week2,"週六"); 
    strcpy(week3,"Sa");
    strcpy(week4,"六");
      break;
    default:
    strcpy(week1,"NO");
    strcpy(week2,"無");
    strcpy(week3,"NO");
    strcpy(week4,"無");
      break; 
  }
  switch(Mode)
  {
    case 1: return week1; break;
    case 2: return week2; break;
    case 3: return week3; break;
    case 4: return week4; break;
  }
}
 
void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(year());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("   ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print("   星期");
  Serial.print(num_week(weekday(),4));
  Serial.println();
}
 
void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
 
 
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
 
time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address
 
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  printAndLog("Transmit NTP Request",newline);
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  printAndLog(ntpServerName);
  printAndLog(": ");
  printAndLog(ntpServerIP.toString().c_str(),newline);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      printAndLog("Receive NTP Response",newline);
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  printAndLog("No NTP Response :-(",newline);
  return 0; // return 0 if unable to get the time
}
 
// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
*/

