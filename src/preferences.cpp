#include "preferences.h"
#include "debug.h"
#include <NanoBLEFlashPrefs.h>

extern ret_code_t fds_init_ret_code;

void Preferences::initialize() {
    DEBUG_PRINT("FDS init ret code: ");
    DEBUG_PRINT(fds_init_ret_code);
    DEBUG_PRINT(" - ");
    DEBUG_PRINTLN(flashPrefs.errorString(fds_init_ret_code));

    fds_stat_t stats;
    ret_code_t fds_stat_ret_code = fds_stat(&stats);
    DEBUG_PRINT("FDS stat ret code: ");
    DEBUG_PRINT(fds_stat_ret_code);
    DEBUG_PRINT(" - ");
    DEBUG_PRINTLN(flashPrefs.errorString(fds_stat_ret_code));
    static char str[1000];
    sprintf(str, "%d pages available, %d open records, %d valid records, %d dirty, %d corruption, %d words used, %d freeable words",
            stats.pages_available,
            stats.open_records,
            stats.valid_records,
            stats.dirty_records,
            stats.corruption,
            stats.words_used,
            stats.freeable_words);
    DEBUG_PRINTLN(str);

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
