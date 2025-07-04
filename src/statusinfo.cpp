#include "statusinfo.h"

void StatusInfo::winchEnabled() {
    info[0] = 'E';
}

void StatusInfo::winchDisabled() {
    info[0] = 'D';
}

void StatusInfo::winchStopped() {
    info[1] = 'S';
}

void StatusInfo::winchIn() {
    info[1] = 'I';
}

void StatusInfo::winchOut() {
    info[1] = 'O';
}

void StatusInfo::digEnabled() {
    info[2] = 'E';
}

void StatusInfo::digDisabled() {
    info[2] = 'D';
}

void StatusInfo::soundEnabled() {
    info[3] = 'E';
}

void StatusInfo::soundDisabled() {
    info[3] = 'D';
}

void StatusInfo::setDistancePerRevolution(double value) {
    char buffer[9];
    sprintf(buffer, "%08.3f", value);
    info = info.substring(0, 4) + String(buffer);
}

String StatusInfo::getInfo() {
    previousInfo = info;
    return info;
}

bool StatusInfo::isChanged() {
    return info != previousInfo;
}
