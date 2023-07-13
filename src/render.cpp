#include <cstdint>
#include "app.hpp"

constexpr static uint32_t WIDTH = 640;
constexpr static uint32_t HEIGHT = 480;

Render::Render() {
    window = SDL_CreateWindow("Music", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

Render::~Render() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Render::update() {
    //SDL_UpdateTexture(texture, nullptr, framebuffer.data(), WIDTH);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
