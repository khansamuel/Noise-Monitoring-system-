#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSOR_PIN = 2;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;

// Add push button code
int buttonPin = 8;
int buttonRead = 1;

const int BUZZER_PIN = 7;
const int LED_PIN = 12;
const int LEDPin = 13;
boolean is_on = false; //To determine/track if led is on or off

void setup() {
 Serial.begin(9600);

 // Push button code
 pinMode(buttonPin, INPUT);

 pinMode(SENSOR_PIN, INPUT); // Set the Sensor pin as INPUT
 pinMode(BUZZER_PIN, OUTPUT); // Set the BUZZER pin as OUTPUT
 pinMode(LED_PIN, OUTPUT); // Set the LED pin as OUTPUT
 pinMode(LEDPin, INPUT); // Set the LED pin as OUTPUT

 // Initialize the I2C LCD
 lcd.begi
n();
 lcd.backlight();

 lcd.setCursor(0, 0); // set the cursor position:
 lcd.print("NOISE MONITORING SYS!");
 lcd.setCursor(0, 1);
 lcd.setCursor(0, 3);
 lcd.print(" NO SOUND DETECTED ");
}

void loop() {
 // Push button code
 buttonRead = digitalRead(buttonPin);
 if (buttonRead == HIGH){ 
 digitalWrite(LEDPin,HIGH);
  
  return;
 }

 millisCurrent = millis();
 millisElapsed = millisCurrent - millisLast;

 if (digitalRead(SENSOR_PIN) == LOW) {
  sampleBufferValue++;
 }

 if (millisElapsed > SAMPLE_TIME) {
  Serial.println(sampleBufferValue);
  sampleBufferValue = 0;
  millisLast = millisCurrent;
 }

 // Rest of the code
 int data = digitalRead(SENSOR_PIN); //Reading data from sensor and storing in variable
 int Sensor_Val = digitalRead(SENSOR_PIN); //get reading from microphone
 if (Sensor_Val == HIGH) //If Sound Sensor Detected the Sound
 {
  lcd.setCursor(0, 3);
  lcd.print(" SOUND DETECTED  ");
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
 } else {
  lcd.setCursor(0, 3);
  lcd.print(" NO SOUND  ");
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
 }

 // Code for the LED to turn on or off depending on the sensor data
 if (data == 1) { // 1 is sent from sensor when loud noise is detected
  if (is_on == true) { // If led is on then turn it off
   digitalWrite(LED_PIN, LOW);
   is_on = false;
  } else { // else if led is off then turn it on
   digitalWrite(LED_PIN, HIGH);
   is_on = true;
  }
 } else if (data == 2) { // 2 is sent from sensor when soft noise is detected
  // ...
 } else {
 

}
}
