#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <atomic>
#include <chrono>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"
#include "lockfree-ring-queue.hpp"

struct SynthEvent {
    uint32_t t;
    note n;
    bool hit;
};

struct Synth : non_copyable {
    Synth();
    ~Synth() = default;

    void hit(note n);
    void release(note n);
    void update(std::span<int16_t> buffer);

    uint32_t event_time();
    void process_events();
    int16_t sample_instrument(uint32_t t);

    lockfree_ring_queue<SynthEvent, 32> events;
    std::atomic<std::chrono::steady_clock::time_point> t_batch;

    uint32_t t_batch_begin = 0;
    uint32_t t_sample = 0;
    uint32_t t_hit = -1U;
    uint32_t t_release = -1U;
    std::optional<note> n;
    std::optional<SynthEvent> e;
};
