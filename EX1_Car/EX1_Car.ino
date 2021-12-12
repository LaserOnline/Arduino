#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(9, 10);           // TX | RX  สำหรับรับค่าจาก bluetooth
LiquidCrystal_I2C lcd(0x3F,16,2);

int Speed_Motor_Left = 4;                 // pin สำหรับควบคุมความเร็วมอเตอร์ซ้าย
int Motor_Left_forward = 3;               // pin สำหรับกำหนดทิศทางการหมุนมอเตอร์ด้านซ้าย
int Motor_Left_reward = 5;                // pin สำหรับกำหนดทิศทางการหมุนมอเตอร์ด้านซ้าย
int Motor_Right_forward = 7;              // pin สำหรับกำหนดทิศทางการหมุนมอเตอร์ด้านขวา
int Motor_Right_reward = 2;               // pin สำหรับกำหนดทิศทางการหมุนมอเตอร์ด้านขวา
int Speed_Motor_Right = 6;                // pin สำหรับควบคุมความเร็วมอเตอร์ขวา
int Horn = 11;                            // pin สำหรับแตร
int Speed = 255;                          // ตัวแปรสำหรับเก็บค่าความเร็ว

void setup() 
{   
  Serial.begin(9600);                     // ความเร็วในการสื่อสารสำหรับคอมฯ
  BTSerial.begin(9600);                   // ความเร็วในการสื่อสารสำหรับ บลูทูธ
  
  Serial.println("     Status     ");
  Serial.println("  Ready to Run  ");
  
  lcd.begin();
  lcd.home();
  lcd.print("     Status     ");
  lcd.setCursor(0,1);
  lcd.print("  Ready to Run  ");
   
  pinMode(Motor_Left_forward, OUTPUT);    // กำหนด pin ให้ทำงานแบบ Output
  pinMode(Motor_Left_reward, OUTPUT);     // กำหนด pin ให้ทำงานแบบ Output   
  pinMode(Speed_Motor_Left, OUTPUT);      // กำหนด pin ให้ทำงานแบบ Output 
  pinMode(Motor_Right_forward, OUTPUT);   // กำหนด pin ให้ทำงานแบบ Output
  pinMode(Motor_Right_reward, OUTPUT);    // กำหนด pin ให้ทำงานแบบ Output   
  pinMode(Speed_Motor_Right, OUTPUT);     // กำหนด pin ให้ทำงานแบบ Output   
  pinMode(Horn, OUTPUT);                  // กำหนด pin ให้ทำงานแบบ Output
}

void loop() 
{  
  if (BTSerial.available()>0)             // ตรวจสอบว่า bluetooth มีการส่งค่ามาหรือไม่
  {
   char Control = BTSerial.read();        // อ่านค่าจาก bluetooth มาเก็บไว้ที่ ตัวแปร Control
   Serial.println(Control);               // แสดงค่า จาก bluetooth (ตัวแปร Control) ทาง Serial Monitor
   
   if(Control == 'F')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'F' 
       Forward();                         // หุ่นยนต์เดินหน้า
   if(Control == 'B')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'B'
       Reward();                          // หุ่นยนต์ถอยหลัง
   if(Control == 'I')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'I'
       Turn_right();                      // หุ่นยนต์เลี้ยวขวา
   if(Control == 'G')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'G'
       Turn_left();                       // หุ่นยนต์เลี้ยวซ้าย
   if(Control == 'R')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'R'
       Spin_right();                      // หุนยนต์หมุนขวา
   if(Control == 'L')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'L'
       Spin_left();                       // หุ่นยนต์หมุนซ้าย
   if(Control == 'H')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'H'
       Reward_turn_left();                // หุ่นยนต์ถอยหลังและเลี้ยวซ้าย
   if(Control == 'J')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'J'
       Reward_turn_right();               // หุ่นยนต์ถอยหลังและเลี้ยวขวา
   if(Control == 'S')                     // เมื่อค่าที่ bluetooth ส่งมาเป็น 'S'
       Stop();                            // หุ่นยนต์หยุดเดิน
                               
       /*else if(Control == '8')           // เมื่อค่าที่ bluetooth ส่งมาเป็น '8'
      {
        Speed = 180;                     // กำหนดความเร็ว = 180
      }       
      else if(Control == '7')            // เมื่อค่าที่ bluetooth ส่งมาเป็น '7'
      {
        Speed = 160;                     // กำหนดความเร็ว = 160
      }       
      else if(Control == '6')            // เมื่อค่าที่ bluetooth ส่งมาเป็น '6'
      {
        Speed = 140;                     // กำหนดความเร็ว = 140
      }       
      else if(Control == '5')            // เมื่อค่าที่ bluetooth ส่งมาเป็น '5'
      {
        Speed = 120;                     // กำหนดความเร็ว = 120
      }
       else if(Control == '4')          // เมื่อค่าที่ bluetooth ส่งมาเป็น '4'
      {
        Speed = 100;                   // กำหนดความเร็ว = 100
      }       
      else if(Control == '3')          // เมื่อค่าที่ bluetooth ส่งมาเป็น '3'
      {
        Speed = 80;                    // กำหนดความเร็ว = 80
      }       
      else if(Control == '2')          // เมื่อค่าที่ bluetooth ส่งมาเป็น '2'
      {
        Speed = 60;                    // กำหนดความเร็ว = 60
      }       
      else if(Control == '1')          // เมื่อค่าที่ bluetooth ส่งมาเป็น '1'
      {
        Speed = 40;                    // กำหนดความเร็ว = 40
      }*/
    }
}

