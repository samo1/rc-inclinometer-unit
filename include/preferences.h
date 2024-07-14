#pragma once

#include "NanoBLEFlashPrefs.h"

struct PreferencesData {
    unsigned long speedMeterTickNr;
};

class Preferences {
private:
    PreferencesData data{};
    NanoBLEFlashPrefs flashPrefs;
public:
    void writeSpeedMeterTickNr(unsigned long value);
    unsigned long readSpeedMeterTickNr();
};
