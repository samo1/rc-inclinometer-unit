#include "winch.h"
#include "debug.h"

void Winch::initialize() {
    DEBUG_PRINTLN("Attaching winch control");
    servo.attach(D9);
#ifdef L298N_WINCH_CONTROLLER
    pinMode(D11, OUTPUT);
    pinMode(D12, OUTPUT);
#endif
    stop();
    disable();
}

void Winch::stop() {
    DEBUG_PRINTLN("Winch stop");
#ifdef L298N_WINCH_CONTROLLER
    digitalWrite(D11, LOW);
    digitalWrite(D12, LOW);
#endif
    servo.write(0);
    statusInfo.winchStopped();
}

void Winch::in() {
    DEBUG_PRINTLN("Winch in");
    if (enabled) {
#ifdef L298N_WINCH_CONTROLLER
        digitalWrite(D11, LOW);
        digitalWrite(D12, HIGH);
        servo.write(180);
#else
        servo.write(45);
#endif
        statusInfo.winchIn();
    }
}

void Winch::out() {
    DEBUG_PRINTLN("Winch out");
    if (enabled) {
#ifdef L298N_WINCH_CONTROLLER
        digitalWrite(D11, HIGH);
        digitalWrite(D12, LOW);
        servo.write(180);
#else
        servo.write(135);
#endif
        statusInfo.winchOut();
    }
}

void Winch::enable() {
    DEBUG_PRINTLN("Winch enable");
    enabled = true;
    statusInfo.winchEnabled();
}

void Winch::disable() {
    DEBUG_PRINTLN("Winch disable");
    stop();
    enabled = false;
    statusInfo.winchDisabled();
}
