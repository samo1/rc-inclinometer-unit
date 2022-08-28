#ifndef PITCHROLL_H
#define PITCHROLL_H

class PitchRoll {
public:
    bool valid;
    float pitch;
    float roll;

    PitchRoll(bool valid, float p, float r);
    String toString() const;
};

#endif // PITCHROLL_H
