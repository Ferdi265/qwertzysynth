#include <SDL.h>
#include "non_copyable.hpp"

struct Render : non_copyable {
    Render();
    ~Render();

    void render();

    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
};
