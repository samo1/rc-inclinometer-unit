#include <Arduino.h>
#include "receiver.h"

void Receiver::initialize() {
    pinMode(D5, INPUT);
}

unsigned long Receiver::readValue() {
    unsigned long duration = pulseIn(D5, HIGH);

    DEBUG_PRINT("Receiver value = ");
    DEBUG_PRINTLN(duration);
    // Receiver value = 1224
    // Receiver value = 1836

    return duration;
}
