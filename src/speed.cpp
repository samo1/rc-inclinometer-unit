#include "speed.h"
#include <Arduino.h>

#define HALL_SENSOR_DOUT D10
#define HALL_SENSOR_AOUT PIN_A0

#define MM_DISTANCE_PER_REVOLUTION (double) 10.0

volatile unsigned long tickNr;
volatile unsigned long tickTime;
volatile unsigned long lastTimeDiff;
volatile double speed;

double calculateSpeed(unsigned long timeDiff) {
    return (double) 3600.0 * MM_DISTANCE_PER_REVOLUTION / (double) timeDiff;
}

void onTick() {
    tickNr++;
    auto oldTickTime = tickTime;
    tickTime = micros();
    lastTimeDiff = tickTime - oldTickTime;
    speed = calculateSpeed(lastTimeDiff);
}

void Speed::initialize() {
    tickNr = 0;
    tickTime = micros();
    pinMode(HALL_SENSOR_DOUT, INPUT);
    pinMode(HALL_SENSOR_AOUT, INPUT);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_DOUT), onTick, FALLING);
}

double Speed::getSpeed() {
    auto timeDiffToLastTick = micros() - tickTime;
    if (timeDiffToLastTick > lastTimeDiff) {
        return calculateSpeed(timeDiffToLastTick);
    }
    return speed;
}

unsigned long Speed::getTickNr() {
    return tickNr;
}
