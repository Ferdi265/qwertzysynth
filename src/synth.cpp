#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"

#include "lockfree-ring-queue.hpp"
#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;
constexpr static uint32_t SAMPLE_RATE = 48000;

Synth::Synth() {
    t_batch = SDL_GetTicks();
}

uint32_t Synth::event_time(uint32_t timestamp) {
    std::chrono::milliseconds t_diff = std::chrono::milliseconds(timestamp - t_batch.load());
    assert(t_diff.count() >= 0);
    uint32_t t = std::chrono::duration_cast<std::chrono::nanoseconds>(t_diff).count() * SAMPLE_RATE / 1'000'000;
    return t;
}

// TODO: use key event timestamp
void Synth::hit(note n, uint32_t timestamp) {
    SynthEvent event = {
        event_time(timestamp), n, true
    };

    if (!events.push(event)) {
        fmt::print("error: failed to push synth hit event\n");
    }
}

// TODO: use key event timestamp
void Synth::release(note n, uint32_t timestamp) {
    SynthEvent event = {
        event_time(timestamp), n, false
    };

    if (!events.push(event)) {
        fmt::print("error: failed to push synth release event\n");
    }
}

void Synth::process_events() {
    while (true) {
        // get at least one event if no event pending
        if (!e) e = events.pop();

        // skip all release events for irrelevant notes
        while (e && !e->hit && e->n != n) {
            e = events.pop();
        }

        if (e && t_batch_begin + e->t >= t_sample) {
            if (e->hit) {
                // new note hit
                t_hit = t_sample;
                t_release = -1U;
                n = e->n;
            } else {
                // current note released
                t_release = t_sample;
            }

            // get another event
            e = std::nullopt;
            continue;
        }

        // current event will trigger later
        break;
    }
}

constexpr adsr vol_envelope = adsr{ 10, 10, 10, 1, 1 };
int16_t Synth::sample_instrument(uint32_t t) {
    if (!n.has_value()) {
        return 0;
    }

    double level = 0;
    if (!app->synth.n.has_value()) {
        return level;
    } else if (app->synth.t_release == -1U) {
        level = vol_envelope.level(t - t_hit, false);
    } else {
        level = vol_envelope.level(t - t_release, true);
    }

    return triangle{ note_to_samples(*n, SAMPLE_RATE), 0, level }.level(t - t_hit) * (1 << 12);
}

void Synth::update(std::span<int16_t> buffer) {
    t_batch = SDL_GetTicks();
    t_batch_begin = t_sample;

    for (size_t i = 0; i < buffer.size(); i++) {
        process_events();
        buffer[i] = sample_instrument(t_sample++);
    }
}
