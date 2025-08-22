#include "preferences.h"
#include "debug.h"
#include <serialEEPROM.h>

#define EEPROM_I2C_ADDRESS 0x50

serialEEPROM externalEEPROM(EEPROM_I2C_ADDRESS, 32768, 64); // AT24C256

// TODO consider wear-levelling

void Preferences::initialize() {
    Wire.begin();
    readPrefs();
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
    PreferencesData storedData{};
    externalEEPROM.read(0, reinterpret_cast<uint8_t *>(&storedData), sizeof(storedData));
    if (storedData.version == data.version && storedData.mmDistancePerRevolution > 0) {
        memcpy(&data, &storedData, sizeof(storedData));
    }
}

void Preferences::writePrefs() {
    externalEEPROM.write(0, reinterpret_cast<uint8_t *>(&data), sizeof(data));
}
