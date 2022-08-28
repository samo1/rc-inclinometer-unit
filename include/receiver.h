#ifndef RECEIVER_H
#define RECEIVER_H

#include "debug.h"

class Receiver {
public:
    void initialize();
    unsigned long readValue();
};

#endif // RECEIVER_H
