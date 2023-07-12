#include <cstdint>
#include "state.h"

constexpr static uint32_t WIDTH = 640;
constexpr static uint32_t HEIGHT = 480;

void render_init() {
    state.window = SDL_CreateWindow("Music", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

void render_fini() {
    SDL_DestroyTexture(state.texture);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
}

void render_update() {
    //SDL_UpdateTexture(texture, nullptr, framebuffer.data(), WIDTH);

    SDL_RenderCopy(state.renderer, state.texture, nullptr, nullptr);
    SDL_RenderPresent(state.renderer);
}