void Forward()                              // ฟังก์ชันสั่งให้หนุ่นยนต์เดินหน้า
{
  // สั่งให้มอเตอร์ซ้ายหมุนไปหน้า
  analogWrite(Speed_Motor_Left,Speed);      // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed 
  digitalWrite(Motor_Left_forward,HIGH);   // สั่งให้มอเตอร์ซ้ายหมุนไปหน้า
  digitalWrite(Motor_Left_reward,LOW); 
  
  // สั่งให้มอเตอร์ขวาหมุนไปหน้า
  analogWrite(Speed_Motor_Right,Speed);     // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed 
  digitalWrite(Motor_Right_forward,HIGH);  // สั่งให้มอเตอร์ขวาหมุนไปหน้า 
  digitalWrite(Motor_Right_reward,LOW);  
  Serial.println("     Status     ");
  Serial.println("    Forward     ");
  lcd.home();
  lcd.print("    Status      ");
  lcd.setCursor(0,1);
  lcd.print("    Forward     ");            // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังเดินหน้า
}

void Reward()                               // ฟังก์ชันสั่งให้หุ่นยนต์ถอยหลัง
{
  // สั่งให้มอเตอร์ซ้ายหมุนไปกลับหลัง
  analogWrite(Speed_Motor_Left,Speed);      // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Left_forward,LOW);   
  digitalWrite(Motor_Left_reward,HIGH);    // สั่งให้มอเตอร์ซ้ายหมุนกลับหลัง
  
  // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
  analogWrite(Speed_Motor_Right,Speed);     // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Right_forward,LOW);   
  digitalWrite(Motor_Right_reward,HIGH);   // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
  Serial.println("     Status     ");
  Serial.println("     Reward     ");
  lcd.home();
  lcd.print("    Status      ");
  lcd.setCursor(0,1);
  lcd.print("    Reward     ");             // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังถอยหลัง
}

void Turn_left()                                // ฟังก์ชันสั่งให้หุนยนต์เลี้ยวซ้าย
{
  // สำหรับคำนวณความเร็วในการเลี้ยวซ้าย
  int Speed_right = Speed + (Speed/2);
  if (Speed_right > 255)
      Speed_right = 250;
  analogWrite(Speed_Motor_Left,Speed-60);       // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Left_forward, HIGH);       // สั่งให้มอเตอร์ซ้ายหมุนไปหน้า
  digitalWrite(Motor_Left_reward, LOW);  
  analogWrite(Speed_Motor_Right,Speed_right);   // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed_right
  digitalWrite(Motor_Right_forward, HIGH);      // สั่งให้มอเตอร์ขวาหมุนไปหน้า 
  digitalWrite(Motor_Right_reward, LOW);
  Serial.println("     Status     ");
  Serial.println("   Turn Left    ");
  lcd.home();
  lcd.print("     Status     ");
  lcd.setCursor(0,1);
  lcd.print("   Turn Left    ");                // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังเลี้ยวซ้าย
}

void Turn_right()                               // ฟังก์ชันสั่งให้หุนยนต์เลี้ยวขวา
{
  // สำหรับคำนวณความเร็วในการเลี้ยวขวา
  int Speed_left = Speed + (Speed/2);
  if (Speed_left > 255)
      Speed_left = 250;
  analogWrite(Speed_Motor_Left,Speed_left);     // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed_left
  digitalWrite(Motor_Left_forward, HIGH);       // สั่งให้มอเตอร์ซ้ายหมุนไปหน้า
  digitalWrite(Motor_Left_reward, LOW);  
  analogWrite(Speed_Motor_Right,Speed-60);      // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Right_forward, HIGH);      // สั่งให้มอเตอร์ขวาหมุนไปหน้า 
  digitalWrite(Motor_Right_reward, LOW);  
  Serial.println("     Status     ");
  Serial.println("   Turn Right   ");
  lcd.home();
  lcd.print("     Status     ");
  lcd.setCursor(0,1);
  lcd.print("   Turn Right   ");                // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังเลี้ยวขวา
}

