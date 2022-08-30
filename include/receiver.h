#ifndef RECEIVER_H
#define RECEIVER_H

#include "debug.h"

enum class ReceiverCommand { none, winchStop, winchIn, winchOut };
enum class ReceiverState { winchStopped, winchingIn, winchingOut };
enum class SwitchPosition { off, up, down };

class Receiver {
public:
    static void initialize();
    ReceiverCommand readCommand();
private:
    ReceiverState state = ReceiverState::winchStopped;
    static SwitchPosition readSwitchPosition();
};

#endif // RECEIVER_H
