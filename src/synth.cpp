#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"

#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;

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

    for (size_t i = 0; i < buffer.size(); ) {
        size_t max = i + process_events(buffer.size() - i);
        for (; i < max; i++, t_sample++) {
            buffer[i] = sample_instrument();
        }
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

size_t Synth::process_events(size_t rest) {
    if (e) {
        assert(t_batch + e->t >= t_sample && "event handled too early");
        assert(t_batch + e->t <= t_sample && "event handled too late");
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
    } else if (t_batch + e->t <= t_sample) {
        // event is now, handle immediately
        assert(t_batch + e->t == t_sample && "event is in the past");
        return 0;
    } else {
        // event is in the future, handle in n samples
        assert(t_batch + e->t - t_sample <= rest && "t is past end of buffer");
        return t_batch + e->t - t_sample;
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
