#pragma once

#include <Arduino.h>

#define INITIAL_STATUS_INFO "DSD"

class StatusInfo {
public:
    void winchEnabled();
    void winchDisabled();
    void winchStopped();
    void winchIn();
    void winchOut();
    void digEnabled();
    void digDisabled();
    String getInfo();
    bool isChanged();

private:
    // first char E = winch enabled, D = winch disabled
    // second char S = winch stopped, I = winching in, O = winching out
    // second char E = front dig enabled, D = front dig disabled
    String info = String(INITIAL_STATUS_INFO);
    String previousInfo = String(INITIAL_STATUS_INFO);
};
