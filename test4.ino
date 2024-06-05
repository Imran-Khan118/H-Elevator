#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 3 // Encoder pin A
#define ENCB 2 // Encoder pin B
#define PWM_UP 10 // Motor PWM up pin
#define PWM_DOWN 6 // Motor PWM down pin
#define BUTTON1 8 // Button 1 pin
#define BUTTON2 7 // Button 2 pin
#define BUTTON3 4 // Button 3 pin

// Global Variables
volatile int posi = 0; // Encoder position
long prevT = 0; // Previous time for PID calculation
float eprev = 0; // Previous error for PID calculation
float eintegral = 0; // Integral of error for PID calculation
int target = 0; // Target floor

// Initialize the LCD with the I2C address (0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  pinMode(PWM_UP, OUTPUT);
  pinMode(PWM_DOWN, OUTPUT);
  
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Lift system");
  lcd.setCursor(0, 1);
  lcd.print("initialized");
}

void loop() {
  // Check buttons to set target floor
  if (digitalRead(BUTTON1) == LOW) {
    target = 0;
  }
  if (digitalRead(BUTTON2) == LOW) {
    target = 900;
  }
  if (digitalRead(BUTTON3) == LOW) {
    target = 1750;
  }
  
  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;
  
  // Calculate time difference for PID
  long currT = micros();
  float deltaT = ((float)(currT - prevT)) / (1.0e6);
  prevT = currT;
  
  // Read encoder position
  int pos = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
   
  // Calculate error
  int e = target - pos;
  
  // Calculate derivative
  float dedt = (e - eprev) / deltaT;
  
  // Calculate integral
  eintegral += e * deltaT;
  
  // Calculate control signal
  float u = kp * e + kd * dedt + ki * eintegral;
  
  // Calculate motor power
  float pwr = fabs(u);
  if (pwr > 255) {
    pwr = 255;
  }
  
  // Determine motor direction
  int dir = 1;
  if (u < 0) {
    dir = -1;
  }
  
  // Signal the motor
  setMotor(dir, pwr, PWM_UP, PWM_DOWN);
  
  // Store previous error
  eprev = e;
  
  // Update LCD display
  updateLCD(pos);
}

// Function to set motor direction and power
void setMotor(int dir, int pwmVal, int pwm_up, int pwm_down) {
  if (dir == 1) {
    analogWrite(pwm_up, pwmVal);
    analogWrite(pwm_down, 0);
  } else if (dir == -1) {
    analogWrite(pwm_up, 0);
    analogWrite(pwm_down, pwmVal);
  } else {
    analogWrite(pwm_up, 0);
    analogWrite(pwm_down, 0);
  }
}

// Function to read encoder position
void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}

// Function to update LCD display with current floor
void updateLCD(int pos) {
  lcd.setCursor(0, 1);
  lcd.print("Current floor: ");
  
  if (pos >= 0 && pos < 450) {
    lcd.print("Ground floor");
  } else if (pos >= 450 && pos < 1350) {
    lcd.print("1st floor");
  } else if (pos >= 1350 && pos <= 1900) {
    lcd.print("2nd floor");
  } else {
    lcd.print("Unknown floor");
  }
}
