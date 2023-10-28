#include <Arduino.h>
#include "receiver.h"

volatile unsigned long pulseBegin = micros();
volatile unsigned long pulseEnd = micros();
volatile unsigned long pulseDuration = 0;

static void receiverPinInterrupt() {
    if (digitalRead(D5) == HIGH) {
        pulseBegin = micros();
    } else {
        pulseEnd = micros();
        pulseDuration = pulseEnd - pulseBegin;
    }
}

void Receiver::initialize() {
    pinMode(D5, INPUT);
    attachInterrupt(digitalPinToInterrupt(D5), receiverPinInterrupt, CHANGE);
}

SwitchPosition Receiver::readSwitchPosition() {
    unsigned long d = pulseDuration;
    SwitchPosition p = SwitchPosition::off;
    if (d >= 1200 && d < 1300) {
        p = SwitchPosition::down;
    } else if (d >= 1800 && d < 1900) {
        p = SwitchPosition::up;
    }
    return p;
}

ReceiverCommand Receiver::readCommand() {
    ReceiverCommand cmd = ReceiverCommand::none;
    SwitchPosition position = readSwitchPosition();
    ReceiverState newState = state;
    if (state == ReceiverState::winchStopped) {
        if (position == SwitchPosition::down) {
            cmd = ReceiverCommand::winchIn;
            newState = ReceiverState::winchingIn;
        } else if (position == SwitchPosition::up) {
            cmd = ReceiverCommand::winchOut;
            newState = ReceiverState::winchingOut;
        }
    } else if (state == ReceiverState::winchingIn) {
        if (position == SwitchPosition::off) {
            cmd = ReceiverCommand::winchStop;
            newState = ReceiverState::winchStopped;
        } else if (position == SwitchPosition::up) {
            cmd = ReceiverCommand::winchOut;
            newState = ReceiverState::winchingOut;
        }
    } else if (state == ReceiverState::winchingOut) {
        if (position == SwitchPosition::off) {
            cmd = ReceiverCommand::winchStop;
            newState = ReceiverState::winchStopped;
        } else if (position == SwitchPosition::down) {
            cmd = ReceiverCommand::winchIn;
            newState = ReceiverState::winchingIn;
        }
    }
    state = newState;
    return cmd;
}
