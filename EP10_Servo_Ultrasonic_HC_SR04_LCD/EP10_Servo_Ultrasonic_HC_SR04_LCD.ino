

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

int trigPin = 9;
int echoPin = 10;
float duration_usec;
int distance_mm;

void setup() 
{
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  digitalWrite(trigPin,LOW);
  lcd.begin();
  Serial.begin(9600);
}

void loop() 
{
  // v = 340 m/s = (340 * 100)/10^6 cm/usec = 34/1000 cm/usec
  // 2*d = v*t => d = v*t/2 = (17*t)/1000 cm = (17*t)/100 mm.  
    duration_usec = ping();
    distance_mm = (17*duration_usec)/100; 
    
    Serial.print("Distance: ");
    Serial.print(distance_mm / 10);
    Serial.print('.' );
    Serial.print(distance_mm % 10);
    Serial.println(" cm");
    lcd.home();
    lcd.print("      Distance      ");
    lcd.setCursor(6,2);
    lcd.print(distance_mm / 10);
    lcd.print('.');
    lcd.print(distance_mm % 10);
    lcd.setCursor(18,2);
    lcd.print("cm");
    
    delay(300);
}

int ping() 
{
  // send a pulse (at least 10 usec long) to the TRIG pin
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(12); 
  digitalWrite(trigPin, LOW); 
  // measure the ECHO pulse width (in microseconds)
  float duration_usec = pulseIn(echoPin, HIGH);
  return duration_usec;
}
