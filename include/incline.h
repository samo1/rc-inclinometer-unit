#pragma once

#include "pitchroll.h"

class Incline {
public:
    void initialize();
    PitchRoll read();

private:
    const double alpha = 0.5;
    double fXg = 0;
    double fYg = 0;
    double fZg = 0;
};
