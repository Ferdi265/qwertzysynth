#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <atomic>
#include <chrono>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"
#include "lockfree_ring_queue.hpp"

struct SynthTime {
    uint32_t t;
    uint32_t t_sdl;
};

struct SynthEvent {
    uint32_t t;
    note n;
    bool hit;
};

struct Synth : non_copyable {
    Synth();
    ~Synth() = default;

    void hit(note n, uint32_t t_sdl);
    void release(note n, uint32_t t_sdl);
    void update(std::span<int16_t> buffer);

private:
    uint32_t event_time(uint32_t t_sdl) const;
    uint32_t hit_time() const;
    uint32_t release_time() const;

    void do_hit(note nt);
    void do_release();
    void do_off();
    size_t process_events(size_t rest);
    int16_t sample_instrument();

    lockfree_ring_queue<SynthEvent, 32> events;
    std::atomic<SynthTime> t_batch;

    uint32_t t_sample = 0;
    uint32_t t_hit = -1U;
    uint32_t t_release = -1U;
    std::optional<note> n;
    std::optional<SynthEvent> e;
};
