#include "winch.h"
#include "debug.h"

void Winch::initialize() {
    DEBUG_PRINTLN("Attaching winch control on D9");
    servo.attach(D9);
    stop();
    disable();
}

void Winch::stop() {
    DEBUG_PRINTLN("Winch stop");
    servo.write(0);
    statusInfo.winchStopped();
}

void Winch::in() {
    DEBUG_PRINTLN("Winch in");
    if (enabled) {
        servo.write(45);
        statusInfo.winchIn();
    }
}

void Winch::out() {
    DEBUG_PRINTLN("Winch out");
    if (enabled) {
        servo.write(135);
        statusInfo.winchOut();
    }
}

void Winch::enable() {
    enabled = true;
    statusInfo.winchEnabled();
}

void Winch::disable() {
    stop();
    enabled = false;
    statusInfo.winchDisabled();
}
