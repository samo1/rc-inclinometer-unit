#pragma once

#include "NanoBLEFlashPrefs.h"

struct PreferencesData {
    unsigned long totalDistanceMeters;
};

class Preferences {
private:
    PreferencesData data{};
    NanoBLEFlashPrefs flashPrefs;
    void readPrefs();
    void writePrefs();
public:
    void initialize();
    void writeTotalDistanceMeters(unsigned long value);
    unsigned long readTotalDistanceMeters();
};
