#include <Servo.h>
Servo myservoH, myservoV;           // create servo object to control a servo
                                    // a maximum of eight servo objects can be created
int pos = 0;                        // variable to store the servo position
void setup()
{
  myservoH.attach(6);                // attaches the servo on pin 6 to the servo object
  myservoV.attach(5);
}
 
void loop()
{
  for(pos = 45; pos < 135; pos += 1) // goes from 0 degrees to 90 degrees
  {
    myservoH.write(pos);             // tell servo to go to position in variable 'hor'
    delay(22);                       // waits 15ms for the servo to reach the position
    myservoV.write(100);             
    delay(22);
  }
  delay(500);
  for(pos = 135; pos >= 45; pos -=1) // goes from 180 degrees to 0 degrees
  {
    myservoH.write(pos);             // tell servo to go to position in variable 'hor'
    delay(22);                       // waits 15ms for the servo to reach the position
    myservoV.write(125);             
    delay(22);
  }
  delay(500);
}


