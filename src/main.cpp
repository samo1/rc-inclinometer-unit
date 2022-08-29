#define _TASK_OO_CALLBACKS

#include <TaskScheduler.h>

#include "bluetooth.h"
#include "debug.h"
#include "incline.h"
#include "receiver.h"
#include "sound.h"
#include "winch.h"

Scheduler scheduler;
Bluetooth bluetooth;
Incline incline;
Receiver receiver;
Sound sound(&scheduler);
Winch winch;

void updateInclineData() {
    PitchRoll pitchRoll = incline.read();
    if (pitchRoll.valid) {
        bluetooth.updatePitchRoll(pitchRoll);

        bool pitchWarning = pitchRoll.pitch > 65 || pitchRoll.pitch < -65;
        bool rollWarning1 = pitchRoll.roll > 45 || pitchRoll.roll < -45;
        bool rollWarning2 = pitchRoll.roll > 40 || pitchRoll.roll < -40;

        if ((rollWarning1 || rollWarning2) && pitchWarning) {
            sound.rollAndPitchWarning();
        } else if (rollWarning1) {
            sound.rollWarning1();
        } else if (rollWarning2) {
            sound.rollWarning2();
        } else if (pitchWarning) {
            sound.pitchWarning();
        } else {
            sound.silence();
        }
    }
}

void updateWinchControl() {
    String controlString = bluetooth.getWinchControlString();
    if (controlString.equalsIgnoreCase("stop")) {
        winch.stop();
    } else if (controlString.equalsIgnoreCase("in")) {
        winch.in();
    } else if (controlString.equalsIgnoreCase("out")) {
        winch.out();
    }
}

class MainTask : public Task {
public:
    explicit MainTask(Scheduler* s) : Task(100, TASK_FOREVER, s, false) {}
    bool Callback() override {
        bluetooth.checkConnection();
        updateInclineData();
        updateWinchControl();

        unsigned long receiverValue = receiver.readValue();

        return false;
    }
};

MainTask mainTask(&scheduler);

void setup() {
    DEBUG_INIT;
    incline.initialize();
    receiver.initialize();
    winch.initialize();
    bluetooth.initialize();
    sound.initialize();
    mainTask.enable();
}

void loop() {
    scheduler.execute();
}
