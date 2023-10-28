#pragma once

class PitchRoll {
public:
    bool valid;
    double pitch;
    double roll;

    PitchRoll(bool valid, double p, double r);
    String toString() const;
};
