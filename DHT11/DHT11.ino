#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   lcd.begin();
   lcd.home();
   Serial.begin(9600); 
   Serial.println("DHTxx test!");
   dht.begin();
}
void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);

   if (isnan(h) || isnan(t) || isnan(f)) {
     Serial.println("Failed to read from DHT sensor!");
      return;
   }
   
   Serial.println("     Group 08      "); //1
   Serial.print("Humidity: ");
   Serial.print(     h,1);
   Serial.println("    %");
    
   Serial.print("Temperature: ");
   Serial.print(t,1);
   Serial.println(" C");

   Serial.print("Temperature: ");
   Serial.print(f,1);
   Serial.println(" F");  
   delay(1000);
   
   

  
  lcd.setCursor(6,0);
  lcd.print("Group 08");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.setCursor(13,1);
  lcd.print(h,1);
  lcd.setCursor(19,1);
  lcd.print("%");
  lcd.setCursor(0,2);
  lcd.print("Temperature: "); 
  lcd.setCursor(13,2);
  lcd.print(t,1);
  lcd.setCursor(19,2);
  lcd.print("C");
  lcd.setCursor(0,3);
  lcd.print("Temperature: ");
  lcd.setCursor(13,3);
  lcd.print(f,1);
  lcd.setCursor(19,3);
  lcd.print("F");
}
