#include <Arduino.h>
#include "receiver.h"

volatile unsigned long pulseBegin = micros();
volatile unsigned long pulseEnd = micros();
volatile unsigned long pulseDuration = 0;

void receiverPinInterrupt() {
    if (digitalRead(D5) == HIGH) {
        pulseBegin = micros();
    } else {
        pulseEnd = micros();
        pulseDuration = pulseEnd - pulseBegin;
    }
}

void Receiver::initialize() {
    pinMode(D5, INPUT);
    attachInterrupt(digitalPinToInterrupt(D5), receiverPinInterrupt, CHANGE);
}

unsigned long Receiver::readValue() {
    //DEBUG_PRINT("Receiver value = ");
    //DEBUG_PRINTLN(pulseDuration);

    // old (dig):
    // Receiver value = 1224
    // Receiver value = 1836
    // Receiver value = 1500 1501 tx turned off

    // new:
    // Receiver value = 1500 1501 tx turned off
    // Receiver value = 0 tx turned off
    // 1500 - no press
    // 1836 - up
    // 1249 - down

    return pulseDuration;
}
