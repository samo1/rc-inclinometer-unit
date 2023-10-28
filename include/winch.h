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
    String getInfo();

private:
    Servo servo;
    bool enabled = false;
    // first char E = enabled, D = disabled
    // second char S = stopped, I = winching in, O = winching out
    String info = String("DS");
};

#endif // WINCH_H
