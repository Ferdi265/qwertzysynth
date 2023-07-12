#include <atomic>
#include "state.h"

constexpr static uint32_t SAMPLE_LENGTH = 256;
constexpr static uint32_t SAMPLE_RATE = 48000;
constexpr static uint32_t freq_sample_step(float freq, float rate) {
    return (SAMPLE_LENGTH / ((1 / freq) * rate)) * (1 << 16);
}
constexpr static uint32_t note_sample_step(note n, float rate) {
    return freq_sample_step(n.freq(), rate);
}

int16_t sample_triangle(uint8_t duty, uint8_t offset, int16_t volume) {
    if (offset < duty) return offset * (2*volume) / duty - volume;
    else return (SAMPLE_LENGTH - offset) * (2*volume) / (SAMPLE_LENGTH - duty) - volume;
}

constexpr static uint32_t sample_steps[] = {
    note_sample_step(A*2, SAMPLE_RATE),
    note_sample_step(A*3, SAMPLE_RATE),
    note_sample_step(C*3, SAMPLE_RATE),
    note_sample_step(C*4, SAMPLE_RATE)
};

struct beat_state {
    constexpr static uint32_t baseduty = 32;
    constexpr static uint32_t lfofreq = 1;
    constexpr static uint32_t lfosize = 32;
    constexpr static uint32_t volume = 64;

    uint32_t t = 0, t2 = 0;
    uint32_t fbase = 0;

    note cur_note = A*2;
    uint32_t ctr = 0, ctrstep = note_sample_step(A*2, SAMPLE_RATE);
    uint32_t lfo = 0;
    constexpr static uint32_t lfostep = freq_sample_step(lfofreq, SAMPLE_RATE);

    int8_t sample() {
        uint8_t duty = baseduty + sample_triangle(128, (uint8_t)(lfo >> 16), lfosize);
        int8_t sample = sample_triangle(duty, (uint8_t)(ctr >> 16), volume);
        return sample;
    }

    void update() {
        ctr += ctrstep;
        if (ctr > (SAMPLE_LENGTH << 16)) ctr -= SAMPLE_LENGTH << 16;
        lfo += lfostep;
        if (lfo > (SAMPLE_LENGTH << 16)) lfo -= SAMPLE_LENGTH << 16;

        if ((t2 & ((1 << 18) - 1)) == 0) { t = 0; if (t2 & (1 << 18)) {
            fbase = 2;
        } else {
            fbase = 0;
        } }
        if ((t & ((1 << 13) - 1)) == 0) { lfo = 0; ctr = 0;
            if ((t >> 13) % 3 != 2) {
                ctrstep = note_sample_step(cur_note, SAMPLE_RATE);
            } else {
                ctrstep = note_sample_step(cur_note>>1, SAMPLE_RATE);
            }
        }
        t++;
        t2++;
    }
};

std::atomic<note> cur_note = A*2;
bool fade_in = true;
beat_state bstate;

void synth_init() {

}

void synth_fini() {

}

void synth_note(note n) {
    cur_note = n;
}

void synth_update(std::span<int16_t> buffer) {
    bstate.cur_note = cur_note;

    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = (bstate.sample() * (1 << 7));
        bstate.update();

        if (fade_in) {
            buffer[i] *= ((float)i/buffer.size());
        }
    }

    fade_in = false;
}
