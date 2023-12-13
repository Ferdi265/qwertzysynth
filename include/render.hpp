#pragma once

#include <cstdint>
#include <SDL.h>
#include "non_copyable.hpp"

constexpr static uint32_t WIDTH = 640;
constexpr static uint32_t HEIGHT = 480;

struct Render : non_copyable {
    Render();
    ~Render();

    void render();

    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
};
