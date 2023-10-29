#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <TaskSchedulerDeclarations.h>
#include "statusinfo.h"

class Dig;

class DigDisableTask : public Task {
public:
    explicit DigDisableTask(Scheduler* s, Dig* dig) : Task(0, TASK_ONCE, s, false), dig(dig) {
        setSchedulingOption(TASK_INTERVAL);
    }
    bool Callback() override;
private:
    Dig* dig;
};

class Dig {
public:
    friend class DigDisableTask;
    explicit Dig(Scheduler *s, StatusInfo& statusInfo) : digDisableTask(s, this), statusInfo(statusInfo) {}
    void initialize();
    void enableFrontDig();
    void disableFrontDig();

private:
    Servo servo;
    DigDisableTask digDisableTask;
    StatusInfo& statusInfo;
};
