#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);
int potpin = 0; // analog pin used to connect the potentiometer
int val;        // variable to read the value from the analog pin
int trigPin = 9;
int echoPin = 10;
float duration_usec;
int distance_mm;

Servo myservoH, myservoV;           // create servo object to control a servo
                                    // a maximum of eight servo objects can be created
int pos = 0;                        // variable to store the servo position
void setup()
{
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  digitalWrite(trigPin,LOW);
  lcd.begin();
  Serial.begin(9600);
  myservoH.attach(6);                // attaches the servo on pin 6 to the servo object
  myservoV.attach(5);
}
 
void loop()
{
  val = analogRead(potpin);        // reads the value of the potentiometer (value // between 0 and 1023)
  val = map(val, 0, 1023, 0, 179); // scale it to use it with the servo (value
                                   // between 0 and 180)
  myservoH.write(val);              // sets the servo position according to the
                                   // scaled value
  duration_usec = ping();
  distance_mm = (17*duration_usec)/100;
  delay(10);                       // waits 15ms for the servo to reach the position
  disp();
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

void disp()
{
  Serial.print("Distance: ");
  Serial.print(distance_mm / 10);
  Serial.print('.' );
  Serial.print(distance_mm % 10);
  Serial.println(" cm");
  lcd.home();
  lcd.setCursor(0,2);
  lcd.print("Distance            ");
  lcd.setCursor(12,2);
  lcd.print(distance_mm / 10);
  lcd.print('.');
  lcd.print(distance_mm % 10);
  lcd.setCursor(18,2);
  lcd.print("cm");
  delay(300);
}


