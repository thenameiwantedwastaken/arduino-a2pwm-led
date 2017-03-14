#include <Wire.h>

// Setup analog 0-10v input pins
int inputA1 = A0;
int inputA2 = A1;
int inputA3 = A2;
int inputA4 = A3;
int inputA5 = A6;
int inputA6 = A7;

// Setup PWM output pins
int ledCh1 = 3;    
int ledCh2 = 5;
int ledCh3 = 6;
int ledCh4 = 9;
int ledCh5 = 10;
int ledCh6 = 11;

void setup() {
  pinMode(ledCh1,OUTPUT);
  pinMode(ledCh2,OUTPUT);
  pinMode(ledCh3,OUTPUT);
  pinMode(ledCh4,OUTPUT);
  pinMode(ledCh5,OUTPUT);
  pinMode(ledCh6,OUTPUT);
  
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Set up new variables and read the analog input pins
  int apexCh1  = analogRead(inputA1);
  int apexCh2  = analogRead(inputA2);
  int apexCh3  = analogRead(inputA3);
  int apexCh4  = analogRead(inputA4);
  int apexCh5  = analogRead(inputA5);
  int apexCh6  = analogRead(inputA6);
  
  Serial.print("Channel 1 Input:");
  Serial.print("\t");
  Serial.println(apexCh1);
  
  // Convert the 10-bit 0-1023 analog voltage to a 0-255 pwm value
  apexCh1 = map(apexCh1, 0, 1023, 0, 255);
  apexCh2 = map(apexCh2, 0, 1023, 0, 255);
  apexCh3 = map(apexCh3, 0, 1023, 0, 255);
  apexCh4 = map(apexCh4, 0, 1023, 0, 255);
  apexCh5 = map(apexCh5, 0, 1023, 0, 255);
  apexCh6 = map(apexCh6, 0, 1023, 0, 255);
  
  // Send the PWM output to the digital pins
  analogWrite(ledCh1,apexCh1); // Write the PWM wave
  analogWrite(ledCh2,apexCh2);
  analogWrite(ledCh3,apexCh3);
  analogWrite(ledCh4,apexCh4);
  analogWrite(ledCh5,apexCh5);
  analogWrite(ledCh6,apexCh6);
  
  Serial.print("Channel 1 Output: ");
  Serial.print("\t");
  Serial.println(apexCh1);
  
  Wire.beginTransmission(8);  
  Wire.write("master ");      
  Wire.endTransmission();    

  delay(500);
}

