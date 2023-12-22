#pragma once

// Speedometer
class Speed {
public:
    static void initialize();
    static double getSpeedKmh();
    static double getDistanceMeters();
    static unsigned long getTickNr();
};
