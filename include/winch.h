#ifndef WINCH_H
#define WINCH_H

#include <Arduino.h>
#include <Servo.h>

class Winch {
public:
    void initialize();
    void stop();
    void in();
    void out();
    void enable();
    void disable();

private:
    Servo servo;
    bool enabled = false;
};

#endif // WINCH_H
