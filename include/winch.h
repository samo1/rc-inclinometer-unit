#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "statusinfo.h"

class Winch {
public:
    explicit Winch(StatusInfo& statusInfo) : statusInfo(statusInfo) {}
    void initialize();
    void stop();
    void in();
    void out();
    void enable();
    void disable();

private:
    Servo servo;
    bool enabled = false;
    StatusInfo& statusInfo;
};
