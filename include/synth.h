#pragma once

#include <cstdint>
#include "note.h"

constexpr uint32_t bpm_to_samples(uint32_t bpm, uint32_t sample_rate) {
    return 60. / bpm * sample_rate;
}

constexpr uint32_t freq_to_samples(double freq, uint32_t sample_rate) {
    return sample_rate / freq;
}

constexpr uint32_t note_to_samples(note n, uint32_t sample_rate) {
    return freq_to_samples(n.freq(), sample_rate);
}

struct val {
    uint32_t t;
    double v;
};

constexpr double lerp(val a, val b, uint32_t t) {
    return (b.v - a.v) * (t - a.t) / (b.t - a.t);
}

struct adsr {
    uint32_t attack_time;
    uint32_t decay_time;
    uint32_t release_time;
    double attack_level;
    double sustain_level;

    constexpr double level(uint32_t t, bool release) const {
        if (!release) {
            if (t < attack_time) {
                return lerp({ 0, 0 }, { attack_time, attack_level }, t);
            } else if (t < decay_time) {
                return lerp({ attack_time, attack_level }, { decay_time, sustain_level }, t);
            } else {
                return sustain_level;
            }
        } else {
            if (t < release_time) {
                return lerp({ 0, sustain_level }, { release_time, 0 }, t);
            } else {
                return 0;
            }
        }
    }
};
constexpr adsr ADSR(uint32_t bpm, uint32_t sample_rate, double a, double d, double r, double al, double sl) {
    uint32_t bpm_smp = bpm_to_samples(bpm, sample_rate);
    return adsr{
        uint32_t(bpm_smp * a),
        uint32_t(bpm_smp * d),
        uint32_t(bpm_smp * r),
        al,
        sl
    };
}

struct triangle {
    uint32_t period;
    double duty;
    double volume;

    constexpr double level(uint32_t t) const {
        t = (t + uint32_t(duty*period/2)) % period; // start triangle at zero-point
        if (t < duty*period) {
            return lerp({ 0, -volume }, { uint32_t(duty*period), volume }, t);
        } else {
            return lerp({ uint32_t(duty*period), volume }, { period, -volume }, t);
        }
    }
};
