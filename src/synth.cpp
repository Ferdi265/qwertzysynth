#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"
#include "util.hpp"

#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;

Synth::Synth() {
    t_batch = { 0, SDL_GetTicks() };
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
    t_batch = { t_sample, SDL_GetTicks() };

    for (size_t i = 0; i < buffer.size(); ) {
        size_t max = i + process_events(buffer.size() - i);
        for (; i < max; i++, t_sample++) {
            buffer[i] = sample_instrument();
        }
    }
}

// --- private ---

uint32_t Synth::event_time(uint32_t t_sdl) const {
    SynthTime base = t_batch.load();
    uint32_t t_sdl_diff = t_sdl - base.t_sdl;
    uint32_t t_diff = t_sdl_diff * SAMPLE_RATE / 1000;
    // place all events one sample buffer in the future
    return t_diff + base.t + BUF_SIZE;
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

size_t Synth::process_events(size_t rest) {
    if (e) {
        warn_on(e->t < t_sample, "event handled {} samples too early\n", t_sample - e->t);
        warn_on(e->t > t_sample, "event handled {} samples too late\n", e->t - t_sample);
        if (e->hit) {
            do_hit(e->n);
        } else {
            do_release();
        }
    }

    // get next event
    e = events.pop();
    if (!e) {
        // no event, skip until end of buffer
        return rest;
    } else if (!e->hit && e->n != n) {
        // skip release events for irrelevant notes
        e = std::nullopt;
        return 0;
    } else if (e->t <= t_sample) {
        // event is now, handle immediately
        warn_on(e->t < t_sample, "event is {} samples in the past\n", t_sample - e->t);
        return 0;
    } else if (e->t - t_sample <= rest) {
        // event is in the future, handle in n samples
        return e->t - t_sample;
    } else {
        // event is not in this buffer, handle next audio buffer
        return rest;
    }
}

constexpr adsr vol_envelope = ADSR(BPM, SAMPLE_RATE, 1./32, 1./4, 3./4, 1.2, 1);
int16_t Synth::sample_instrument() {
    if (!n.has_value()) {
        return 0;
    }

    double level = vol_envelope.level(hit_time(), release_time());
    int16_t sample = triangle{ note_to_samples(*n, SAMPLE_RATE), 0.2, level }.level(hit_time()) * (1 << 12);

    if (vol_envelope.release_done(release_time())) {
        do_off();
    }

    return sample;
}
