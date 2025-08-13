#include "winch.h"
#include "debug.h"

#define PWM_PIN D9
#define CONTROL_PIN_1 D7
#define CONTROL_PIN_2 D8

void Winch::initialize() {
    DEBUG_PRINTLN("Attaching winch control");
#ifdef L298N_WINCH_CONTROLLER
    pinMode(CONTROL_PIN_1, OUTPUT);
    pinMode(CONTROL_PIN_2, OUTPUT);
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
    digitalWrite(CONTROL_PIN_1, LOW);
    digitalWrite(CONTROL_PIN_2, LOW);
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
        digitalWrite(CONTROL_PIN_1, LOW);
        digitalWrite(CONTROL_PIN_2, HIGH);
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
        digitalWrite(CONTROL_PIN_1, HIGH);
        digitalWrite(CONTROL_PIN_2, LOW);
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
