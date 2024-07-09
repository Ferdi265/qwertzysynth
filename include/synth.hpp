#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <atomic>
#include "lockfree_ring_queue.hpp"
#include "non_copyable.hpp"
#include "note.hpp"

struct SynthTime {
    uint32_t t;
    uint32_t t_sdl;
};

struct SynthEvent {
    uint32_t t;
    Note n;
    bool hit;
    HitType type;

    constexpr friend auto operator<=>(SynthEvent, SynthEvent) = default;
};

template <>
struct fmt::formatter<SynthEvent> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const SynthEvent& e, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "{} {} @ {}",
            e.hit ? "hit" : "rel",
            e.n,
            e.t
        );
    }
};

struct SynthTrack {
    uint32_t t_hit = -1U;
    uint32_t t_release = -1U;
    std::optional<Note> n;
    HitType type;

    uint32_t hit_time(uint32_t t) const;
    uint32_t release_time(uint32_t t) const;

    void hit(uint32_t t, Note nt, HitType type);
    void release(uint32_t t);
    void off();

    int16_t sample_raw(Note n, uint32_t t);
    int16_t sample_centered(Note n, uint32_t t);
    int16_t sample_padme(Note n, uint32_t t);
    int16_t sample_padme_fifth(Note n, uint32_t t);
    int16_t sample_padme_third(Note n, uint32_t t);
    int16_t sample(uint32_t t, int transpose);
};

struct Synth : non_copyable {
    Synth();
    ~Synth() = default;

    void hit(Note n, HitType type, uint32_t t_sdl);
    void release(Note n, HitType type, uint32_t t_sdl);
    void update(std::span<int16_t> buffer);

private:
    uint32_t event_time(uint32_t t_sdl) const;

    void hit();
    void release();

    size_t time_until_event(size_t rest);
    void handle_event();
    int16_t sample();

    lockfree_ring_queue<SynthEvent, 32> events;
    std::atomic<SynthTime> t_batch;
    static_assert(std::atomic<SynthTime>::is_always_lock_free, "accessing t_batch is not lock free");

    uint32_t t_sample = 0;
    std::optional<SynthEvent> e;
    std::array<SynthTrack, 2> tracks;
};
