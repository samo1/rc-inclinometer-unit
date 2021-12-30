//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x) \
  do                   \
  {                    \
  } while (0)
#define DEBUG_PRINTLN(x) \
  do                     \
  {                      \
  } while (0)
#endif

#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>
#include <Servo.h>
#include "pitches.h"

const int maxPitchRollCharSize = 32;
const int maxWinchControlCharSize = 32;

BLEService infoService("be75903a-14b3-11ec-a7df-e069953c4ba2");
BLEStringCharacteristic pitchRollChar("d6c77054-14b3-11ec-b16c-e069953c4ba2", BLERead | BLENotify, maxPitchRollCharSize);
BLEStringCharacteristic winchControlChar("4eae0d40-699f-11ec-b55b-e069953c4ba2", BLEWrite, maxWinchControlCharSize);

String previousPitchRoll = "0:0";
long previousMillis = 0;

const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

Servo winch;

void introSound()
{
  tone(D3, NOTE_C4, 250);
  delay(300);
  noTone(D3);
}

void winchStop() {
  DEBUG_PRINTLN("Winch stop");
  winch.write(0);
}

void winchIn() {
  DEBUG_PRINTLN("Winch in");
  winch.write(45);
}

void winchOut() {
  DEBUG_PRINTLN("Winch out");
  winch.write(135);
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Started");
#endif

  if (!IMU.begin())
  {
    DEBUG_PRINTLN("Failed to initialize IMU!");
    while (1)
      ;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D3, OUTPUT);

  if (!BLE.begin())
  {
    DEBUG_PRINTLN("starting BLE failed!");
    while (1)
      ;
  }

  BLE.setLocalName("RC-inclinometer");
  BLE.setAdvertisedService(infoService);
  infoService.addCharacteristic(pitchRollChar);
  infoService.addCharacteristic(winchControlChar);
  BLE.addService(infoService);
  pitchRollChar.writeValue(previousPitchRoll);

  DEBUG_PRINTLN("Attaching winch control on D9");
  winch.attach(D9);

  BLE.advertise();
  DEBUG_PRINTLN("Bluetooth device active, waiting for connections...");

  introSound();
}

void updatePitchRoll(bool connected)
{
  float pitch, roll, Xg, Yg, Zg;

  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(Xg, Yg, Zg);

    //Low Pass Filter
    fXg = Xg * alpha + (fXg * (1.0 - alpha));
    fYg = Yg * alpha + (fYg * (1.0 - alpha));
    fZg = Zg * alpha + (fZg * (1.0 - alpha));

    //Roll & Pitch Equations
    roll = (atan2(-fYg, fZg) * 180.0) / PI;
    pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / PI;

    String currentPitchRoll = "";
    currentPitchRoll += static_cast<int>(pitch);
    currentPitchRoll += ":";
    currentPitchRoll += static_cast<int>(roll);

    if (currentPitchRoll.compareTo(previousPitchRoll) != 0)
    {
      previousPitchRoll = currentPitchRoll;
      DEBUG_PRINTLN(currentPitchRoll);
      if (connected)
      {
        pitchRollChar.writeValue(currentPitchRoll.substring(0, maxPitchRollCharSize - 1));
      }
    }

    if (pitch > 65 || pitch < -65)
    {
      tone(D3, 300, 100);
      delay(100);
      noTone(D3);
    }

    if (roll > 45 || roll < -45)
    {
      tone(D3, 500, 100);
      delay(100);
      noTone(D3);
    }
    else if (roll > 40 || roll < -40)
    {
      tone(D3, 500, 50);
      delay(50);
      noTone(D3);
    }
  }
}

void loop()
{
  BLEDevice central = BLE.central();
  if (central)
  {
    DEBUG_PRINT("Connected to central: ");
    DEBUG_PRINTLN(central.address());

    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected())
    {
      long currentMillis = millis();
      if (currentMillis - previousMillis >= 200)
      {
        previousMillis = currentMillis;
        updatePitchRoll(true);
      }

      if (winchControlChar.written()) {
        String controlString = winchControlChar.value();
        if (controlString.equalsIgnoreCase("stop")) {
          winchStop();
        } else if (controlString.equalsIgnoreCase("in")) {
          winchIn();
        } else if (controlString.equalsIgnoreCase("out")) {
          winchOut();
        }
      }
    }

    digitalWrite(LED_BUILTIN, LOW);

    DEBUG_PRINT("Disconnected from central: ");
    DEBUG_PRINTLN(central.address());
  }
  else
  {
    long currentMillis = millis();
    if (currentMillis - previousMillis >= 200)
    {
      previousMillis = currentMillis;
      updatePitchRoll(false);
    }
  }
}
