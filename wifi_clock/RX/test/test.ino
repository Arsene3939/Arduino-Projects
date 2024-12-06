#include "esp32WifiClock.h"
esp32WifiClock wifiClk(A12,A11);
void setup() {
  // put your setup code here, to run once:
  wifiClk.begin(9600);
  Serial.begin(9600);
}
time_s now;
void loop() {
  // put your main code here, to run repeatedly:
  now=wifiClk.getTime();
  //delay(1000);
}
