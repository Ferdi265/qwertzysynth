#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"

#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;
constexpr static uint32_t SAMPLE_RATE = 48000;
constexpr static uint32_t BUF_SIZE = 1024;

Synth::Synth() {
    t_sdl_batch = SDL_GetTicks();
}

void Synth::hit(note n, uint32_t timestamp) {
    SynthEvent event = {
        event_time(timestamp), n, true
    };

    if (!events.push(event)) {
        fmt::print("error: failed to push synth hit event\n");
    }
}

void Synth::release(note n, uint32_t timestamp) {
    SynthEvent event = {
        event_time(timestamp), n, false
    };

    if (!events.push(event)) {
        fmt::print("error: failed to push synth release event\n");
    }
}

void Synth::update(std::span<int16_t> buffer) {
    t_sdl_batch = SDL_GetTicks();
    t_batch = t_sample;

    for (size_t i = 0; i < buffer.size(); i++, t_sample++) {
        process_events();
        buffer[i] = sample_instrument();
    }
}

// --- private ---

uint32_t Synth::event_time(uint32_t timestamp) const {
    uint32_t diff = timestamp - t_sdl_batch.load();
    uint32_t t = diff * SAMPLE_RATE / 1000;
    if (t >= BUF_SIZE) {
        fmt::print("warn: buffer exceeded by {} samples\n", t - BUF_SIZE - 1);
        t = BUF_SIZE - 1;
    }
    return t;
}

uint32_t Synth::hit_time() const {
    return t_hit == -1U ? -1U : t_sample - t_hit;
}

uint32_t Synth::release_time() const {
    return t_release == -1U ? -1U : t_sample - t_release;
}

void Synth::do_hit(note nt) {
    n = nt;
    t_hit = t_sample;
    t_release = -1U;
}

void Synth::do_release() {
    t_release = t_sample;
}

void Synth::do_off() {
    n = std::nullopt;
    t_hit = -1U;
    t_release = -1U;
}

void Synth::process_events() {
    while (true) {
        // get at least one event if no event pending
        if (!e) e = events.pop();

        // skip all release events for irrelevant notes
        while (e && !e->hit && e->n != n) {
            e = events.pop();
        }

        if (e && t_sample >= t_batch + e->t) {
            if (e->hit) {
                do_hit(e->n);
            } else {
                do_release();
            }

            // get another event
            e = std::nullopt;
            continue;
        }

        // current event will trigger later
        break;
    }
}

constexpr adsr vol_envelope = ADSR(BPM, SAMPLE_RATE, 1./32, 1./4, 3./4, 1.2, 1);
int16_t Synth::sample_instrument() {
    if (!n.has_value()) {
        return 0;
    }

    double level = vol_envelope.level(hit_time(), release_time());
    int16_t sample = triangle{ note_to_samples(*n, SAMPLE_RATE), 0, level }.level(hit_time()) * (1 << 12);

    if (vol_envelope.release_done(release_time())) {
        do_off();
    }

    return sample;
}
