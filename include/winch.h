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

private:
    Servo servo;
};

#endif // WINCH_H
