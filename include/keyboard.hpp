#pragma once

#include <climits>
#include <array>
#include <optional>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"
#include "cli.hpp"

struct Keyboard : non_copyable {
    Keyboard(CLIArgs args);
    ~Keyboard() = default;

    void update(SDL_Event e);

    std::array<std::optional<Note>, UCHAR_MAX + 1> note_mapping = {};
    int octave = 0;
};
