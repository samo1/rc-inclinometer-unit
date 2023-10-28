#pragma once

#include <TaskSchedulerDeclarations.h>
#include "debug.h"
#include "notes.h"

#define BUZZER_PIN D3
#define SOUND_TASK_INTERVAL 50

enum class SoundTaskPhase { off, note, pause };

struct CurrenMelodyState {
    const int* startPointer = nullptr;
    size_t length = 0;
    size_t pos = 0;
    SoundTaskPhase phase = SoundTaskPhase::off;

    String toString() const {
        String s = "melody length:";
        s += length;
        s += " pos:";
        s += pos;
        s += " phase:";
        s += static_cast<int>(phase);
        return s;
    }
};

// note, note duration, delay without sound
static const int rollWarning1Melody[] = {NOTE_B4, 1, 1};
static const int rollWarning2Melody[] = {NOTE_B4, 2, 2};
static const int pitchWarningMelody[] = {NOTE_D4, 2, 2};
static const int rollAndPitchWarningMelody[] = {NOTE_B4, 1, 1, NOTE_D4, 1, 1};

class Sound : public Task {
public:
    explicit Sound(Scheduler *scheduler) : Task(SOUND_TASK_INTERVAL, TASK_FOREVER, scheduler, false) {}
    void initialize();
    bool Callback() override;
    void rollWarning1();
    void rollWarning2();
    void pitchWarning();
    void rollAndPitchWarning();
    void silence();

private:
    CurrenMelodyState currentMelody{};
    void setCurrentMelody(const int* melody, size_t size);
};
