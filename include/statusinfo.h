#pragma once

#include <Arduino.h>

#define INITIAL_STATUS_INFO "DSDE"

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
    String getInfo();
    bool isChanged();

private:
    // char 0: E = winch enabled, D = winch disabled
    // char 1: S = winch stopped, I = winching in, O = winching out
    // char 2: E = front dig enabled, D = front dig disabled
    // char 3: E = sound enabled, D = sound disabled
    String info = String(INITIAL_STATUS_INFO);
    String previousInfo = String(INITIAL_STATUS_INFO);
};
