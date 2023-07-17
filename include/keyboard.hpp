#pragma once

#include <climits>
#include <array>
#include <optional>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void update(SDL_Event e);

    static constinit std::array<std::optional<note>, UCHAR_MAX + 1> note_mapping;
    int octave = 0;
};
