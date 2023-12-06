#pragma once

#include <optional>
#include "non_copyable.hpp"
#include "note.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void hit(Note n, int octave, uint32_t t_sdl);
    void release(Note n, int octave, uint32_t t_sdl);
    void render();

    static constexpr int MIN_KEY = (C*3).n;
    static constexpr int NUM_KEYS = 12 * 3;
    std::optional<Note> cur_note;
};
