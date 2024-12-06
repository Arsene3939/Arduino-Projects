#include "easyTimer.h"
#include <DHT.h>
//#include <IRremote.h>
#include<SoftwareSerial.h>
#define pin 12
#define type DHT11
#define changingSpeed 3
#define brightPower 350
SoftwareSerial uart(13,11);//RX,TX
DHT dht(pin, type);
byte t=3;
uint8_t LEDC[24] = {24, 25, 27, 23, 29, 22, 26, 28, 34, 31, 33, 37, 35, 36, 32, 30, 42, 39, 41, 38, 43, 40, 44, 45};
uint8_t LEDL[8] = {51, 49, 53, 47, 48, 52, 46, 50};
uint8_t _LEDC[8]={15,4,5,18,7,14,16,17};
uint8_t _LEDL[8]={6,3,A4,A5,21,2,20,19};
uint8_t uartData[4]={0,0,0,0},uartCount=0;
uint8_t f=A2;
uint8_t Q=A3;
uint8_t BW=A1;
bool    LC[24][8];
bool   _LC[8][8];
uint8_t timesCount=0;
uint8_t changeLine=0;
uint8_t hour =23-1;
uint8_t Min=8;
uint8_t delayTime=80;
uint8_t H,m;
uint64_t _time=0;
uint8_t mode=0;
uint8_t DHTmode=0;
boolean V=0,v=1,Val=1;
uint8_t i=0,j=0;
int8_t I=0;
//c:x,l:y
void turnlightalloff()
{
  for (int i = 0; i < 24; i++)
    for (int j = 0; j < 8; j++)
      if (LC[i][j]) {
        digitalWrite(LEDL[j], 0);
        digitalWrite(LEDC[i], 1);
        LC[i][j] = 0;
      }
}
void _turnlightalloff()
{
  for(int i=0;i<8;i++){
    digitalWrite(_LEDL[i], 0);
    digitalWrite(_LEDC[i], 1);    
  }
  for (int i = 0; i < 24; i++)
    for (int j = 0; j < 8; j++)
      _LC[i][j] = 0;
}
void light(int x, int y)
{
  if (x > 23 || y > 7 || x < 0 || y < 0)return ;
  turnlightalloff();
  digitalWrite(LEDL[y], 1);
  digitalWrite(LEDC[x], 0);
  udelay(55);
  LC[x][y] = 1;
}
void _light(int x, int y)
{
  _turnlightalloff();
  digitalWrite(_LEDL[y], 1);
  digitalWrite(_LEDC[x], 0);
  _LC[x][y] = 1;
}
void lightsquare(int x, int y, int X, int Y)
{
  if (x > 23 || y > 7 || x < 0 || y < 0)return;
  turnlightalloff();
  for (int i = x; i <= X; i++)
    digitalWrite(LEDC[i], 0);
  for (int j = y; j <= Y; j++)
    digitalWrite(LEDL[j], 1);
  udelay(350);
  for (int i = x; i <= X; i++)
    for (int j = y; j <= Y; j++)
       LC[i][j] = 1;
}
void _lightsquare(int x, int y, int X, int Y)
{
  _turnlightalloff();
  for (int i = x; i <= X; i++)
    digitalWrite(_LEDC[i], 0);
  for (int j = y; j <= Y; j++)
    digitalWrite(_LEDL[j], 1);
  for (int i = x; i <= X; i++)
    for (int j = y; j <= Y; j++)
       _LC[i][j] = 1;
}
void line(int x, int y, int X) {
  if (x > X)
    for (int i = x; i >= X; i--)
    {
      light(i, y);
      y++;
    }
  if (X > x)
    for (int i = x; i <= X; i++)
    {
      light(i, y);
      y++;
    }
}
void lightbox(int x, int y, int X, int Y)
{
  for (int i = x; i <= X; i++)
  {
    light(i, y);
    light(i, Y);
  }
  for (int j = y + 1; j <= Y - 1; j++)
  {
    light(x, j);
    light(X, j);
  }
}
void turnofflight(int x, int y)
{
  digitalWrite(LEDL[y], 0);
  digitalWrite(LEDC[x], 1);
}
void turnofflightsquare(int x, int y, int X, int Y)
{
  for (int i = x; i <= X; i++)
    for (int j = y; j <= Y; j++)
    {
      turnofflight(i, j);
    }
}
void zero(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 6 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 7 + l, 4 + c, 7 + l);
}
void one(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(4 + c, 2 + l, 4 + c, 7 + l);
  light(3 + c, 6 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
}
void two(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  light(2 + c, 6 + l);
  light(3 + c, 2 + l);
  light(4 + c, 3 + l);
  light(3 + c, 7 + l);
  light(4 + c, 7 + l);
  lightsquare(5 + c, 4 + l, 5 + c, 6 + l);
  lightsquare(2 + c, 1 + l, 5 + c, 1 + l);
}
void three(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  light(3 + c, 4 + l);
  light(4 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 4 + c, 7 + l);
  lightsquare(5 + c, 5 + l, 5 + c, 6 + l);
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 3 + l);
  light(2 + c, 2 + l);
  light(2 + c, 6 + l);
}
void four(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(5 + c, 1 + l, 5 + c, 7 + l);
  line(2 + c, 4 + l, 4 + c);
  lightsquare(2 + c, 3 + l, 4 + c, 3 + l);
  light(6 + c, 3 + l);
}
void five(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 4 + l);
  light(2 + c, 2 + l);
  lightsquare(2 + c, 5 + l, 4 + c, 5 + l);
  light(2 + c, 6 + l);
  lightsquare(2 + c, 7 + l, 5 + c, 7 + l);
}
void six(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 3 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 4 + l, 4 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 4 + c, 7 + l);
  light(5 + c, 6 + l);
}
void seven(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2+c,6+l,2+c,7+l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  lightsquare(5+c,5+l,5+c,6+l);
  lightsquare(4+c,1+l,4+c,4+l);
}
void eight(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 3 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 3 + l);
  lightsquare(2 + c, 5 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 4 + l, 4 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 4 + c, 7 + l);
  lightsquare(5 + c, 5 + l, 5 + c, 6 + l);
}
void nine(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 5 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 4 + l, 4 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 4 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 6 + l);
  light(2 + c, 2 + l);
}
void Af(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  light(4 + c, 7 + l);
  light(3 + c, 6 + l);
  light(5 + c, 6 + l);
  light(2 + c, 5 + l);
  light(6 + c, 5 + l);
  lightsquare(2 + c, 1 + l, 2 + c, 4 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 4 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
}
void Bf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  light(6 + c, 2 + l);
  light(6 + c, 3 + l);
  light(6 + c, 5 + l);
  light(6 + c, 6 + l);
}
void Cf(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  light(6 + c, 2 + l);
  light(6 + c, 6 + l);
}
void Df(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 3 + l, 6 + c, 5 + l);
  light(5 + c, 2 + l);
  light(5 + c, 6 + l);
  light(4 + c, 1 + l);
  light(3 + c, 1 + l);
  light(4 + c, 7 + l);
  light(3 + c, 7 + l);
}
void Ef(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 6 + c, 1 + l);
  lightsquare(2 + c, 7 + l, 6 + c, 7 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
}
void Ff(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 7 + l, 6 + c, 7 + l);
  lightsquare(2 + c, 1 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
}
void Gf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(4 + c, 4 + l, 6 + c, 4 + l);
  light(6 + c, 6 + l);
  light(6 + c, 2 + l);
  light(6 + c, 3 + l);
}
void Hf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 7 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
}
void If(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    light(3 + c, 7 + l);
    light(5 + c, 7 + l);
    light(3 + c, 1 + l);
    light(5 + c, 1 + l);
    lightsquare(4 + c, 1 + l, 4 + c, 7 + l);
  }
}
void Jf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(5 + c, 2 + l, 5 + c, 6 + l);
  lightsquare(4 + c, 7 + l, 6 + c, 7 + l);
  light(2 + c, 2 + l);
  light(3 + c, 1 + l);
  light(4 + c, 1 + l);
}
void Kf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  line(3 + c, 4 + l, 6 + c);
  line(6 + c, 1 + l, 4 + c);
}
void Lf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 6 + c, 1 + l);
}
void Mf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 7 + l);
  lightsquare(4 + c, 4 + l, 4 + c, 5 + l);
  light(3 + c, 6 + l);
  light(5 + c, 6 + l);
}
void Nf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 7 + l);
  line(5 + c, 3 + l, 3 + c);
}
void Of(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 6 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
}
void Pf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  light(6 + c, 6 + l);
  light(6 + c, 5 + l);
}
void Qf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 6 + l);
  lightsquare(3 + c, 1 + l, 4 + c, 1 + l);
  lightsquare(6 + c, 3 + l, 6 + c, 6 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  line(6 + c, 1 + l, 4 + c);
}
void Rf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  light(6 + c, 6 + l);
  light(6 + c, 5 + l);
  line(6 + c, 1 + l, 4 + c);
}
void Sf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
  lightsquare(3 + c, 7 + l, 6 + c, 7 + l);
  light(2 + c, 5 + l);
  light(2 + c, 6 + l);
  light(6 + c, 2 + l);
  light(6 + c, 3 + l);
}
void Tf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 7 + l, 6 + c, 7 + l);
  lightsquare(4 + c, 1 + l, 4 + c, 6 + l);
}
void Uf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
}
void Vf(int c = 0, int l = 0)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  light(4 + c, 1 + l);
  lightsquare(2 + c, 3 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 3 + l, 6 + c, 7 + l);
  lightsquare(3 + c, 2 + l, 3 + c, 3 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 3 + l);
}
void Wf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 7 + l);
  lightsquare(4 + c, 2 + l, 4 + c, 5 + l);
  light(3 + c, 1 + l);
  light(5 + c, 1 + l);
}
void Xf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  line(2 + c, 2 + l, 6 + c);
  line(6 + c, 2 + l, 5 + c);
  line(3 + c, 5 + l, 2 + c);
  light(2 + c, 1 + l);
  light(2 + c, 7 + l);
  light(6 + c, 7 + l);
  light(6 + c, 1 + l);
}
void Yf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 5 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 5 + l, 6 + c, 7 + l);
  lightsquare(4 + c, 1 + l, 4 + c, 3 + l);
  light(3 + c, 4 + l);
  light(5 + c, 4 + l);
}
void Zf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 7 + l, 6 + c, 7 + l);
  lightsquare(2 + c, 1 + l, 6 + c, 1 + l);
  line(2 + c, 2 + l, 6 + c);
}
void af(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  lightsquare(3 + c, 5 + l, 5 + c, 5 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 4 + l);
  light(2 + c, 2 + l);
}
void bf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 4 + l);
  light(3 + c, 4 + l);
  light(5 + c, 5 + l);
  light(4 + c, 5 + l);
}
void cf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 5 + l, 5 + c, 5 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 4 + l);
  light(6 + c, 2 + l);
}
void df(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c + 4, 1 + l, 2 + 4 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(6 - 4 + c, 2 + l, 6 - 4 + c, 4 + l);
  light(5 + c, 4 + l);
  light(4 + c, 5 + l);
  light(3 + c, 5 + l);
}
void ef(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 3 + l, 6 + c, 3 + l);
  lightsquare(3 + c, 5 + l, 5 + c, 5 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 4 + l);
  light(6 + c, 4 + l);
}
void ff(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 3 + c, 6 + l);
  light(6 + c, 6 + l);
  light(5 + c, 7 + l);
  light(4 + c, 7 + l);
  light(2 + c, 4 + l);
  light(4 + c, 4 + l);
}
void gf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  lightsquare(3 + c, 6 + l, 5 + c, 6 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 6 + l);
  light(2 + c, 4 + l);
  light(2 + c, 5 + l);
}
void hf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 4 + l);
  light(3 + c, 4 + l);
  light(4 + c, 5 + l);
  light(5 + c, 5 + l);
}
void iF(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(4 + c, 1 + l, 4 + c, 5 + l);
  light(3 + c, 5 + l);
  light(4 + c, 7 + l);
  light(3 + c, 1 + l);
  light(5 + c, 1 + l);
}
void jf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  light(5 + c, 7 + l);
  light(2 + c, 2 + l);
  light(3 + c, 1 + l);
  light(4 + c, 1 + l);
  light(4 + c, 5 + l);
  lightsquare(5 + c, 2 + l, 5 + c, 5 + l);
}
void kf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 7 + l);
  line(3 + c, 3 + l, 5 + c);
  light(4 + c, 2 + l);
  light(5 + c, 1 + l);
}
void lf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(4 + c, 2 + l, 4 + c, 7 + l);
  light(3 + c, 7 + l);
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
}
void mf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 5 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 4 + l);
  light(3 + c, 5 + l);
  light(5 + c, 5 + l);
  light(4 + c, 4 + l);
  light(4 + c, 3 + l);
}
void nf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 5 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 4 + l);
  light(5 + c, 5 + l);
  light(3 + c, 4 + l);
  light(4 + c, 5 + l);
}
void of(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 4 + l);
  lightsquare(3 + c, 5 + l, 5 + c, 5 + l);
  lightsquare(2 + c, 2 + l, 2 + c, 4 + l);
}
void pf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 5 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  lightsquare(3 + c, 5 + l, 5 + c, 5 + l);
  light(6 + c, 4 + l);
}
void qf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(6 + c, 1 + l, 6 + c, 5 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  light(2 + c, 4 + l);
  light(3 + c, 5 + l);
  light(4 + c, 5 + l);
  light(5 + c, 4 + l);
}
void rf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 2 + c, 5 + l);
  light(3 + c, 4 + l);
  light(5 + c, 5 + l);
  light(4 + c, 5 + l);
  light(6 + c, 4 + l);
}
void sf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  lightsquare(3 + c, 5 + l, 6 + c, 5 + l);
  light(2 + c, 4 + l);
  light(6 + c, 2 + l);
}
void tf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 2 + l, 3 + c, 7 + l);
  light(4 + c, 1 + l);
  light(4 + c, 5 + l);
  light(2 + c, 5 + l);
  light(6 + c, 2 + l);
  light(5 + c, 1 + l);
}
void uf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 5 + l);
  lightsquare(6 + c, 1 + l, 6 + c, 5 + l);
  light(4 + c, 1 + l);
  light(5 + c, 2 + l);
  light(3 + c, 1 + l);
}
void vf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 3 + l, 2 + c, 5 + l);
  lightsquare(6 + c, 3 + l, 6 + c, 5 + l);
  light(4 + c, 1 + l);
  light(5 + c, 2 + l);
  light(3 + c, 2 + l);
}
void wf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 2 + l, 2 + c, 5 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 5 + l);
  light(3 + c, 1 + l);
  light(5 + c, 1 + l);
  light(4 + c, 2 + l);
  light(4 + c, 3 + l);
}
void xf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  line(2 + c, 1 + l, 6 + c);
  line(6 + c, 1 + l, 5 + c);
  line(3 + c, 4 + l, 2 + c);
}
void yf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 5 + c, 1 + l);
  lightsquare(6 + c, 2 + l, 6 + c, 5 + l);
  lightsquare(3 + c, 3 + l, 5 + c, 3 + l);
  light(2 + c, 4 + l);
  light(2 + c, 5 + l);
}
void zf(int c = 0, int l = 0) {
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(2 + c, 1 + l, 6 + c, 1 + l);
  lightsquare(2 + c, 5 + l, 6 + c, 5 + l);
  line(3 + c, 2 + l, 5 + c);
}
void _1(int c = 0, int l = 0) //!
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    lightsquare(4 + c, 4 + l, 4 + c, 7 + l);
    light(4 + c, 1 + l);
  }
}
void _2(int c = 0, int l = 0) //%
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  line(2 + c, 2 + l, 6 + c);
  lightsquare(2 + c, 6 + l, 3 + c, 7 + l);
  lightsquare(5 + c, 1 + l, 6 + c, 2 + l);
}
void _3(int c = 0, int l = 0) //&
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  line(6 + c, 1 + l, 2 + c);
  light(6 + c, 3 + l);
  light(3 + c, 1 + l);
  light(2 + c, 2 + l);
  light(2 + c, 3 + l);
  light(4 + c, 5 + l);
  light(2 + c, 6 + l);
  light(3 + c, 7 + l);
  light(4 + c, 7 + l);
  light(5 + c, 6 + l);
}
void _4(int c = 0, int l = 0) //(
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    line(3 + c, 5 + l, 5 + c);
    line(5 + c, 1 + l, 3 + c);
    light(3 + c, 4 + l);
  }
}
void _5(int c = 0, int l = 0) //)
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    line(3 + c, 1 + l, 5 + c);
    line(5 + c, 5 + l, 3 + c);
    light(5 + c, 4 + l);
  }
}
void _6(int c = 0, int l = 0) //+
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    lightsquare(2 + c, 4 + l, 6 + c, 4 + l);
    light(4 + c, 2 + l);
    light(4 + c, 3 + l);
    light(4 + c, 5 + l);
    light(4 + c, 6 + l);
  }
}
void _7(int c = 0, int l = 0) //=
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    lightsquare(2 + c, 5 + l, 6 + c, 5 + l);
    lightsquare(2 + c, 3 + l, 6 + c, 3 + l);
  }
}
void _8(int c = 0, int l = 0) //-
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 6; i++)
    lightsquare(3 + c, 4 + l, 5 + c, 4 + l);
}
void _9(int c = 0, int l = 0) //~
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 7; i++) {
    line(5 + c, 3 + l, 3 + c);
    light(2 + c, 4 + l);
    light(6 + c, 4 + l);
  }
}
void _10(int c = 0, int l = 0) //?
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 7 + l, 5 + c, 7 + l);
  light(6 + c, 6 + l);
  light(2 + c, 6 + l);
  light(6 + c, 5 + l);
  light(5 + c, 4 + l);
  light(4 + c, 3 + l);
  light(4 + c, 1 + l);
}
void _11(int c = 0, int l = 0) //:
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    lightsquare(3 + c, 5 + l, 4 + c, 6 + l);
    lightsquare(3 + c, 2 + l, 4 + c, 3 + l);
  }
}
void _12(int c = 0, int l = 0) //;
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    lightsquare(3 + c, 5 + l, 4 + c, 6 + l);
    light(3 + c, 3 + l);
    light(4 + c, 2 + l);
    light(4 + c, 3 + l);
    light(3 + c, 1 + l);
  }
}
void _13(int c = 0, int l = 0) //>
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    line(3 + c, 1 + l, 6 + c);
    line(5 + c, 5 + l, 3 + c);
  }
}
void _14(int c = 0, int l = 0) //<
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 2; i++) {
    line(2 + c, 4 + l, 5 + c);
    line(5 + c, 1 + l, 3 + c);
  }
}
void _15(int c = 0, int l = 0) //,
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 4; i++) {
    lightsquare(4 + c, 3 + l, 5 + c, 3 + l);
    light(5 + c, 2 + l);
    light(4 + c, 1 + l);
  }
}
void _16(int c = 0, int l = 0) //.
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  for (int i = 0; i < 4; i++) {
    lightsquare(4 + c, 1 + l, 5 + c, 2 + l);
  }
}
void _17(int c = 0, int l = 0) //#
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3 + c, 1 + l, 3 + c, 7 + l);
  lightsquare(5 + c, 1 + l, 5 + c, 7 + l);
  light(2 + c, 5 + l);
  light(4 + c, 5 + l);
  light(6 + c, 5 + l);
  light(2 + c, 3 + l);
  light(4 + c, 3 + l);
  light(6 + c, 3 + l);
}
void _18(int c = 0, int l = 0) //○
{
  if (c > 21 || l > 7 || c < -6 || l < 0)return;
  lightsquare(3+c,5+l,5+c,5+l);
  lightsquare(3+c,7+l,5+c,7+l);
  turnlightalloff();
  light(3+c,6+l);
  light(5+c,6+l);
}
void heart0() {
  for (int i = 0; i < t * 2; i++) {
    line(3, 0, 0);
    line(4, 1, 6);
    line(0, 4, 1);
    line(6, 4, 5);
    line(3, 4, 2);
    line(0, 4, 1);
    light(4, 5);
  }
}
void heart1() {
  for (int i = 0; i < t * 1.6; i++) {
    line(3, 1, 1);
    line(4, 2, 5);
    line(3, 3, 2);
    light(4, 4);
  }
}
void heart2() {
  for (int i = 0; i < t * 1.35; i++) {
    line(3, 2, 2);
    light(4, 3);
  }
}
void changer(uint8_t N,int8_t C){
  switch(N){
    case 0:
      zero(C,0);
      turnlightalloff();
      break;
    case 1:
      one(C,0);
      turnlightalloff();
      break;
    case 2:
      two(C,0);
      turnlightalloff();
      break;
    case 3:
      three(C,0);
      turnlightalloff();
      break;
    case 4:
      four(C,0);
      turnlightalloff();
      break;
    case 5:
      five(C,0);
      turnlightalloff();
      break;
    case 6:
      six(C,0);
      turnlightalloff();
      break;
    case 7:
      seven(C,0);
      turnlightalloff();
      break;
    case 8:
      eight(C,0);
      turnlightalloff();
      break;
    case 9:
     nine(C,0);
     turnlightalloff();
     break;
   default:
     _10(C,0);//?
     turnlightalloff();
     break;
  }
}
void Time(uint8_t timeArray[4]){
  uint8_t ctrl=0;
  for(int i=0;i<4;i++){
    changer(timeArray[i],-1+i*5+ctrl);
    if(i==1){
      _11(8,0);  
      ctrl=3;
    }
  }
}
void getTemperature(int8_t Temperature){
  for(int j=0;j<2;j++){
    for(int i=0;i<2;i++)
      changer(int(Temperature/(pow(10,i)))%10,5-i*6);
    _18(11,0);
  }
  Cf(16,0);   
}
void getHumidity(int8_t Humidity){
  for(int j=0;j<2;j++){
    for(int i=0;i<2;i++)
      changer(int(Humidity/(pow(10,i)))%10,6-i*6);
  }
  _2(13,0);   
}
void led_print(char string[])
{
  int8_t space = 0;
  int lenth = strlen(string)*6;
  bool L = 0;
  for (int C=21;C>-7-lenth;C--) {
    for (int i=0;i<t;i++) {
      for (int count = 0; count < strlen(string); count++) {
        bool plusSw=digitalRead(f);
        if(plusSw){
          v=0;
          return;
        }
        switch (string[count])
        {
          case '0':
            zero(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '1':
            one(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '2':
            two(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '3':
            three(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '4':
            four(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '5':
            five(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '6':
            six(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '7':
            seven(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '8':
            eight(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '9':
            nine(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'A':
            Af(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'B':
            Bf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'C':
            Cf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'D':
            Df(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'E':
            Ef(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'F':
            Ff(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'G':
            Gf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'H':
            Hf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'I':
            If(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'J':
            Jf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'K':
            Kf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'L':
            Lf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'M':
            Mf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'N':
            Nf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'O':
            Of(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'P':
            Pf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'Q':
            Qf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'R':
            Rf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'S':
            Sf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'T':
            Tf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'U':
            Uf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'V':
            Vf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'W':
            Wf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'X':
            Xf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'Y':
            Yf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'Z':
            Zf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'a':
            af(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'b':
            bf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'c':
            cf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'd':
            df(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'e':
            ef(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'f':
            ff(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'g':
            gf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'h':
            hf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'i':
            iF(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'j':
            jf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'k':
            kf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'l':
            lf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'm':
            mf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'n':
            nf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'o':
            of(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'p':
            pf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'q':
            qf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'r':
            rf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 's':
            sf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 't':
            tf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'u':
            uf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'v':
            vf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'w':
            wf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'x':
            xf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'y':
            yf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case 'z':
            zf(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '!':
            _1(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '%':
            _2(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '&':
            _3(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '(':
            _4(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case ')':
            _5(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '+':
            _6(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '=':
            _7(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '-':
            _8(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '~':
            _9(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '?':
            _10(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case ':':
            _11(C + count * 6 - space, L);
            space = space + 2;
            turnlightalloff();
            break;
          case ';':
            _12(C + count * 6 - space, L);
            space = space + 2;
            turnlightalloff();
            break;
          case '>':
            _13(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '<':
            _14(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case ',':
            _15(C + count * 6 - space, L);
            turnlightalloff();
            break;
          case '.':
            _16(C + count * 6 - space, L);
            space = space + 2;
            turnlightalloff();
            break;
          case '#':
            _17(C + count * 6 - space, L);
            turnlightalloff();
            break;
          default:
            for (int i = 0; i < 16; i++) {}
            space = space + 4;
            turnlightalloff();
            break;
        }
      }
      space = 0;
    }
  }
}
void remind(byte Hr,byte minute,byte controlTimeFastOrSlow,char string_[],byte ifdef=60){
  t=controlTimeFastOrSlow;
  if(m>=minute&&m<=ifdef&&H==Hr&&_time%30==0&v&!Val){
      mode=4;
      DHTmode=4;
      if(timesCount>7)timesCount=0,changeLine++;
      if(changeLine>7)changeLine=0;
      _light(timesCount,7-changeLine);
      led_print(string_);
      timesCount++;
    }
  if(m==minute-1&&H==Hr)v=1,timesCount=0,changeLine=0;
}
void uart_decode(){
  if(uart.available()){
    uint8_t uartRead=int(uart.read());
    uint8_t debug=abs(uartData[uartCount]-uartRead);
    if(_time%1806<150)Val=1;
    else Val=0;
    if(uartRead!='i'&&(debug<2||debug==9||debug==5||(H==23&&m==59)|V|Val)){
        uartData[uartCount]=uartRead;
        uartCount++;
    }
    else uartCount=0;
    m=uartData[2]*10+uartData[3];
    H=uartData[0]*10+uartData[1];
  }
}
char str[]="You have a study today";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uart.begin(115200);
  dht.begin();
  for (int i = 0; i < 24; i++) {
    pinMode(LEDC[i], OUTPUT);
    digitalWrite(LEDC[i], 1);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(LEDL[i], OUTPUT);
    digitalWrite(LEDL[i], 0);
    pinMode(_LEDL[i], OUTPUT);
    digitalWrite(_LEDL[i], 0);
    pinMode(_LEDC[i], OUTPUT);
    digitalWrite(_LEDC[i], 1);
  }
  for (int i = 0; i < 24; i++)
    for (int j = 1; j < 8; j++)
      LC[i][j] = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 1; j < 8; j++)
      _LC[i][j] = 0;
}
void loop() {
  //led_print("ABCDEFGHIJKLMNOPQRSTUVWXYX abcdefghijklmnopqrstuvwxyz 0123456789 !#%&()-+=:;<>?,.");
  _time++;
  if(_time>0xFFFFFFFFFFFFFFFF)_time=0;
  bool hrSw=digitalRead(BW);
  bool plusSw=digitalRead(f);
  bool costSw=digitalRead(Q);
  float hu = dht.readHumidity();
  float tp = dht.readTemperature();
  if(mode==0){
    if(_time%changingSpeed==0){
      _turnlightalloff();  
      _lightsquare(0,0,I,I);
      I++;
      if(I>7)mode++,I=1; 
    }
  }
  if(mode==1){
    if(_time%changingSpeed==0){
      _turnlightalloff();
      _lightsquare(I,I,7,7);   
      I++;  
      if(I>7)mode++,I=7;
    }
  }
  if(mode==2){
    if(_time%changingSpeed==0){
      _turnlightalloff();
      _lightsquare(I,I,7,7);
      I--;  
      if(I<0)mode++,I=7;
    } 
  }
  if(mode==3){
    if(_time%changingSpeed==0){
      _turnlightalloff();
      _lightsquare(0,0,I,I);   
      I--;  
      if(I<0)mode++,I=0;
    }
  }
  if(mode>3){
    mode=0;
  }
//remind(hour,minute,speed,remind sentence,redefineTime)
  remind(6,10,3,str,30);
  remind(6,30,3,"go to eat breakfast!");
  remind(11,30,3,"go to have lunch");
  remind(17,30,3,",go to have dinner!");
  remind(19,1,2,"You should read the magazine",45);
  remind(19,45,3,"It is time to take a bath.");
  remind(21,30,2,"Its already to sleep,make a prepare to sleep!");
  remind(22,1,2,"It is time to sleep and bursh your teeth.",30);
  remind(22,30,3,"You realy shoud go to bed.");
  if(plusSw){
    delay(delayTime);
    V=!V;
    DHTmode=0;
  }
  if(costSw){
    delay(delayTime);
    DHTmode=1;
  }
  if(hrSw){
    delay(delayTime);
    DHTmode=2;
  }
  if(_time%int(600/(DHTmode+1))==0)DHTmode++;
  if(DHTmode>3)DHTmode=0;  
  uart_decode();
  if(V|Val)digitalWrite(LEDL[0],1);
  else digitalWrite(LEDL[0],0);
  if(DHTmode==0)Time(uartData);
  if(DHTmode==1)getTemperature(tp);
  if(DHTmode==2)getHumidity(hu);
}
