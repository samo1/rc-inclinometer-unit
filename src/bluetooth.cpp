#include "bluetooth.h"
#include "debug.h"
#include "statusinfo.h"

void Bluetooth::initialize() {
    pinMode(LED_BUILTIN, OUTPUT);

    if (!BLE.begin()) {
        DEBUG_PRINTLN("starting BLE failed!");
        while (true);
    }

    BLE.setLocalName("RC-inclinometer");
    BLE.setAdvertisedService(infoService);
    infoService.addCharacteristic(pitchRollChar);
    infoService.addCharacteristic(winchInfoChar);
    infoService.addCharacteristic(winchControlChar);
    infoService.addCharacteristic(speedChar);
    BLE.addService(infoService);
    pitchRollChar.writeValue(previousPitchRoll);
    String initialWinchInfo(INITIAL_STATUS_INFO);
    winchInfoChar.writeValue(initialWinchInfo);
    speedChar.writeValue(previousSpeed);

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

void Bluetooth::updateWinchInfo(const String& winchInfo) {
    if (connected) {
        String message = winchInfo.substring(0, maxWinchInfoCharSize - 1);
        DEBUG_PRINT("Sending winch info: ");
        DEBUG_PRINTLN(message);
        winchInfoChar.writeValue(message);
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

void Bluetooth::updateSpeed(double speed, unsigned long tickNr) {
    String currentSpeed = String(speed, 2) + String(";") + String(tickNr);
    if (currentSpeed.compareTo(previousSpeed) != 0) {
        previousSpeed = currentSpeed;
        DEBUG_PRINTLN(currentSpeed);
        if (connected) {
            speedChar.writeValue(currentSpeed.substring(0, maxSpeedCharSize - 1));
        }
    }
}
