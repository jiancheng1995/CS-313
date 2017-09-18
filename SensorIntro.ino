/*
  HC-SR04 Ping distance sensor]
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/
#include <AFMotor.h>
#include <Servo.h>              // Add library
#include "servoDemo.h"
Servo name_servo;               // Define any servo name

void setup() {
  name_servo.attach(10);
  Serial.begin (9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  name_servo.write(OFFPOSITION);
}

int servo_position = 0;
bool servoState = false;

void loop() {
  long duration, distance;
  digitalWrite(TRIGPIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGPIN, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;
  if (servoState) {
    if (distance < SETPOINT - (HYSTERISIS / 2)) {
      name_servo.write(ONPOSITION);
      servoState = true;
    } else {
      name_servo.write(OFFPOSITION);
      servoState = false;
    }
  }
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
    if (distance < 6) {
      name_servo.write(180);
    } else {
      name_servo.write(-180);
    }
  }
\
  delay(500);
}
