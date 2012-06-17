// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 7, 6);

int last_row, last_col;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  // Print a message to the LCD.
  last_row = last_col = 0;

  pinMode(11, OUTPUT);
  set_lcd_light(1);
  
}

unsigned int get_fps() {
  static long unsigned int last_millis = 0, cur_millis;
  static unsigned int last_fps = 0;
  static unsigned int current_fps = 0;
  
  cur_millis = millis();
  current_fps += 1;
  if (cur_millis - last_millis >= 1000) {
    last_millis = cur_millis;
    last_fps = current_fps;
    current_fps = 0;
  }
  
  return last_fps;
}

void set_lcd_light(int light_status) {
  /*
    light_status
      0 -> OFF
      1 -> ON
      2 -> TOGGLE
      3 -> STAY ON FOR $$ SECONDS AND THEN OFF
     -1 -> SAME AS BEFORE
  */
  #define SCREEN_TOGGLE_DELAY  300
  #define SCREEN_STAY_ON_SECS  20
  static long last_check = 0;
  static long screen_delay_toggle = 0;
  static int lcd_bright = 0;
  static int last_light_status = -1000;  // Something to start

  if (light_status == -1) {
    light_status = last_light_status;
  }
  
  switch(light_status) {
    case 1:
      if (last_light_status != 1)
        digitalWrite(11, HIGH);
      last_light_status = light_status;
      break;
    
    case 2:
      if (last_light_status != 2) {
        last_check = millis();
        screen_delay_toggle = SCREEN_TOGGLE_DELAY;
      }
      last_light_status = light_status;
      screen_delay_toggle = screen_delay_toggle - (millis() - last_check);
      last_check = millis();
      
      if (screen_delay_toggle <= 0) {
        lcd_bright = !lcd_bright;
        digitalWrite(11, lcd_bright);
        screen_delay_toggle = SCREEN_TOGGLE_DELAY;
      }
      break;
    
    case 3:
      if (last_light_status != 3) {
        last_check = millis();
        screen_delay_toggle = SCREEN_STAY_ON_SECS * 1000;
        digitalWrite(11, HIGH);
      }
      last_light_status = light_status;
      screen_delay_toggle = screen_delay_toggle - (millis() - last_check);
      last_check = millis();
      
      if (screen_delay_toggle <= 0) {
        digitalWrite(11, LOW);
        last_light_status = 0;
      }
      break;
    
    case 0:
    default:
      if (last_light_status != 0)
        digitalWrite(11, LOW);
      last_light_status = light_status;
  }
}

void loop() {
  static int max_light = 0, min_light = 1024;
  int row, col, sec, light;
  sec = row = col = (int)(millis() / 1000);
  row = row % 4;
  col = col % 19;
  
  sec = sec % 60;
  
  light = analogRead(A0);
  if (light > max_light && light < 1000) max_light = light;  // oria lathous i bgike to kalwdio
  if (light < min_light && light > 5   ) min_light = light;  // oria lathous i bgike to kalwdio
  set_lcd_light(light <= ((max_light - min_light) / 2  + min_light) ? 3 : -1);
  
  lcd.setCursor(3, 1);
  lcd.print(min_light);
  lcd.print(' ');
  lcd.print(light);
  lcd.print(' ');
  lcd.print(max_light);
  lcd.print(' ');
  
  if (last_row == row && last_col == col) {
    lcd.setCursor(3, 0);
    lcd.print(get_fps());
    return;
  }
  
  last_row = row;
  last_col = col;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(col, row);
  // print the number of seconds since reset:
  lcd.print(sec);
  
  lcd.setCursor(3, 0);
  lcd.print(get_fps());

  delay(11);
}

