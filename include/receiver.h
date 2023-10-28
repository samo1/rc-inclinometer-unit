#pragma once

#include "debug.h"

// command to be executed, based on the physical switch position and the internal state
enum class ReceiverCommand { none, winchStop, winchIn, winchOut };

// internal state machine
enum class ReceiverState { winchStopped, winchingIn, winchingOut };

// current position of the physical switch on the controller
enum class SwitchPosition { off, up, down };

class Receiver {
public:
    static void initialize();
    ReceiverCommand readCommand();
private:
    ReceiverState state = ReceiverState::winchStopped;
    static SwitchPosition readSwitchPosition();
};
