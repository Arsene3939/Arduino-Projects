 #include <LiquidCrystal.h>
 #include <DHT.h>
 LiquidCrystal lcd(2, 3, 5, 6, 7, 8);
 #define pin 4
 #define type DHT11
 DHT dht(pin, type);
 void setup() {
 lcd.begin(16,2);
 dht.begin();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("hellow word");
 delay(1000);
 lcd.clear();
 lcd.print("I can use");
 delay(1000);
 lcd.setCursor(0,1);
 lcd.print("LCD screen");
 delay(1000);
 }
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t) ) 
    return;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.print("*C");
  delay(2000);
}
