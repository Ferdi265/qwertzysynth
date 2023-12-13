#pragma once

#include <SDL.h>
#include "non_copyable.hpp"

struct Input : non_copyable {
    Input() = default;
    ~Input() = default;

    void update(SDL_Event e);
};
