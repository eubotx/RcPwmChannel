#include <Arduino.h>
#include <RcPwmChannel.h>

// example values to be derived with pulseLengthDeterminer.cpp
#define PWM_CHANNEL_1_PIN 9
#define MAX_MS_BETWEEN_UPDATES 500
#define LOW_PULSE_LENGTH 1057
#define LOWER_DEADZONE_WIDTH 50
#define CENTER_PULSE_LENGTH 1491
#define CENTER_DEADZONE_WIDTH 50
#define HIGH_PULSE_LENGTH 2013
#define HIGHER_DEADZONE_WIDTH 50
#define INVALID_LOW_THRESHOLD 700
#define INVALID_HIGH_THRESHOLD 2400

//alternative constructors depending on your need
/* // no center no deadzone
RcPwmChannel channel1   (PWM_CHANNEL_1_PIN, MAX_MS_BETWEEN_UPDATES, 
                        LOW_PULSE_LENGTH, HIGH_PULSE_LENGTH,
                        INVALID_LOW_THRESHOLD, INVALID_HIGH_THRESHOLD); */

/* // no center and deadzone
RcPwmChannel channel1   (PWM_CHANNEL_1_PIN, MAX_MS_BETWEEN_UPDATES, 
                        LOW_PULSE_LENGTH, LOWER_DEADZONE_WIDTH, 
                        HIGH_PULSE_LENGTH, HIGHER_DEADZONE_WIDTH, 
                        INVALID_LOW_THRESHOLD, INVALID_HIGH_THRESHOLD); */

/* // center no deadzone
RcPwmChannel channel1   (PWM_CHANNEL_1_PIN, MAX_MS_BETWEEN_UPDATES, 
                        LOW_PULSE_LENGTH, CENTER_PULSE_LENGTH, HIGH_PULSE_LENGTH,
                        INVALID_LOW_THRESHOLD, INVALID_HIGH_THRESHOLD); */

// center and deadzone
RcPwmChannel channel1   (PWM_CHANNEL_1_PIN, MAX_MS_BETWEEN_UPDATES, 
                        LOW_PULSE_LENGTH, LOWER_DEADZONE_WIDTH, 
                        CENTER_PULSE_LENGTH, CENTER_DEADZONE_WIDTH, 
                        HIGH_PULSE_LENGTH, HIGHER_DEADZONE_WIDTH, 
                        INVALID_LOW_THRESHOLD, INVALID_HIGH_THRESHOLD);

//to be included for each instance of RcPwmChannel since interrupts must be public and can not belong to members
void InterruptHandlerChannel1(){
    channel1.updatePwmChannel();
}

void setup() {

    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_1_PIN), InterruptHandlerChannel1, CHANGE);    //attach ISR

}

void loop() {

    Serial.print("channel1:");
    Serial.print(channel1.getPulseLength());
    Serial.print(" , ");
    Serial.print("channel1[%]:");
    Serial.print(channel1.getSignalPercent());
    Serial.print(" , ");
    Serial.print("channel1-signal-health:");
    Serial.println(channel1.rcSignalIsHealthy());
    delay(10);

}