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

String StatusInfo::getInfo() {
    previousInfo = info;
    return info;
}

bool StatusInfo::isChanged() {
    return info != previousInfo;
}
