#include "preferences.h"
#include "debug.h"
#include <NanoBLEFlashPrefs.h>

void Preferences::writeTotalDistanceMeters(unsigned long value) {
    DEBUG_PRINTLN("Writing preferences");
    data.totalDistanceMeters = value;
    int8_t rc = flashPrefs.writePrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("Error writing preferences");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
}

unsigned long Preferences::readTotalDistanceMeters() {
    DEBUG_PRINTLN("Reading preferences");
    int8_t rc = flashPrefs.readPrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("No preferences found");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
    return data.totalDistanceMeters;
}
