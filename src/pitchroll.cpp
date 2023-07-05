#include <Arduino.h>
#include "pitchroll.h"

PitchRoll::PitchRoll(bool v, double p, double r) : valid(v), pitch(p), roll(r) {}

String PitchRoll::toString() const {
    String s = "";
    if (valid) {
        s += static_cast<int>(pitch);
        s += ":";
        s += static_cast<int>(roll);
    }
    return s;
}
