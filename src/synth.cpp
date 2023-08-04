#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"
#include "util.hpp"

#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;

Synth::Synth() {
    t_batch = { 0, SDL_GetTicks() };
}

void Synth::hit(note n, uint32_t t_sdl) {
    warn_on(!events.push({ event_time(t_sdl), n, true }), "failed to push synth hit event\n");
}

void Synth::release(note n, uint32_t t_sdl) {
    warn_on(!events.push({ event_time(t_sdl), n, false }), "failed to push synth release event\n");
}

void Synth::update(std::span<int16_t> buffer) {
    t_batch = { t_sample, SDL_GetTicks() };

    for (size_t i = 0; i < buffer.size(); ) {
        size_t max = i + time_until_event(buffer.size() - i);
        for (; i < max; i++, t_sample++) {
            buffer[i] = sample_instrument();
        }
        handle_event();
    }
}

// --- private ---

uint32_t Synth::event_time(uint32_t t_sdl) const {
    SynthTime base = t_batch.load();
    uint32_t t_sdl_diff = t_sdl - base.t_sdl;
    uint32_t t_diff = t_sdl_diff * SAMPLE_RATE / 1000;
    // place all events one buffer size in the future to ensure correct timing
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

size_t Synth::time_until_event(size_t rest) {
    if (!e) {
        // get next event
        e = events.pop();
    }

    if (!e) {
        // no event, skip until end of buffer
        return rest;
    } else if (!e->hit && e->n != n) {
        // skip release events for irrelevant notes
        e = std::nullopt;
        return 0;
    } else {
        // handle events in the past now
        // handle events in the future in n samples
        // handle events not in this buffer later
        int32_t diff = e->t - t_sample;
        return std::clamp<int32_t>(diff, 0, rest);
    }
}

void Synth::handle_event() {
    if (!e) {
        return;
    }

    int32_t diff = e->t - t_sample;
    if (diff <= 0) {
        warn_on(diff < 0, "event handled {} samples too late\n", -diff);

        if (e->hit) {
            do_hit(e->n);
        } else {
            do_release();
        }

        e = std::nullopt;
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
