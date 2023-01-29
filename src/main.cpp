#define _TASK_OO_CALLBACKS

#include <TaskScheduler.h>
#include <ezButton.h>

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
ezButton toggleSwitch(D2);

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

void updateWinchControl(const String& controlString, ReceiverCommand receiverCommand) {
    if (receiverCommand == ReceiverCommand::winchStop) {
        winch.stop();
    } else if (receiverCommand == ReceiverCommand::winchIn) {
        winch.in();
    } else if (receiverCommand == ReceiverCommand::winchOut) {
        winch.out();
    } else {
        if (controlString.equalsIgnoreCase("stop")) {
            winch.stop();
        } else if (controlString.equalsIgnoreCase("in")) {
            winch.in();
        } else if (controlString.equalsIgnoreCase("out")) {
            winch.out();
        }
    }
}

class MainTask : public Task {
public:
    explicit MainTask(Scheduler* s) : Task(100, TASK_FOREVER, s, false) {}
    bool Callback() override {
        bluetooth.checkConnection();
        updateInclineData();
        String controlString = bluetooth.getWinchControlString();
        ReceiverCommand receiverCommand = receiver.readCommand();
        updateWinchControl(controlString, receiverCommand);
        return false;
    }
};

MainTask mainTask(&scheduler);

void setup() {
    DEBUG_INIT;
    toggleSwitch.setDebounceTime(50);
    incline.initialize();
    Receiver::initialize();
    winch.initialize();
    bluetooth.initialize();
    sound.initialize();
    mainTask.enable();
}

void loop() {
    scheduler.execute();
    toggleSwitch.loop();
    if (toggleSwitch.isPressed()) {
        DEBUG_PRINTLN("The switch: OFF -> ON");
        winch.enable();
    }
    if (toggleSwitch.isReleased()) {
        DEBUG_PRINTLN("The switch: ON -> OFF");
        winch.disable();
    }
}
