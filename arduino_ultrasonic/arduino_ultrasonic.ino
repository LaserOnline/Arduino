#include <LiquidCrystal_I2C.h>

const int trigPin = 9;  //สร้างตัวแปลและบอกว่าต่อขาไหน
const int echoPin = 10;  //สร้างตัวแปลและบอกว่าต่อขาไหน
const int speakerPin = 12; //สร้างตัวแปลและบอกว่าต่อขาไหน

long duration;  //ระยะเวลา
int distance; // ระยะทาง
int beepCount =0; // ระยะของเสียง
LiquidCrystal_I2C lcd(0x3F,20,4);
//---------------------------------------------------------------------
void setup() { // รันครั้งแรก ส่วนมาก นิยมใช้ รันบอกโปรแกรมว่ามีตัวแปลชนิดอะไร 
  pinMode(trigPin, OUTPUT); // ชนิดของตัวแปล
  pinMode(echoPin, INPUT); // ชนิดของตัวแปล
  pinMode(speakerPin, OUTPUT); // ชนิดของตัวแปล
  Serial.begin(9600); // น่าจะบอกความเร็วของการส่งข้อมูลของโปรแกรม
}

void loop() {

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // 0.034 มาจากสูตรของความเร็วเสียง 340
  Serial.print("Distance: ");
  Serial.println(distance); 
  beep(distance); // รับค่าระยะทาง
}

void beep(int distance) {

  beepCount += 12;
  if(beepCount / (distance * 10) > 1){
  digitalWrite(speakerPin, LOW);
  Serial.println("Open");
  beepCount = 0;
}else if(beepCount > 50){
  digitalWrite(speakerPin, HIGH);
  Serial.println("Close");
  }

}
