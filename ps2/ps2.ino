// include the library code:
#include <LiquidCrystal.h>
#include <PS2Keyboard.h>



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 7, 6);
PS2Keyboard keyboard;

const int DataPin = 3;   // ps2-mple
const int IRQpin =  2;   // ps2-kitrino
                         // ps2-kokkino = trofodosia
                         // ps2-aspro   = geiwsi

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  keyboard.begin(DataPin, IRQpin);
}

int keypad_availiable() {
  return keyboard.available();
}

char keypad_read() {
  int k = keyboard.read();
  switch(k) {
    case 109:  return '1';
    case 118:  return '2';
    case  42:  return '3';
    case  47:  return 'A';

    case 104:  return '4';
    case 103:  return '5';
    case  46:  return '6';
    case  48:  return 'B';

    case 106:  return '7';
    case 102:  return '8';
    case  51:  return '9';
    case  50:  return 'C';

    case 121:  return '*';
    case 116:  return '0';
    case  54:  return '#';
    case  53:  return 'D';
    default:   return '?';
  }
}

void loop() {
  static char p;
  
  lcd.clear();
  lcd.setCursor(0, 0);

  int a = keypad_availiable();
  lcd.print(a);
  if (a) {
    p = keypad_read();
    
    if (p == '1')       keyboard.setLed(0, 0);
    else if (p == '2')  keyboard.setLed(1, 0);
    else if (p == '3')  keyboard.setLed(2, 0);
    else if (p == '4')  keyboard.setLed(0, 1);
    else if (p == '5')  keyboard.setLed(1, 1);
    else if (p == '6')  keyboard.setLed(2, 1);
    else if (p == '7')  keyboard.toggleLed(0);
    else if (p == '8')  keyboard.toggleLed(1);
    else if (p == '9')  keyboard.toggleLed(2);
  }
  lcd.setCursor(0, 1);
  lcd.print(p);
  
  delay(10);
}

