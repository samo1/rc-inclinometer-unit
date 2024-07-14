#include "speed.h"
#include "preferences.h"
#include <Arduino.h>

#define HALL_SENSOR_DOUT D10
#define HALL_SENSOR_AOUT PIN_A0

#define MM_DISTANCE_PER_REVOLUTION 49.5

volatile unsigned long tickNr;
volatile unsigned long tickTime;
volatile unsigned long lastTimeDiff;
volatile double speed;

extern Preferences preferences;
unsigned long persistedTickNr;

double calculateSpeedKmh(unsigned long timeDiffMicros) {
    // mm / us ... (mm / 1e6) km / (us / (60 * 60 * 1e6)) h
    return 3600.0 * MM_DISTANCE_PER_REVOLUTION / (double) timeDiffMicros;
}

void onTick() {
    tickNr++;
    auto oldTickTime = tickTime;
    tickTime = micros();
    lastTimeDiff = tickTime - oldTickTime;
    speed = calculateSpeedKmh(lastTimeDiff);
}

void Speed::initialize() {
    persistedTickNr = preferences.readSpeedMeterTickNr();
    tickNr = persistedTickNr;
    tickTime = micros();
    pinMode(HALL_SENSOR_DOUT, INPUT);
    pinMode(HALL_SENSOR_AOUT, INPUT);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_DOUT), onTick, FALLING);
}

double Speed::getSpeedKmh() {
    auto timeDiffToLastTick = micros() - tickTime;
    if (timeDiffToLastTick > lastTimeDiff) {
        return calculateSpeedKmh(timeDiffToLastTick);
    }
    return speed;
}

double Speed::getDistanceMeters() {
    return tickNr * MM_DISTANCE_PER_REVOLUTION / 1000.0;
}

unsigned long Speed::getTickNr() {
    return tickNr;
}

void Speed::persist() {
    // persist cca every 50m
    if (tickNr - persistedTickNr > 1000 || tickNr < persistedTickNr) {
        persistedTickNr = tickNr;
        preferences.writeSpeedMeterTickNr(persistedTickNr);
    }
}

void Speed::reset() {
    tickNr = 0;
    persistedTickNr = 0;
    preferences.writeSpeedMeterTickNr(0);
}