void Reward_turn_left()                             // ฟังก์ชันสั่งให้หุ่นยนต์ถอยหลังซ้าย
{
    int Speed_trun_left = Speed + (Speed/2);
    if (Speed_trun_left > 255)
        Speed_trun_left = 250;
    // สั่งให้มอเตอร์ซ้ายหมุนไปกลับหลัง
    analogWrite(Speed_Motor_Left,Speed-60);         // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
    digitalWrite(Motor_Left_forward, LOW);   
    digitalWrite(Motor_Left_reward, HIGH);   	    // สั่งให้มอเตอร์ซ้ายหมุนกลับหลัง
    // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
    analogWrite(Speed_Motor_Right,Speed_trun_left); // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed_trun_left
    digitalWrite(Motor_Right_forward, LOW);   
    digitalWrite(Motor_Right_reward, HIGH);  	    // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
    Serial.println("     Status     ");
    Serial.println("Reward Turn Left");
    lcd.home();
    lcd.print("    Status      ");
    lcd.setCursor(0,1);
    lcd.print("Reward Turn Left");                  // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังถอยหลังซ้าย
}

void Reward_turn_right()                            // ฟังก์ชันสั่งให้หุ่นยนต์ถอยหลังขวา
{
  int Speed_trun_right = Speed + (Speed/2);
  if (Speed_trun_right > 255)
     Speed_trun_right = 250;
  // สั่งให้มอเตอร์ซ้ายหมุนไปกลับหลัง
  analogWrite(Speed_Motor_Left,Speed_trun_right);   // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed_trun_right
  digitalWrite(Motor_Left_forward, LOW);   
  digitalWrite(Motor_Left_reward, HIGH);            // สั่งให้มอเตอร์ซ้ายหมุนกลับหลัง
  // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
  analogWrite(Speed_Motor_Right,Speed - 30);        // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Right_forward, LOW);   
  digitalWrite(Motor_Right_reward, HIGH);           // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
  Serial.println("     Status     ");
  Serial.println("Reward TurnRight");
  lcd.home();
  lcd.print("    Status      ");
  lcd.setCursor(0,1);
  lcd.print("Reward TurnRight");                    // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังถอยหลังขวา
}

void Spin_left()                                    // ฟังก์ชันสั่งให้หุนยนต์หมุนซ้าย
{
  analogWrite(Speed_Motor_Left,Speed);              // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Left_forward, LOW);   
  digitalWrite(Motor_Left_reward, HIGH);            // สั่งให้มอเตอร์ซ้ายหมุนกลับหลัง
  
  analogWrite(Speed_Motor_Right,Speed);             // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Right_forward, HIGH);          // สั่งให้มอเตอร์ขวาหมุนไปหน้า
  digitalWrite(Motor_Right_reward, LOW);  
  Serial.println("     Status     ");
  Serial.println("   Spin Left    ");
  lcd.home();
  lcd.print("    Status      ");
  lcd.setCursor(0,1);
  lcd.print("   Spin Left    ");                  // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังหมุนซ้าย
}

void Spin_right()                                   // ฟังก์ชันสั่งให้หุนยนต์หมุนขวา
{
  analogWrite(Speed_Motor_Left,Speed);              // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Left_forward, HIGH);           // สั่งให้มอเตอร์ซ้ายหมุนไปหน้า 
  digitalWrite(Motor_Left_reward, LOW);  
  analogWrite(Speed_Motor_Right,Speed);             // กำหนดความเร็วมอเตอร์ ด้วยตัวแปร Speed
  digitalWrite(Motor_Right_forward, LOW);   
  digitalWrite(Motor_Right_reward, HIGH);           // สั่งให้มอเตอร์ขวาหมุนกลับหลัง
  Serial.println("     Status     ");
  Serial.println("   Spin Right   ");
  lcd.home();
  lcd.print("    Status      ");
  lcd.setCursor(0,1);
  lcd.print("   Spin Right   ");                    // แสดงค่าที่จอ LCD ว่าหุ่นยนต์กำลังหมุนขวา
}

void Stop()                                         // ฟังก์ชันสั่งให้หุนยนต์หยุดเดิน
{
  analogWrite(Speed_Motor_Left,0);                  // กำหนดความเร็วมอเตอร์ = 0
  digitalWrite(Motor_Left_forward, LOW);            // มอเตอร์หยุดหมุน
  digitalWrite(Motor_Left_reward, LOW);             // มอเตอร์หยุดหมุน
  
  analogWrite(Speed_Motor_Right,0);                 // กำหนดความเร็วมอเตอร์ = 0
  digitalWrite(Motor_Right_forward, LOW);           // มอเตอร์หยุดหมุน
  digitalWrite(Motor_Right_reward, LOW);            // มอเตอร์หยุดหมุน
}










    





