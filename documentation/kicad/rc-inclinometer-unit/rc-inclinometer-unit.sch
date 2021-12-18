EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino:Arduino_Nano U?
U 1 1 6170AB08
P 5600 3500
F 0 "U?" H 5600 4467 50  0000 C CNN
F 1 "Arduino Nano 33 BLE Sense" H 5600 4376 50  0000 C CNN
F 2 "Arduino:Arduino_Nano" H 5600 2650 50  0001 C CNN
F 3 "https://store.arduino.cc/usa/arduino-nano" H 5600 3400 50  0001 C CNN
	1    5600 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 61705681
P 6650 2750
F 0 "#PWR?" H 6650 2600 50  0001 C CNN
F 1 "+5V" H 6665 2923 50  0000 C CNN
F 2 "" H 6650 2750 50  0001 C CNN
F 3 "" H 6650 2750 50  0001 C CNN
	1    6650 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61716A22
P 6650 2950
F 0 "#PWR?" H 6650 2700 50  0001 C CNN
F 1 "GND" H 6655 2777 50  0000 C CNN
F 2 "" H 6650 2950 50  0001 C CNN
F 3 "" H 6650 2950 50  0001 C CNN
	1    6650 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2900 6650 2950
Wire Wire Line
	6200 2900 6450 2900
Wire Wire Line
	6200 2800 6650 2800
Wire Wire Line
	6650 2800 6650 2750
Text GLabel 6950 3900 1    50   Input ~ 0
GND
Text GLabel 6850 3900 1    50   Input ~ 0
IO
Text GLabel 6750 3900 1    50   Input ~ 0
VCC
Text Notes 6950 3400 3    50   ~ 0
Passive\nbuzzer\nmodule
Text Notes 6700 2850 0    50   ~ 0
RC Receiver
Wire Wire Line
	6450 2900 6450 3300
Wire Wire Line
	6450 3300 7250 3300
Wire Wire Line
	7250 3300 7250 4150
Wire Wire Line
	7250 4150 6950 4150
Wire Wire Line
	6950 4150 6950 3900
Connection ~ 6450 2900
Wire Wire Line
	6450 2900 6650 2900
Wire Wire Line
	5000 3300 4800 3300
Wire Wire Line
	4800 3300 4800 4500
Wire Wire Line
	4800 4500 6850 4500
Wire Wire Line
	6850 4500 6850 3900
Wire Wire Line
	6200 4100 6750 4100
Wire Wire Line
	6750 4100 6750 3900
$EndSCHEMATC
