// Include the required Wire library for I2C<br>
#include <Wire.h>//A4_SDA  A5_SCL
int LED = 13;
int x = 0;
bool flag=0;
byte I2C_bus;
byte image[1024];
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  Serial.begin(57600);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(0x11);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  int i=0;
  while(Wire.available()){
    I2C_bus=Wire.read();
    Serial.println(I2C_bus);
  }
}
void loop() {
  //If value received is 0 blink LED for 200 ms
}
