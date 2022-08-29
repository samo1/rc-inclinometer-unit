#include <Arduino.h>
#include "receiver.h"

void Receiver::initialize() {
    pinMode(D5, INPUT);
}

unsigned long Receiver::readValue() {
    unsigned long duration = pulseIn(D5, HIGH);

    DEBUG_PRINT("Receiver value = ");
    DEBUG_PRINTLN(duration);

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

    return duration;
}
