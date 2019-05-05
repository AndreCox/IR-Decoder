#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "IRLibAll.h"

IRrecvPCI Receiver(4);

IRdecode Decoder;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
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
  lcd.setCursor(0,0);                //probably unnessasary but moves the cursor to the first line
  lcd.print("Reciving Signals");     //prints the text to first line
  lcd.setCursor(0,1);
}

void loop() {

  if (Receiver.getResults()) {
    
    lcd.print(Decoder.decode());
    
    Receiver.enableIRIn();
  }

}
