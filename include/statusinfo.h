#pragma once

#include <Arduino.h>

#define INITIAL_STATUS_INFO "DSDE0049.500"

class StatusInfo {
public:
    void winchEnabled();
    void winchDisabled();
    void winchStopped();
    void winchIn();
    void winchOut();
    void digEnabled();
    void digDisabled();
    void soundEnabled();
    void soundDisabled();
    void setDistancePerRevolution(double value);
    String getInfo();
    bool isChanged();

private:
    // char 0: E = winch enabled, D = winch disabled
    // char 1: S = winch stopped, I = winching in, O = winching out
    // char 2: E = front dig enabled, D = front dig disabled
    // char 3: E = sound enabled, D = sound disabled
    // char 4-11: distance per revolution as 8-char string with 3 decimal places
    String info = String(INITIAL_STATUS_INFO);
    String previousInfo = String(INITIAL_STATUS_INFO);
};
