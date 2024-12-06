byte getcode[3]={21,23,22};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for(int i=0;i<3;i++)
    pinMode(getcode[i],1);
}
byte decoder(){
  byte N=0;
  for(int i=0;i<3;i++){
    N+=(digitalRead(getcode[i]))<<i;
    Serial.print(N);
  }
  Serial.println();
}
void loop() {
  // put your main code here, to run repeatedly:
  decoder();
}
