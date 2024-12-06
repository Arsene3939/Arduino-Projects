#include<SoftwareSerial.h>
SoftwareSerial mySerial(A12,A11);
void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
}
void loop(){
  mySerial.write('S');
  Serial.println("write 'S'");
  delay(100);
}

/*
#include"easyTimer.h"
#include"char.h"
#include<DHT.h>
#include"esp32WifiClock.h"

uint8_t LEDC[24] = {24, 25, 27, 23, 29, 22, 26, 28, 34, 31, 33, 37, 35, 36, 32, 30, 42, 39, 41, 38, 43, 40, 44, 45};
uint8_t LEDL[8] = {51, 49, 53, 47, 48, 52, 46, 50};
uint8_t _LEDC[8] = {15, 4, 5, 18, 7, 14, 16, 17};
uint8_t _LEDL[8] = {6, 3, A4, A5, 21, 2, 20, 19};

byte timeButton[3] = {A10, A9, A6};
byte cds = A8;
byte DHT11_pin = A7;
byte bz = 11;
byte cd = 100;
byte week = 1;
int bright;
int h, t;
DHT dht(DHT11_pin, DHT11);
esp32WifiClock wifiClk(A12, A11);
#define RESTART_FLAG 1
#define wifi
//DFRobotDFPlayerMini myDFPlayer;
#define countof(a) (sizeof(a) / sizeof(a[0]))
time_s now;
uint32_t time_mod;
bool buzz = 0;
uint64_t clk = 0;
byte mode = 0;
bool soundingGate = 1;
void setup() {
  wifiClk.begin(9600);
  Serial.begin(9600);
  for (int i = 0; i < 3; i++)
    pinMode(timeButton[i], INPUT_PULLUP);
  pinMode(cds, INPUT);
  for (int i = 0; i < 24; i++) {
    pinMode(LEDC[i], 1);
    digitalWrite(LEDC[i], 1);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(LEDL[i], 1);
    pinMode(_LEDL[i], 1);
    pinMode(_LEDC[i], 1);
    digitalWrite(LEDL[i], 0);
    digitalWrite(_LEDL[i], 0);
    digitalWrite(_LEDC[i], 1);
  }

  dht.begin();
  #ifdef wifi
  now = wifiClk.GetDateTime();
  #endif  
  week = redate(now.Month() * 100 + now.Day(), now.Year() + 2000);
  time_mod = now.Hour() * 10000.0 + now.Minute() * 100 + now.Second();
  t = dht.readTemperature();
  h = dht.readHumidity();
}
void placeDot(uint8_t y, uint8_t x, bool device) {
  if (device) {
    if (y > 7 || x > 23)return;
    digitalWrite(LEDL[y], 1);
    digitalWrite(LEDC[x], 0);
    delayMicroseconds(cd);
    digitalWrite(LEDL[y], 0);
    digitalWrite(LEDC[x], 1);
    delayMicroseconds(100 - cd);
  }
  else {
    if (y > 7 || x > 7)return;
    digitalWrite(_LEDL[y], 1);
    digitalWrite(_LEDC[x], 0);
    delayMicroseconds(cd);
    digitalWrite(_LEDL[y], 0);
    digitalWrite(_LEDC[x], 1);
    delayMicroseconds(100 - cd);
  }
}
void display(uint8_t ASCII, byte cc) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if ((code_[ASCII - 0x20][7 - i]) & 1 << (j))
        placeDot(i, j + cc + ((ASCII > 'Z') | ASCII == '@') + 24, 1);
}
void play3x5(byte n, byte cc) {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 8; j++)
      if ((num_code[n][i]) & 1 << (j))
        placeDot(7 - j, i + cc + 2, 0);
}
void playweeks(byte n, byte cc) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if ((__weeks_[n][7 - j]) & 1 << (7 - i))
        placeDot(7 - j, i + cc + 2, 0);
}
void print(char str[], char len) {
  char i;
  int j;
  for (j = 0; j < len * 6 + 32; j++)
    mdelay(60)
    for (i = 0; i < len; i++) {
      if ((-j + i * 6) > -32 && (-j + i * 6) < 0)
        display(str[i], (-j + i * 6));
    }
}
bool buttonBf[3][2];
bool rising_edge(byte button) {
  if (buttonBf[button][1] == 0)
    buttonBf[button][0] = digitalRead(timeButton[button]);
  else
    buttonBf[button][0] = buttonBf[button][1];
  buttonBf[button][1] = digitalRead(timeButton[button]);
  if (buttonBf[button][1] != buttonBf[button][0] && buttonBf[button][0] == 1)
    return 1;
  return 0;
}
uint64_t getsec = 0xFFFFFFFFFFFFFFFF;
bool long_press(byte button) {
  if (rising_edge(button)) {
    getsec = millis();
    return 1;
  }
  if (!buttonBf[button][0])
    if (millis() - getsec > 100)return 1;
  return 0;
}

unsigned int redate(int now_time, int y) {
  int x[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  now_time -= 100;
  int y_ = 2021, m = 6, d = 28, res = 0;
  for (int j = y_; j < y + 1; j++) {
    if (j % 4 == 0)x[1] = 29;
    else x[1] = 28;
    for (int i = (m - 1) * (j == 2021); i < (now_time / 100) * (j == y) + 12 * (j != y); i++)res += x[i % 12];
  }
  res += (now_time % 100) - d;
  return res % 7;
}
void screen(uint32_t now_time, char format) {
  bool aa = now_time > 1000, bb = now_time % 100 >= 10;
  switch (format) {
    case 't':
      if (bright > 900)
        cd = 20;
      else
        cd = 100;
      display(now_time / 100000 + 0x30, -26);
      display((now_time / 10000) % 10 + 0x30, -21);
      if (millis() % 1000 < 500)
        display(':', -18);
      display((now_time / 1000) % 10 + 0x30, -13);
      display((now_time / 100) % 10 + 0x30, -8);
      playweeks(week, -2);
      break;
    case 'h':
      if (isnan(h) || isnan(t) )
        return;
      display(t / 10 + 0x30, -24);
      display(t % 10 + 0x30, -19);
      display(95 + 0x20, -14);
      display('C', -9);
      play3x5(h / 10, -1);
      play3x5(h % 10, 3);
      break;
    case 'd':
      if (aa & bb) {
        display(now_time / 1000 + 0x30, -28);
        display((now_time / 100) % 10 + 0x30, -23);
        display('/', -18);
        display((now_time / 10) % 10 + 0x30, -12);
        display(now_time % 10 + 0x30, -7);
      }
      else if (!aa & bb) {
        display((now_time / 100) % 10 + 0x30, -24);
        display('/', -19);
        display((now_time / 10) % 10 + 0x30, -13);
        display(now_time % 10 + 0x30, -8);
      }
      else if (aa & !bb) {
        display(now_time / 1000 + 0x30, -25);
        display((now_time / 100) % 10 + 0x30, -20);
        display('/', -15);
        display(now_time % 10 + 0x30, -9);
      }
      else {
        display((now_time / 100) % 10 + 0x30, -22);
        display('/', -17);
        display(now_time % 10 + 0x30, -11);
      }
      playweeks(week, -2);
      break;
    case 'y':
      display(now_time / 1000 + 0x30, -26);
      display((now_time / 100) % 10 + 0x30, -20);
      display((now_time / 10) % 10 + 0x30, -14);
      display(now_time % 10 + 0x30, -8);
      break;
    default :
      break;
  }
}
void without_rtc_mode_detect() {
  if (rising_edge(2)) {
    mode = 7;
    now = wifiClk.GetDateTime();
    time_mod=now.Hour()*10000.0+now.Minute()*100+now.Second();
    week = redate(now.Month() * 100 + now.Day(), now.Year() + 2000);
    t = dht.readTemperature();
    h = dht.readHumidity();
  }
  if (long_press(1)) {
    time_mod = ((time_mod) / 100 + 1) * 100;
    if (time_mod % 10000 >= 6000) time_mod += 4000;
    if (time_mod > 235959)        time_mod = 0;
    mode = 2;
  }
  if (long_press(0)) {
    time_mod = ((time_mod) / 100 - 1) * 100;
    if (time_mod < 0)             time_mod = 235900;
    if (time_mod % 10000 > 6000)  time_mod -= 4000;
    mode = 2;
  }
}
void rtc_mode_detect() {
  if (long_press(0))mode = 7, week = redate(now.Month() * 100 + now.Day(), now.Year() + 2000);
  else if (long_press(1))mode = 0;
  else if (long_press(2))mode = 2;
}
void without_rtc_mode() {
  if (time_mod % 100 == 60)time_mod += 40;
  #ifdef wifi
    if (time_mod % 10000 == 6000){
      now=wifiClk.GetDateTime();
      week = redate(now.Month() * 100 + now.Day(), now.Year() + 2000);
      time_mod=now.Hour()*10000.0+now.Minute()*100+now.Second();
    }
  #else
    if (time_mod % 10000 == 6000){
      time_mod+=4000;
    }
  #endif
    
  if (time_mod > 235959){
    week = redate(now.Month() * 100 + now.Day(), now.Year() + 2000);
    time_mod = 0;
  }
}
void rtc_mode() {
  time_mod = now.Hour() * 10000.0 + now.Minute() * 100 + now.Second(); //*10000.0先轉乘double才不會爆
}

void loop() {
  without_rtc_mode_detect();
  if (mode < 2)
    screen(0, 'h');
  else if (mode < 6)
    screen(time_mod, 't');
  else if (mode < 9)
    screen(now.Year() + 2000, 'y');
  else if (mode < 11)
    screen(now.Month() * 100 + now.Day(), 'd');
  if (clk != millis() / 1000) {
    bright = analogRead(cds);
    time_mod++;
    mode++;
    if (mode == 6 || mode == 11) {
      mode = 0;
      int temp = dht.readTemperature();
      if ( abs(t-temp)< 2 )
        t = temp;
      temp = dht.readHumidity();
      if ( abs(h-temp)< 7 )
        h = temp;
      Serial.print("Temperature: ");
      Serial.println(t);
      Serial.print("Humidity: ");
      Serial.println(h);
      
      
    }
    clk = millis() / 1000;
    without_rtc_mode();
  }
}
*/







