#include <Wire.h>

// Set up some output smoothing
// This will use a running average of readings to produce the output instead of an instantaneous reading.
// Based on example taken from: https://www.arduino.cc/en/Tutorial/Smoothing

const int numReadings = 100;

// Address of this board on the I2C Bus
const int i2c_address = 0;

// Delay between loop iterations
const int loop_delay = 50;

// Set a minimum input value to be considered zero, this helps prevent noise from causing lights to turn on.
const int min_input = 20;

// Setup analog 0-10v input pins
int inputA1 = A3;
int inputA2 = A2;
int inputA3 = A1;
int inputA4 = A0;

// Setup PWM output pins
int ledCh1 = 3;    
int ledCh2 = 5;
int ledCh3 = 6;
int ledCh4 = 9;

int readIndex = 0;              // the index of the current reading

int apexCh1[numReadings];       // the readings from the analog input
int apexCh2[numReadings];       // the readings from the analog input
int apexCh3[numReadings];       // the readings from the analog input
int apexCh4[numReadings];       // the readings from the analog input

long apexCh1Tot = 0;             // the running total
int apexCh1Avg = 0;             // the average
long apexCh2Tot = 0;             // the running total
int apexCh2Avg = 0;             // the average
long apexCh3Tot = 0;             // the running total
int apexCh3Avg = 0;             // the average
long apexCh4Tot = 0;             // the running total
int apexCh4Avg = 0;             // the average

int pwmCh1 = 0;
int pwmCh2 = 0;
int pwmCh3 = 0;
int pwmCh4 = 0;

void setup() {
  pinMode(ledCh1,OUTPUT);
  pinMode(ledCh2,OUTPUT);
  pinMode(ledCh3,OUTPUT);
  pinMode(ledCh4,OUTPUT);
  
  // initialize all the readings for input arrays to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    apexCh1[thisReading] = 0;
    apexCh2[thisReading] = 0;
    apexCh3[thisReading] = 0;
    apexCh4[thisReading] = 0;
  }
  
  Wire.begin(i2c_address);        // join i2c bus with address #8
  Wire.onRequest(requestEvent);   // register event
  Serial.begin(9600);
}

void loop() {
  
  // Read the analog input pins
  apexCh1Tot -= apexCh1[readIndex];
  apexCh1[readIndex] = analogRead(inputA1);
  if ( apexCh1[readIndex] < min_input ) apexCh1[readIndex] = 0;
  if ( apexCh1[readIndex] > 1010 ) apexCh1[readIndex] = 1023;
  apexCh1Tot += apexCh1[readIndex];
  apexCh1Avg = apexCh1Tot / numReadings;
  apexCh1Avg = constrain(apexCh1Avg,0,1023);
  pwmCh1 = apexCh1Avg / 4;

  apexCh2Tot -= apexCh2[readIndex];
  apexCh2[readIndex] = analogRead(inputA2);
  if ( apexCh2[readIndex] < min_input ) apexCh2[readIndex] = 0;
  if ( apexCh2[readIndex] > 1010 ) apexCh2[readIndex] = 1023;
  apexCh2Tot += apexCh2[readIndex];
  apexCh2Avg = apexCh2Tot / numReadings;
  apexCh2Avg = constrain(apexCh2Avg,0,1023);
  pwmCh2 = apexCh2Avg / 4;
  
  apexCh3Tot -= apexCh3[readIndex];
  apexCh3[readIndex] = analogRead(inputA3);
  if ( apexCh3[readIndex] < min_input ) apexCh3[readIndex] = 0;
  if ( apexCh3[readIndex] > 1010 ) apexCh3[readIndex] = 1023;
  apexCh3Tot += apexCh3[readIndex];
  apexCh3Avg = apexCh3Tot / numReadings;
  apexCh3Avg = constrain(apexCh3Avg,0,1023);
  pwmCh3 = apexCh3Avg / 4;
  
  apexCh4Tot -= apexCh4[readIndex];
  apexCh4[readIndex] = analogRead(inputA4);
  if ( apexCh4[readIndex] < min_input ) apexCh4[readIndex] = 0;
  if ( apexCh4[readIndex] > 1010 ) apexCh4[readIndex] = 1023;
  apexCh4Tot += apexCh4[readIndex];
  apexCh4Avg = apexCh4Tot / numReadings;
  apexCh4Avg = constrain(apexCh4Avg,0,1023);
  pwmCh4 = apexCh4Avg / 4;
  
  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  
  // Send the PWM output to the digital pins
  analogWrite(ledCh1,pwmCh1); // Write the PWM wave
  analogWrite(ledCh2,pwmCh2);
  analogWrite(ledCh3,pwmCh3);
  analogWrite(ledCh4,pwmCh4);
  
  Serial.print("Input:\t");
  Serial.print(apexCh1Avg);
  Serial.print("\t");
  Serial.print(apexCh2Avg);
  Serial.print("\t");
  Serial.print(apexCh3Avg);
  Serial.print("\t");
  Serial.print(apexCh4Avg);
  Serial.println();
  Serial.print("Output:\t");
  Serial.print(pwmCh1);
  Serial.print("\t");
  Serial.print(pwmCh2);
  Serial.print("\t");
  Serial.print(pwmCh3);
  Serial.print("\t");
  Serial.print(pwmCh4);
  Serial.println();
  Serial.println();
  
  delay(loop_delay);
}

void requestEvent() {
  Wire.write("s: 0"); // respond with message of 6 bytes
  // as expected by master
}

