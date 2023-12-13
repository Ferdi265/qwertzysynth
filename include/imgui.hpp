#pragma once

#include <SDL.h>
#include "non_copyable.hpp"

struct Imgui : non_copyable {
    Imgui();
    ~Imgui();

    void frame();
    void update(SDL_Event e);
    void render();

    bool keyboard_captured();
};
