#pragma once

#include "NanoBLEFlashPrefs.h"

struct PreferencesData {
    unsigned long totalDistanceMeters;
};

class Preferences {
private:
    PreferencesData data{};
    NanoBLEFlashPrefs flashPrefs;
public:
    void writeTotalDistanceMeters(unsigned long value);
    unsigned long readTotalDistanceMeters();
};
