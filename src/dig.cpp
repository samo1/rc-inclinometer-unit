#include "dig.h"
#include "debug.h"

#define FRONT_DIG_OFF 113
#define FRONT_DIG_OFF_2 115
#define FRONT_DIG_OFF_2_DELAY_MS 1000
#define FRONT_DIG_ON 30

void Dig::initialize() {
    DEBUG_PRINTLN("Attaching dig control on D6");
    servo.attach(D6);
    disableFrontDig();
}

void Dig::enableFrontDig() {
    DEBUG_PRINTLN("Enable front dig");
    servo.write(FRONT_DIG_ON);
    statusInfo.digEnabled();
}

void Dig::disableFrontDig() {
    DEBUG_PRINTLN("Disable front dig");
    servo.write(FRONT_DIG_OFF);
    digDisableTask.restartDelayed(FRONT_DIG_OFF_2_DELAY_MS);
    statusInfo.digDisabled();
}

bool DigDisableTask::Callback() {
    DEBUG_PRINTLN("Disable front dig (step 2)");
    dig->servo.write(FRONT_DIG_OFF_2);
    dig->statusInfo.digDisabled();
    return true;
}
