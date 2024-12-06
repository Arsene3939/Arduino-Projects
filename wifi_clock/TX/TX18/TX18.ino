void setup() {
  // put your setup code here, to run once:
  Serial1.begin(4800);
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial1.write('i');
  delay(200);
}
