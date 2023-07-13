#pragma once

#include <cstdint>
#include <span>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"

struct Synth : non_copyable {
    Synth();
    ~Synth() = default;

    void hit(note n);
    void release(note n);
    void update(std::span<int16_t> buffer);

    uint32_t t;
    uint32_t t_hit = -1U;
    uint32_t t_release = -1U;
    note cur_note = C*4;
};
