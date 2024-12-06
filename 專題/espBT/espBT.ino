#include<BluetoothSerial.h>
BluetoothSerial espBT;
void setup() { 
  espBT.begin("esp32"); 
  Serial.begin(115200);
}
char a[]="hajimemashita,\nyoloshikuonegaishimaz\n";
void loop() {
  // put your main code here, to run repeatedly:
  if(espBT.available()){
    int value=espBT.read();
    if(value>=0x20&&value<0x80)
      Serial.print(char(value));
  }
  delay(20);
}
