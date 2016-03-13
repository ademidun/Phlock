

// Arduino Bluetooth LE Servo Controlled by iOS
#include <Servo.h>
#include <SoftwareSerial.h>


int lock = 9;          //pin 9 on Arduino
int LED = 3; 
char final[4];         //Characters the Arduino will receive
char correct[4] = {'A','B','C','D'};    //User-Defined Password
int pass_correct = 0;          //Does Password match, 0=false 1=true
boolean locked = true;
Servo myservo;
SoftwareSerial BLE_Shield(4,5);

void setup()
{
myservo.attach(9);
BLE_Shield.begin(9600);
myservo.write(15);
pinMode(LED, OUTPUT);
}

void loop()
{
while(BLE_Shield.available() >= 4) 
{
  for(int i=0; i<4; i++)   //While data is available read 4 bytes
  {
   final[i] = BLE_Shield.read();  //Read 4 bytes into the array labled "final"
  }

  for(int i=0; i<4; i++)
  {
   if(final[i]==correct[i]) //Compare each char received to each car in our password in order
   {
    pass_correct = 1;   //If we compare two chars and they match, set the pass_correct variable to true(1)
   }
   else
   {
    pass_correct = 0;  //if the two compared chars do NOT match, set pass_correct variable to false(0)
    break;   //End loop and stop comparing chars
   }
  }
}

if(pass_correct==1)  //If all chars compared match, deactivate(unlock) the lock for 5 seconds
{
  Serial.println("Unlocked");
  digitalWrite(LED, HIGH);
  delay(500);
  myservo.write(105);
  delay(3000);
  digitalWrite(LED, LOW);
  delay(500);
  myservo.write(15);
  Serial.println("Locked");
  pass_correct = 0;  
  delay(3000);
}
else
{

}

/* FOR TESTING
Serial.print(final[0]);Serial.print(final[1]);Serial.print(final[2]);Serial.print(final[3]);
Serial.print(" | ");
Serial.print(correct[0]);Serial.print(correct[1]);Serial.print(correct[2]);Serial.print(correct[3]);
Serial.print(" ");
Serial.print(pass_correct);
Serial.println("");
*/
delay(500);


}
