/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#define PIN_A     8
#define PIN_B     9
#define PIN_C    10
#define PIN_D    11

#define PIN_LED  13
#define ALL_STEPS 64 * 64

#define STEP_DELAY  4

int led_status = HIGH;
int current_step = 0;
int steps[4][4] = {{1, 0, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}};    // wave step
// int steps[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}; // quick step

int step_direction = 0;
int count_steps = ALL_STEPS;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  
  count_steps = 0;
  Serial.begin(9600);
}

void step_forward() {
  int new_step;
  new_step = (current_step + 1) % 4;
  digitalWrite(PIN_A, steps[new_step][0]);
  digitalWrite(PIN_B, steps[new_step][1]);
  digitalWrite(PIN_C, steps[new_step][2]);
  digitalWrite(PIN_D, steps[new_step][3]);
  current_step = new_step;
  delay(STEP_DELAY);
}

void step_backwards() {
  int new_step;
  new_step = (current_step - 1) < 0 ? 3 : current_step - 1;
  digitalWrite(PIN_A, steps[new_step][0]);
  digitalWrite(PIN_B, steps[new_step][1]);
  digitalWrite(PIN_C, steps[new_step][2]);
  digitalWrite(PIN_D, steps[new_step][3]);
  current_step = new_step;
  delay(STEP_DELAY);
}

void loop() {
  count_steps--;
  if (count_steps < 0) {
    step_direction = !step_direction;
    count_steps = ALL_STEPS;
    Serial.println(step_direction);
  }
  
  if (step_direction > 0) {
    digitalWrite(PIN_LED, HIGH);
    step_forward();
  }
  else {
    digitalWrite(PIN_LED, LOW);
    step_backwards();
  }
}


