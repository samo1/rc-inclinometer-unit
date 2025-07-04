#include "preferences.h"
#include "debug.h"
#include <NanoBLEFlashPrefs.h>

void Preferences::initialize() {
    readPrefs();
    flashPrefs.garbageCollection();
    writePrefs();
}

void Preferences::writeTotalDistanceMeters(unsigned long value) {
    data.totalDistanceMeters = value;
    writePrefs();
}

unsigned long Preferences::readTotalDistanceMeters() {
    readPrefs();
    return data.totalDistanceMeters;
}

void Preferences::writeMmDistancePerRevolution(double value) {
    data.mmDistancePerRevolution = value;
    writePrefs();
}

double Preferences::readMmDistancePerRevolution() {
    readPrefs();
    return data.mmDistancePerRevolution;
}

void Preferences::readPrefs() {
    DEBUG_PRINTLN("Reading preferences");
    int8_t rc = flashPrefs.readPrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("No preferences found");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
}

void Preferences::writePrefs() {
    DEBUG_PRINTLN("Writing preferences");
    int8_t rc = flashPrefs.writePrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("Error writing preferences");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
}
