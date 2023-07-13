#pragma once

#include <SDL.h>
#include "non_copyable.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void update(SDL_Event e);

    int octave;
};
