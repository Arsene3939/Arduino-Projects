// Using Arduino as the master for application of SD178BM-I2C
// Refer to the "slave_receiver" example for use with this
#include <Wire.h>
 
const int SLAVE_ADDRESS = 0x20;  // SLAVE ADDRESS of SD178B

// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

 byte x[13] = {
  0x8A,0x00,                  // set SD178BM output pins MO[2:0] = 0b000
  0x8A,0x04,                  // set SD178BM output pins MO[2:0] = 0b100
  0x86,0xC0,
  0x88,0x27,0x0C,0x00,0x02,   // 播放 microSD 9998.WAV 2遍
  0x8A,0x00                   // set SD178BM output pins MO[2:0] = 0b000
 };

// the loop function runs over and over again forever
void loop() {
  delay(10); // waits 10ms
  Wire.beginTransmission(SLAVE_ADDRESS); // transmit to slave device
  Wire.write(x,13);
  Wire.endTransmission();     // stop transmitting
}
