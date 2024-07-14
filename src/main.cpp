#include <TaskScheduler.h>
#include <ezButton.h>

#include "bluetooth.h"
#include "debug.h"
#include "dig.h"
#include "incline.h"
#include "preferences.h"
#include "receiver.h"
#include "sound.h"
#include "speed.h"
#include "winch.h"

Scheduler scheduler;
Preferences preferences;
Bluetooth bluetooth;
StatusInfo statusInfo;
Dig dig(&scheduler, statusInfo);
Incline incline;
Receiver receiver;
Sound sound(&scheduler);
Winch winch(statusInfo);
ezButton toggleSwitch(D2);

static void updateInclineData() {
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

static void updateWinchControl(const String& controlString, ReceiverCommand receiverCommand) {
    if (controlString != "") {
        DEBUG_PRINT("BLE command '");
        DEBUG_PRINT(controlString);
        DEBUG_PRINTLN("'");
    }
    if (controlString.equalsIgnoreCase("enable")) {
        winch.enable();
    } else if (controlString.equalsIgnoreCase("disable")) {
        winch.disable();
    } else if (controlString.equalsIgnoreCase("dig_enable")) {
        dig.enableFrontDig();
    } else if (controlString.equalsIgnoreCase("dig_disable")) {
        dig.disableFrontDig();
    } else if (controlString.equalsIgnoreCase("reset_speed")) {
        Speed::reset();
    }
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
    if (statusInfo.isChanged()) {
        DEBUG_PRINTLN("Status changed");
        bluetooth.updateWinchInfo(statusInfo.getInfo());
    }
}

static void handleToggleSwitch() {
    toggleSwitch.loop();
    if (toggleSwitch.isPressed()) {
        DEBUG_PRINTLN("The switch: OFF -> ON");
        winch.enable();
    }
    if (toggleSwitch.isReleased()) {
        DEBUG_PRINTLN("The switch: ON -> OFF");
        winch.disable();
    }
    if (statusInfo.isChanged()) {
        DEBUG_PRINTLN("Status changed");
        bluetooth.updateWinchInfo(statusInfo.getInfo());
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
        bluetooth.updateSpeed(Speed::getSpeedKmh(), Speed::getDistanceMeters(), Speed::getTickNr());
        Speed::persist();
        return true;
    }
};

MainTask mainTask(&scheduler);

void setup() {
    DEBUG_INIT;
    toggleSwitch.setDebounceTime(50);
    dig.initialize();
    incline.initialize();
    Receiver::initialize();
    Speed::initialize();
    winch.initialize();
    bluetooth.initialize();
    sound.initialize();
    mainTask.enable();
}

void loop() {
    scheduler.execute();
    handleToggleSwitch();
}
