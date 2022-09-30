#include <SDL.h>
#include <fmt/format.h>

constexpr static uint32_t WIDTH = 640;
constexpr static uint32_t HEIGHT = 480;

void update(SDL_Renderer * renderer, SDL_Texture * texture) {

    //SDL_UpdateTexture(texture, nullptr, framebuffer.data(), WIDTH);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    while (true) {
        SDL_Event e;
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT) {
            break;
        }

        update(renderer, texture);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
