#pragma once

#include <climits>
#include <array>
#include <optional>
#include <SDL.h>
#include "non_copyable.hpp"
#include "note.hpp"
#include "cli.hpp"

struct Input : non_copyable {
    Input() = default;
    ~Input() = default;

    void update(SDL_Event e);
};
