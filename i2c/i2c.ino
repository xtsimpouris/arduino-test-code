// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 5, 4, 7, 6);

void setup()
{
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System loading..");
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System started..");
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    lcd.print(c);
  }
  int x = Wire.read();    // receive byte as an integer
  
  lcd.setCursor(3, 0);
  lcd.print(x);
  Serial.println(x);         // print the integer
}
