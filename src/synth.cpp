#include <cstdint>

#include "app.hpp"

#include "lockfree-ring-queue.hpp"
#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;
constexpr static uint32_t SAMPLE_RATE = 48000;

Synth::Synth() {
}

void Synth::hit(note n) {
    cur_note = n;
    t_hit = t;
    t_release = -1U;
}

void Synth::release(note n) {
    if (cur_note.n == n.n) {
        t_release = t;
    }
}

constexpr adsr vol_envelope = adsr{ 10, 10, 10, 1, 1 };
static int16_t synth_test() {
    uint32_t t = app->synth.t++;

    double level = 0;
    if (app->synth.t_hit == -1U) {
        return level;
    } else if (app->synth.t_release == -1U) {
        level = vol_envelope.level(t - app->synth.t_hit, false);
    } else {
        level = vol_envelope.level(t - app->synth.t_release, true);
    }

    return triangle{ note_to_samples(app->synth.cur_note, SAMPLE_RATE), 0, 1 }.level(t - app->synth.t_hit) * level * (1 << 12);
}

void Synth::update(std::span<int16_t> buffer) {
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = synth_test();
    }
}
