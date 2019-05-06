#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

int IRPIN = 4;
String LastVal = "No Last Val";

IRrecv Receiver(IRPIN);

decode_results result;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  Serial.println("Enabled IRin");
// initialize the LCD
  lcd.begin();                       //starts the lcd
  lcd.backlight();                   //turns the backlight on

  Receiver.enableIRIn();             //Starts the IR reciver
  
  lcd.print(" Andre's Sensor");      //prints the text to the screen
  lcd.setCursor(0,1);                //moves the curser down to the second line
  lcd.print("    Booting!");         //prints booting on second line
  delay(2500);                       //waits 2.5 seconds

  Serial.begin(9600);
  
  lcd.clear();                       //clears the screen
  lcd.print("   Waiting To");  //prints the text to first line
  lcd.setCursor(0,1);
  lcd.print("    Receive");
}

void loop() 
{
  if (Receiver.decode(&result)) 
  {
    lcd.clear();
    lcd.print(" Hex:");
    lcd.print(result.value, HEX);
    lcd.setCursor(0,1);
    lcd.print("Last:");
    lcd.print(LastVal);
    LastVal = String(result.value,HEX);
    LastVal.toUpperCase();
    Receiver.enableIRIn();
    Serial.println(result.value, HEX);
    Receiver.resume();
  }
  delay(500);
}
