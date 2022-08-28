#include <Arduino.h>
#include "sound.h"

void Sound::initialize() {
    pinMode(BUZZER_PIN, OUTPUT);

    tone(BUZZER_PIN, NOTE_C4, 250);
    ::delay(300);
    noTone(BUZZER_PIN);

    enable();
}

bool Sound::Callback() {
    const int* pointer = currentMelody.startPointer + currentMelody.pos * 3;
    int frequency;
    unsigned long duration;
    unsigned long delay;
    switch (currentMelody.phase) {
        case SoundTaskPhase::note:
            frequency = pointer[0];
            duration = pointer[1] * SOUND_TASK_INTERVAL;
            delay = pointer[1] * SOUND_TASK_INTERVAL;
            tone(BUZZER_PIN, frequency, duration);
            setInterval(delay);
            currentMelody.phase = SoundTaskPhase::pause;
            break;
        case SoundTaskPhase::pause:
            delay = pointer[2] * SOUND_TASK_INTERVAL;
            noTone(BUZZER_PIN);
            setInterval(delay);
            currentMelody.phase = SoundTaskPhase::note;
            currentMelody.pos++;
            if (currentMelody.pos >= currentMelody.length) {
                currentMelody.pos = 0;
            }
            break;
        case SoundTaskPhase::off:
        default:
            noTone(BUZZER_PIN);
            setInterval(SOUND_TASK_INTERVAL);
    }
    return false;
}

void Sound::rollWarning1() {
    setCurrentMelody(rollWarning1Melody, sizeof(rollWarning1Melody));
}

void Sound::rollWarning2() {
    setCurrentMelody(rollWarning2Melody, sizeof(rollWarning2Melody));
}

void Sound::pitchWarning() {
    setCurrentMelody(pitchWarningMelody, sizeof(pitchWarningMelody));
}

void Sound::rollAndPitchWarning() {
    setCurrentMelody(rollAndPitchWarningMelody, sizeof(rollAndPitchWarningMelody));
}

void Sound::silence() {
    currentMelody.phase = SoundTaskPhase::off;
    currentMelody.startPointer = nullptr;
}

void Sound::setCurrentMelody(const int* melody, size_t size) {
    if (currentMelody.startPointer != melody) {
        currentMelody.startPointer = melody;
        currentMelody.pos = 0;
        currentMelody.length = size / sizeof(int) / 3;
        currentMelody.phase = SoundTaskPhase::note;
        DEBUG_PRINTLN(currentMelody.toString());
    }
}
