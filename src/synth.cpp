#include <atomic>
#include "state.h"
#include "synth.h"

constexpr static uint32_t BPM = 120;
constexpr static uint32_t SAMPLE_RATE = 48000;

struct Synth {
    uint32_t t;
    uint32_t t_hit = -1U;
    uint32_t t_release = -1U;
    note cur_note = C*4;
};

Synth synth;

void synth_init() {
}

void synth_fini() {

}

void synth_note(note n) {
    synth.cur_note = n;
    synth.t_hit = synth.t;
    synth.t_release = -1U;
}

void synth_release(note n) {
    if (synth.cur_note.n == n.n) {
        synth.t_release = synth.t;
    }
}

constexpr adsr vol_envelope = adsr{ 10, 10, 10, 1, 1 }; //ADSR(BPM, SAMPLE_RATE, 0, 0, 0, 1, 1);
int16_t synth_test() {
    uint32_t t = synth.t++;

    double level = 0;
    if (synth.t_hit == -1U) {
        return level;
    } else if (synth.t_release == -1U) {
        level = vol_envelope.level(t - synth.t_hit, false);
    } else {
        level = vol_envelope.level(t - synth.t_release, true);
    }

    return triangle{ note_to_samples(synth.cur_note, SAMPLE_RATE), 0, level }.level(t - synth.t_hit) * (1 << 12);
}

void synth_update(std::span<int16_t> buffer) {
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = synth_test();
    }
}
