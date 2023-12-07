#include <cstdint>
#include <fmt/format.h>

#include "app.hpp"
#include "util.hpp"

#include "libsynth.hpp"

constexpr static uint32_t BPM = 120;

// --- Synth public ---

Synth::Synth() {
    t_batch = { 0, SDL_GetTicks() };
}

void Synth::hit(Note n, uint32_t t_sdl) {
    SynthEvent e = { event_time(t_sdl), n, true };
    warn_on(!events.push(e), "failed to push {} event\n", e);
}

void Synth::release(Note n, uint32_t t_sdl) {
    SynthEvent e = { event_time(t_sdl), n, false };
    warn_on(!events.push(e), "failed to push {} event\n", e);
}

void Synth::update(std::span<int16_t> buffer) {
    t_batch = { t_sample, SDL_GetTicks() };

    for (size_t i = 0; i < buffer.size(); ) {
        size_t max = i + time_until_event(buffer.size() - i);
        for (; i < max; i++, t_sample++) {
            buffer[i] = sample();
        }
        handle_event();
    }
}

// --- Synth private ---

uint32_t Synth::event_time(uint32_t t_sdl) const {
    SynthTime base = t_batch.load();
    int32_t t_sdl_diff = t_sdl - base.t_sdl;
    int32_t t_diff = t_sdl_diff * int32_t(SAMPLE_RATE) / 1000;
    // place all events one buffer size in the future to ensure correct timing
    int32_t t = base.t + BUF_SIZE + t_diff;
    warn_on(t_sdl_diff < 0, "calculating sample timing for event in the past, base.t = {}, t = {}\n",
        base.t, t
    );
    return t;
}

void Synth::hit() {
    SynthTrack* hit_track = &tracks[0];
    for (SynthTrack& track : tracks) {
        if (track.n == e->n || !track.n) {
            hit_track = &track;
            break;
        } else if (track.t_hit <= hit_track->t_hit) {
            hit_track = &track;
        }
    }

    hit_track->hit(t_sample, e->n);
}

void Synth::release() {
    for (SynthTrack& track : tracks) {
        if (track.n == e->n) {
            track.release(t_sample);
        }
    }
}

size_t Synth::time_until_event(size_t rest) {
    if (!e) {
        // get next event
        e = events.pop();
    }

    if (!e) {
        // no event, skip until end of buffer
        return rest;
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
        fmt::print("info: {}\n", *e);
        warn_on(diff < 0, "event handled {} samples too late\n", -diff);

        if (e->hit) {
            hit();
        } else {
            release();
        }

        e = std::nullopt;
    }
}

int16_t Synth::sample() {
    int16_t s = 0;
    for (SynthTrack& track : tracks) {
        s += track.sample(t_sample, app->args.transpose);
    }

    return s;
}

// --- SynthTrack ---

void SynthTrack::hit(uint32_t t, Note nt) {
    n = nt;
    t_hit = t;
    t_release = -1U;
}

void SynthTrack::release(uint32_t t) {
    t_release = t;
}

void SynthTrack::off() {
    n = std::nullopt;
    t_hit = -1U;
    t_release = -1U;
}

uint32_t SynthTrack::hit_time(uint32_t t) const {
    return t_hit == -1U ? -1U : t - t_hit;
}

uint32_t SynthTrack::release_time(uint32_t t) const {
    return t_release == -1U ? -1U : t - t_release;
}

constexpr adsr vol_envelope = ADSR(BPM, SAMPLE_RATE, 1./32, 1./4, 3./4, 1.2, 1);
int16_t SynthTrack::sample(uint32_t t, int transpose) {
    if (!n.has_value()) {
        return 0;
    }

    double level = vol_envelope.level(hit_time(t), release_time(t));
    int16_t sample = triangle{ note_to_samples(*n + transpose, SAMPLE_RATE), 0.2, level }.level(hit_time(t)) * (1 << 12);

    if (vol_envelope.release_done(release_time(t))) {
        off();
    }

    return sample;
}
