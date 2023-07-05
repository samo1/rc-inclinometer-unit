#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "incline.h"
#include "debug.h"

void Incline::initialize() {
    if (!IMU.begin()) {
        DEBUG_PRINTLN("Failed to initialize IMU!");
        while (true);
    }
}

PitchRoll Incline::read() {
    double pitch, roll;
    float Xg, Yg, Zg;
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(Xg, Yg, Zg);

        // Low Pass Filter
        fXg = Xg * alpha + (fXg * (1.0 - alpha));
        fYg = Yg * alpha + (fYg * (1.0 - alpha));
        fZg = Zg * alpha + (fZg * (1.0 - alpha));

        // Roll & Pitch Equations
        roll = (atan2(-fYg, fZg) * 180.0) / PI;
        pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / PI;

        PitchRoll pitchRoll(true, pitch, roll);
        return pitchRoll;
    } else {
        PitchRoll pitchRoll(false, 0.0, 0.0);
        return pitchRoll;
    }
}
