#pragma once

#include "non_copyable.hpp"
#include "note.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void hit(Note n, uint32_t t_sdl);
    void release(Note n, uint32_t t_sdl);
    void render();
};
