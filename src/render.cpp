#include "render.hpp"
#include "app.hpp"

Render::Render() {
    window = SDL_CreateWindow("QwertzySynth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

Render::~Render() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Render::render() {
    //SDL_UpdateTexture(texture, nullptr, framebuffer.data(), WIDTH);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    app->imgui.render();
    SDL_RenderPresent(renderer);
}
