#ifndef INCLINE_H
#define INCLINE_H

#include "pitchroll.h"

class Incline {
public:
    void initialize();
    PitchRoll read();

private:
    const float alpha = 0.5;
    double fXg = 0;
    double fYg = 0;
    double fZg = 0;
};

#endif // INCLINE_H
