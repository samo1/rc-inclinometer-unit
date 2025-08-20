#pragma once

struct PreferencesData {
    int version = 1;
    unsigned long totalDistanceMeters = 0;
    double mmDistancePerRevolution = 49.5;
};

class Preferences {
private:
    PreferencesData data{};
    void readPrefs();
    void writePrefs();
public:
    void initialize();
    void writeTotalDistanceMeters(unsigned long value);
    unsigned long readTotalDistanceMeters();
    void writeMmDistancePerRevolution(double value);
    double readMmDistancePerRevolution();
};
