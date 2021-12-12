
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>

Servo myservo;
const int BuzzerPin = 7;
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int beepCount = 0;
float mm;

LiquidCrystal_I2C lcd(0x3F,20,4);
//---------------------------------------------------------------------
void setup() {
  //Serial.begin(9600);
  myservo.attach(1);
  myservo.write (0);
  lcd.begin();
  lcd.home();
  pinMode(trigPin, OUTPUT);
  //pinMode(BuzzerPin,OUTPUT);
  pinMode(echoPin, INPUT);
  delay (1000);
  

}
//-----------------------------------------------------------------------
void loop() 
{
//--------------------------------------------------------    
    
    ultrasonic();
    LCD();
    delay(50);
    myservo.write(0);
    ultrasonic();
    LCD();
    delay(50);
    ultrasonic();
    LCD();
    delay(1000);
    myservo.write(90);
    ultrasonic();
    LCD();
    delay(50);
    ultrasonic();
    LCD();
    delay(1000);
    myservo.write(180);
    ultrasonic();
    LCD();
    delay(50);
    ultrasonic();
    LCD();
    delay(1000);
//------------------------------------------------------------    
}


//----------------------------------------------------------------------
void loopservo()
{
  myservo.write(0);
  delay(1000);
  myservo.write(30);
  delay(1000);
  myservo.write(60);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(120);
  delay(1000);
  myservo.write(150);
  delay(1000);
  myservo.write(180);
  delay(1000);
  myservo.write(150);
  delay(1000);
  myservo.write(120);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(60);
  delay(1000);
  myservo.write(30);
  delay(1000);
  myservo.write(0);
  delay(1000);
}
//--------------------------------------------------------------------  
void beep(int distance){

  beepCount += 12;
  if (beepCount / (distance * 10) > 1) {
    digitalWrite(BuzzerPin, LOW);
    beepCount = 0;
  }else if (beepCount > 50){
    digitalWrite(BuzzerPin, HIGH);
  }
}
//---------------------------------------------------------------------
void ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  mm = distance / 100.00;
}
//----------------------------------------------------------------------
void LCD()
{
  lcd.clear();
  delay(50);
  lcd.setCursor(6,0);
  lcd.print("Group:08");
  lcd.setCursor(1,1);
  lcd.print("Distance: ");
  lcd.setCursor(11,1);
  lcd.print(distance);
  lcd.setCursor(18,1);
  lcd.print("cm");
  lcd.setCursor(1,2);
  lcd.print("Distance: ");
  lcd.setCursor(11,2);
  lcd.print(mm);
  lcd.setCursor(18,2);
  lcd.print("mm");
}
