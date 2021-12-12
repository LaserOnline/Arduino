#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>


int LEDT   = 11;
int LEDH   = 13;
int Buzzer = 10;

int MinT,MaxT,MinH,MaxH;

//=================================================================
/*const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8,7,6,5};
byte colPins[COLS] = {4,3,2};*/

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

//=================================================================
LiquidCrystal_I2C lcd(0x27,20,4);
//=================================================================
DHT dht;
//=================================================================
void setup()
{
  lcd.begin();
  lcd.setCursor(0,0);lcd.print("Temperature        C");
  lcd.setCursor(0,1);lcd.print("Humidity           %");
  lcd.setCursor(0,2);lcd.print("MinT    C  MaxT    C");
  lcd.setCursor(0,3);lcd.print("MinH    %  MaxH    %");
  
  pinMode(Buzzer,OUTPUT);digitalWrite(Buzzer,HIGH);
  pinMode(LEDT   ,OUTPUT);digitalWrite(LEDT   ,HIGH);
  pinMode(LEDH   ,OUTPUT);digitalWrite(LEDH   ,HIGH);
  
  dht.setup(13); // data pin 13 
  
  MinT = EEPROM.read(0);
  MaxT = EEPROM.read(1);
  MinH = EEPROM.read(2);
  MaxH = EEPROM.read(3);
  
  
  lcd.setCursor(5,2); lcd.print(MinT);
  lcd.setCursor(16,2);lcd.print(MaxT);
  lcd.setCursor(5,3); lcd.print(MinH);
  lcd.setCursor(16,3);lcd.print(MaxH);
}

//=================================================================
void loop()
{
  delay(dht.getMinimumSamplingPeriod());
  
  char Key;
  
  while(Key == NO_KEY)
  {
    float humidity    = dht.getHumidity(); // ดึงค่าความชื้น
    float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
    lcd.setCursor(14,0);lcd.print(temperature, 1);
    lcd.setCursor(14,1);lcd.print(humidity   , 1);
    
    if(temperature <= MinT)
    {
      digitalWrite(LEDT,HIGH);
    }
    if(temperature >= MaxT)
    {
      digitalWrite(LEDT,LOW);      
    }
    
    if(humidity <= MinH)
    {
      digitalWrite(LEDH,LOW);
    }
    if(humidity >= MaxH)
    {
      digitalWrite(LEDH,HIGH);      
    }
    
    Key = keypad.getKey();
  }
  Beep();
  if(Key == '*')
  {
    lcd.setCursor(5,2);
    lcd.blink();
    MinT = GetNum(2,5,2);
    EEPROM.write(0,MinT);
    MaxT = GetNum(2,16,2);
    EEPROM.write(1,MaxT);
    lcd.noBlink();
    
    lcd.setCursor(5,3);
    lcd.blink();
    MinH = GetNum(2,5,3);
    EEPROM.write(2,MinH);
    MaxH = GetNum(2,16,3);
    EEPROM.write(3,MaxH);
    lcd.noBlink();
  }
}

//=================================================================

char BufNum[8];
void SlideNum(void)
{
  BufNum[6] = BufNum[5];
  BufNum[5] = BufNum[4];
  BufNum[4] = BufNum[3];
  BufNum[3] = BufNum[2];
  BufNum[2] = BufNum[1];
  BufNum[1] = BufNum[0];
}

//=================================================================

unsigned long GetNum(int Count, int X, int Y)
{
  char Key, i, N;
  int Sum;
  
  lcd.setCursor(X+(Count-1),Y);
  N = 0;
  for(i=0;i<Count;i++)
  {
    BufNum[i] = ' ';
  }
  i = 0;
  while(Key != '#')
  {
    Key = NO_KEY;
    while(Key == NO_KEY)
    {
      Key = keypad.getKey();
    }
    
    lcd.setCursor(X+(Count-1),Y);
    N = 0;
    for(i=0;i<Count;i++)
    {
      BufNum[i] = ' ';
    }
    i=0;
    while(Key != '#')
    {
      Key = NO_KEY;
      while(Key == NO_KEY)
      {
        Key = keypad.getKey();
      }
      Beep();
      delay(300);
      if(Key == '*')
      {
        for(i=0;i<Count;i++)
        {
          BufNum[i] = ' ';
        }
        N = 0;
      }
      if((N<Count)&&(Key>='0')&&(Key<='9'))
      {
        SlideNum();
        BufNum[0] = Key;
        N++;
      }
      lcd.setCursor(X,Y);
      for(i=0;i<Count;i++)
      {
        lcd.print(BufNum[Count-(i+1)]);
      }
      lcd.setCursor(X+(Count-1),Y);
    }
  Sum = 0;
  for(i=0;i<Count;i++)
  {
    if(BufNum[Count-(i+1)]==0x20)
    {
      BufNum[Count-(i-1)] = '0';
    }
    Sum = (Sum*10)+(BufNum[Count-(i+1)]-'0');
  }
  lcd.noCursor();
  return(Sum);
  }
}  

//=================================================================

void Beep()
{
  digitalWrite(Buzzer,LOW);
  delay(50);
  digitalWrite(Buzzer,HIGH);
}


