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
    info[1] = 'S';
}

void Winch::in() {
    DEBUG_PRINTLN("Winch in");
    if (enabled) {
        servo.write(45);
        info[1] = 'I';
    }
}

void Winch::out() {
    DEBUG_PRINTLN("Winch out");
    if (enabled) {
        servo.write(135);
        info[1] = 'O';
    }
}

void Winch::enable() {
    enabled = true;
    info[0] = 'E';
}

void Winch::disable() {
    enabled = false;
    info[0] = 'D';
}

String Winch::getInfo() {
    return info;
}
