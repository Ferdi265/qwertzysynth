#pragma once

#include <climits>
#include <array>
#include <optional>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"
#include "cli.hpp"

struct KeyboardInput : non_copyable {
    KeyboardInput(CLIArgs args);
    ~KeyboardInput() = default;

    void update(SDL_Event e);

    std::array<std::optional<Note>, UCHAR_MAX + 1> note_mapping = {};
    int octave = 0;
};
