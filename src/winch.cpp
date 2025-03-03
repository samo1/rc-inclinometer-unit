#include "winch.h"
#include "debug.h"

#define PWM_PIN D9

void Winch::initialize() {
    DEBUG_PRINTLN("Attaching winch control");
#ifdef L298N_WINCH_CONTROLLER
    pinMode(D11, OUTPUT);
    pinMode(D12, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);
#else
    servo.attach(PWM_PIN);
#endif
    stop();
    disable();
}

void Winch::stop() {
    DEBUG_PRINTLN("Winch stop");
#ifdef L298N_WINCH_CONTROLLER
    digitalWrite(D11, LOW);
    digitalWrite(D12, LOW);
    analogWrite(PWM_PIN, 0);
#else
    servo.write(0);
#endif
    statusInfo.winchStopped();
}

void Winch::in() {
    DEBUG_PRINTLN("Winch in");
    if (enabled) {
#ifdef L298N_WINCH_CONTROLLER
        digitalWrite(D11, LOW);
        digitalWrite(D12, HIGH);
        analogWrite(PWM_PIN, 255);
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
        analogWrite(PWM_PIN, 255);
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
