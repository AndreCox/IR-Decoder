#include <Wire.h>                       //includes the Wire.h library already included in arduino
#include <LiquidCrystal_I2C.h>          //this includes the liquid crystal library for I2C LCD's this should be installed per the instructions here https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library 
#include <IRremote.h>                   //this includes the IRremote library this should be installed per the instructions here https://github.com/z3t0/Arduino-IRremote


int IRPIN = 4;                          //change this to which digital pin you pluged the IR reciver output into
String LastVal = "No Last Val";         //This stores the last value as a string because there is no value it says "No Last Val"

IRrecv Receiver(IRPIN);                 //Creates the IRrecv object and sets IRPIN as the input
decode_results result;                  //this is used to decode our result


LiquidCrystal_I2C lcd(0x27, 16, 2);     // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()                            //this runs at once when the program starts
{
  Serial.begin(9600);                   //Start serial with 9600 Baudrate
  Serial.println("Enabling IRin");      //Prints to serial monitor
  Serial.println("Enabled IRin");       //Prints to serial monitor

  lcd.begin();                          //starts the lcd
  lcd.backlight();                      //turns the backlight on

  Receiver.enableIRIn();                //Starts the IR reciver
  
  lcd.print(" Andre's Sensor");         //prints the text to the screen
  lcd.setCursor(0,1);                   //moves the curser down to the second line
  lcd.print("    Booting!");            //prints booting on second line
  delay(2500);                          //waits 2.5 seconds
  
  lcd.clear();                          //clears the screen
  lcd.print("   Waiting To");           //prints the text to first line
  lcd.setCursor(0,1);                   //moves cursor down to second line
  lcd.print("    Receive");             //prints the text to the second line
}

void loop()                             //loops this code until arduino is shut off
{
  if (Receiver.decode(&result))         //this waits until there is an input
  {
    lcd.clear();                        //clears the lcd
    lcd.print(" Hex:");                 //prints the text to lcd
    lcd.print(result.value, HEX);       //prints the result in hex
    lcd.setCursor(0,1);                 //moves cursor down to second line
    lcd.print("Last:");                 //prints the text to the screen
    lcd.print(LastVal);                 //prints the last value to the screen
    LastVal = String(result.value,HEX); //sets the last value to be equal to the result and turns it into a string
    LastVal.toUpperCase();              //then because the letters are in lower case we convert them into upper case          
    Serial.println(result.value, HEX);  //prints the result to the serial monitor
    Receiver.resume();                  //lets the receiver resume; fixes a bug            
  }
  delay(500);                           //waits half a second
}
