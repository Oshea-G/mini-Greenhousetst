#include<Servo.h>
Servo myServo;

int rawSensorValue;
float rawVolts;

float tempC; // holds celsius
float tempF; // holds fahrenheit 

int setPoint = 79; // sets max temp in fahrenheit 
int returnPoint = 78; // sets the point of normal state

void setup() {
  
  pinMode(11, OUTPUT);
  
  myServo.attach(9, 1000, 2000);
  myServo.write(0);
  
  Serial.begin(9600); // initializes the serial communication
  Serial.print("raw");
  Serial.print("\t"); 
  Serial.print("volts");

  Serial.print("\t");
  Serial.print("degC");
  Serial.print("\t");
  Serial.print("degF");
  
  Serial.println(); // new line character
}

void loop() {
  digitalWrite(11,LOW); // turns off motor before reading sensor
  delay(1); // short 1 ms delay before reading sensor

  /// CONVERTS SENSOR READINGS TO FAHRENHEIT /// //// //// /// /// // /// // /// 
  rawSensorValue = analogRead(A0);  // read in sensor value
  rawVolts = volts(rawSensorValue); // convert sensor value to volts

  tempC = 100 * rawVolts - 50; // convert volts to deg. C
  tempF = 1.8 * tempC + 32;    // convert deg. C to deg. F
  // ///// // ///// / ///// // ///// // ///// // ///// ///// ///// ////
  
  Serial.print(rawSensorValue); // print raw sensor value
  Serial.print("\t");

  Serial.print(rawVolts); // prints raw voltage reading
  Serial.print("\t");

  Serial.print(tempC);
  Serial.print("\t");
  Serial.print(tempF);
  Serial.print("\t");
  
  Serial.println();
  if(tempF > setPoint){         //opens window and turns on fan
    myServo.write(180);
    digitalWrite(11, HIGH);     // turns the fan on
  }
  else if(tempF < returnPoint) { // closes window and turns off fan
    myServo.write(20);
    digitalWrite(11, LOW);
  }
  
  delay(1500);
}

float volts(int rawCount)
{
  const float AREF = 5.0;
  float calculatedVolts;
  calculatedVolts = rawCount * AREF / 1023;
  return calculatedVolts;
}
