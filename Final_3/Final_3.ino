#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x3F, 20, 4);

void menu()
{
  Serial.println();
  Serial.println("=========================");
  Serial.println("      Famiry Group       ");
  Serial.println("=========================");
  Serial.println("1 Mr.Arnont Phetarphorn  ");
  Serial.println("2 Mrs.Chida Phetarphorn  ");
  Serial.println("3 Miss Warisa Phetarphorn");
  Serial.println("=========================");
  Serial.println("   Select number 1-3...  ");
  lcd.setCursor(0,0); lcd.print("====================");
  lcd.setCursor(0,1); lcd.print("    Famiry Group    ");
  lcd.setCursor(0,2); lcd.print("====================");
  lcd.setCursor(0,3); lcd.print("Select number 1-3...");
}

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  menu();
}

void loop() 
{
  while(Serial.available() > 0)
  {
    int var = Serial.read();
    Serial.write(var);

    if (var == '1')
    {
      Serial.println(" Mr.Arnont  Phetarphorn ");
      Serial.println("Phone  :    081-826-4203");
      Serial.println("Sex    :            Male");
      Serial.println("Age    :              51");
      lcd.setCursor(0,0); lcd.print(" Arnont Phetarphorn ");
      lcd.setCursor(0,1); lcd.print("Phone : 081-826-4203");
      lcd.setCursor(0,2); lcd.print("Sex   :         Male");
      lcd.setCursor(0,3); lcd.print("Age   :           51");
      delay(5000);
    }
    else if(var == '2')
    {
      Serial.println(" Mrs.Chida  Phetarphorn ");
      Serial.println("Phone  :    081-826-4204");
      Serial.println("Sex    :          Female");
      Serial.println("Age    :              51");
      lcd.setCursor(0,0); lcd.print(" Chida  Phetarphorn ");
      lcd.setCursor(0,1); lcd.print("Phone : 081-826-4204");
      lcd.setCursor(0,2); lcd.print("Sex   :       Female");
      lcd.setCursor(0,3); lcd.print("Age   :           51");
      delay(5000);
    }
    else if(var == '3') 
    {
      Serial.println(" Miss Warisa Phetarphorn");
      Serial.println("Phone  :    081-826-4205");
      Serial.println("Sex    :          Female");
      Serial.println("Age    :              24");
      lcd.setCursor(0,0); lcd.print(" Warisa Phetarphorn ");
      lcd.setCursor(0,1); lcd.print("Phone : 081-826-4205");
      lcd.setCursor(0,2); lcd.print("Sex   :       Female");
      lcd.setCursor(0,3); lcd.print("Age   :           24");
      delay(5000);
    }
    else
    { 
      Serial.println("Select Number Error");
      lcd.clear();
      lcd.setCursor(0,1); lcd.print("Select Number  Error");
      delay(3000);
    }
    menu();
  }
}

