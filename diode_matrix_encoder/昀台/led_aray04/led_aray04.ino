#include "ledAray .h"
ledAray LL;
void setup() {
  LL.setLEDC(10,3,2,7,15,8,12,13);
  LL.setLEDL(14,4,16,5,9,17,11,6);
  LL.begin();
}
void loop() {
   LL.marquee(40,"held");
}
  
