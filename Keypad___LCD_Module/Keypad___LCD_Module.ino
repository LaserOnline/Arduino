#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

int Buzzer = 11; //ตัวลำโพง ต่อ ขา 11

const byte ROWS = 4; //แถว
const byte COLS = 4; //บรรรทัด
char keys [ROWS] [COLS] = {

  {'1','2','3','A'}, //ตามจำนวณปุ่มkeypen
  {'4','5','6','B'}, 
  {'7','8','9','C'},
  {'*','0','#','D'},
};

byte rowPins[ROWS] = {9,8,7,6}; //ไม่รู้
byte colPins[COLS] = {5,4,3,2}; //ไม่รู้


Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
LiquidCrystal_I2C lcd(0x3F,20,4);

//--------------------------------------------------
void setup() {
  Serial.begin(9600); //ความเร็วส่งข้อมูล
  lcd.begin();
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("     Keypad Test     ");
  lcd.setCursor(0,3);      
  lcd.print("Key        =         ");
  pinMode(Buzzer,OUTPUT); //บอกโปรแกรมว่า Buzzer เป็น OUTPUT
  digitalWrite(Buzzer,HIGH); // HIGH คือปิดเพราะ ไม่งันมันจะดังตลอด
  lcd.blink();
  lcd.setCursor(19,3);
}
//--------------------------------------------------
void loop() 
 {int Num;
                                            
     Num = GetNum(4,16,3);                //GetNum(4,16,3)
     lcd.setCursor(16,2);                       // 4 จำนวณที่เก็บ จะเกิน 4 หลักไม่ได้ 16 จริงๆคือ 17 สรุปก็คือจะไปโชว์ที่ 17 บรรดทัดที่ 4
     lcd.print(Num);
 }    
//--------------------------------------------------
char BufNum[8];
void  SlideNum(void)
{
  BufNum[6]  = BufNum[5];
  BufNum[5]  = BufNum[4];
  BufNum[4]  = BufNum[3];
  BufNum[3]  = BufNum[2];
  BufNum[2]  = BufNum[1];
  BufNum[1]  = BufNum[0];
}
//---------------------------------------------------
unsigned long GetNum(int Count,int X,int Y)
{ char Key,i,N;
  int Sum; 

  lcd.setCursor(X+(Count-1),Y); 
  N = 0;
  for(i=0;i<Count;i++){BufNum[i] = ' ';}
  i = 0;
  while(Key != '#')
  { Key = NO_KEY;
    while(Key == NO_KEY){Key = keypad.getKey();}    
    Beep(); delay(300);
   if(Key == '*'){for(i=0;i<Count;i++){BufNum[i] = ' ';}N = 0;}                  
   if((N < Count)&&(Key >= '0')&&(Key <= '9'))
   { SlideNum();
     BufNum[0] = Key;
     N++;
   }
   lcd.setCursor(X,Y);
   for(i=0;i<Count;i++){lcd.print(BufNum[Count-(i+1)]);}
   lcd.setCursor(X+(Count-1),Y);  
    
  }
Sum = 0;
for(i=0;i<Count;i++)
 {
   if(BufNum[Count-(i+1)]==0x20){BufNum[Count-(i+1)] = '0';}
   Sum = (Sum*10) + (BufNum[Count-(i+1)]-'0');
 }
lcd.noCursor();
return(Sum);  
}
//--------------------------------------------------
void Beep()
{
  digitalWrite(Buzzer,LOW);delay(50);
  digitalWrite(Buzzer,HIGH);
}
//--------------------------------------------------
