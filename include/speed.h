#pragma once

// Speedometer
class Speed {
public:
    static void initialize();
    static double getSpeedKmh();
    static double getDistanceMeters();
    static unsigned long getTickNr();
    static void persist();
    static void reset();
    static double calculateSpeedKmh(unsigned long timeDiffMicros);
    static void setDistancePerRevolution(double mmDistance);

private:
    static double mmDistancePerRevolution;
};
