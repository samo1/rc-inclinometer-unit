#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <ArduinoBLE.h>
#include "pitchroll.h"

class Bluetooth {
public:
    Bluetooth() : infoService("be75903a-14b3-11ec-a7df-e069953c4ba2"),
                  pitchRollChar("d6c77054-14b3-11ec-b16c-e069953c4ba2", BLERead | BLENotify, maxPitchRollCharSize),
                  winchControlChar("4eae0d40-699f-11ec-b55b-e069953c4ba2", BLEWrite, maxWinchControlCharSize),
                  connected(false),
                  previousPitchRoll("0.0") {}

    void initialize();
    void checkConnection();
    void updatePitchRoll(PitchRoll pitchRoll);
    String getWinchControlString();

private:
    const int maxPitchRollCharSize = 32;
    const int maxWinchControlCharSize = 32;
    BLEService infoService;
    BLEStringCharacteristic pitchRollChar;
    BLEStringCharacteristic winchControlChar;
    BLEDevice central;
    bool connected;
    String previousPitchRoll;
};

#endif // BLUETOOTH_H
