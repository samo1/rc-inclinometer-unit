#include "winch.h"
#include "debug.h"

void Winch::initialize() {
    DEBUG_PRINTLN("Attaching winch control on D9");
    servo.attach(D9);
}

void Winch::stop() {
    DEBUG_PRINTLN("Winch stop");
    servo.write(0);
}

void Winch::in() {
    DEBUG_PRINTLN("Winch in");
    servo.write(45);
}

void Winch::out() {
    DEBUG_PRINTLN("Winch out");
    servo.write(135);
}
