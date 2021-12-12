
#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(9);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  
  Serial.print("Humidity, ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Temperature, ");
  Serial.print(temperature);
  Serial.println("C");
}
