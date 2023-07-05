#include "bluetooth.h"
#include "debug.h"

void Bluetooth::initialize() {
    pinMode(LED_BUILTIN, OUTPUT);

    if (!BLE.begin()) {
        DEBUG_PRINTLN("starting BLE failed!");
        while (true);
    }

    BLE.setLocalName("RC-inclinometer");
    BLE.setAdvertisedService(infoService);
    infoService.addCharacteristic(pitchRollChar);
    infoService.addCharacteristic(winchControlChar);
    BLE.addService(infoService);
    pitchRollChar.writeValue(previousPitchRoll);

    BLE.advertise();
    DEBUG_PRINTLN("Bluetooth device active, waiting for connections...");
}

void Bluetooth::checkConnection() {
    if (connected) {
        if (!central.connected()) {
            connected = false;
            digitalWrite(LED_BUILTIN, LOW);
            DEBUG_PRINT("Disconnected from central: ");
            DEBUG_PRINTLN(central.address());
        }
    } else {
        central = BLE.central();
        if (central) {
            connected = central.connected();
            if (connected) {
                digitalWrite(LED_BUILTIN, HIGH);
                DEBUG_PRINT("Connected to central: ");
                DEBUG_PRINTLN(central.address());
            }
        }
    }
}

void Bluetooth::updatePitchRoll(PitchRoll pitchRoll) {
    String currentPitchRoll = pitchRoll.toString();
    if (currentPitchRoll.compareTo(previousPitchRoll) != 0) {
        previousPitchRoll = currentPitchRoll;
        DEBUG_PRINTLN(currentPitchRoll);
        if (connected) {
            pitchRollChar.writeValue(currentPitchRoll.substring(0, maxPitchRollCharSize - 1));
        }
    }
}

String Bluetooth::getWinchControlString() {
    if (connected && winchControlChar.written()) {
        String controlString = winchControlChar.value();
        return controlString;
    } else {
        String controlString = "";
        return controlString;
    }
}
