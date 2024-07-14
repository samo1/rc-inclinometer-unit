#include "preferences.h"
#include "debug.h"
#include <NanoBLEFlashPrefs.h>

void Preferences::writeSpeedMeterTickNr(unsigned long value) {
    DEBUG_PRINTLN("Writing preferences");
    data.speedMeterTickNr = value;
    int8_t rc = flashPrefs.writePrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("Error writing preferences");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
}

unsigned long Preferences::readSpeedMeterTickNr() {
    DEBUG_PRINTLN("Reading preferences");
    int8_t rc = flashPrefs.readPrefs(&data, sizeof(data));
    if (rc != FDS_SUCCESS) {
        DEBUG_PRINTLN("No preferences found");
        DEBUG_PRINTLN(flashPrefs.errorString(rc));
    }
    return data.speedMeterTickNr;
}
