#include <Arduino.h>

#define PWM_PIN 9

unsigned long duration;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, INPUT);
}

void loop() {
  duration = pulseIn(PWM_PIN, HIGH);
  Serial.println(duration);
}