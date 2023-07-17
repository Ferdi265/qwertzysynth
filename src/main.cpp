#include <SDL.h>
#include "util.hpp"
#include "app.hpp"
#include "scope_guard.hpp"

App::App() {

}

void App::run() {
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                CASE(SDL_QUIT) {
                    return;
                }

                CASE(SDL_KEYDOWN) {
                    app->keyboard.update(e);
                    break;
                }

                CASE(SDL_KEYUP) {
                    app->keyboard.update(e);
                    break;
                }
            }
        }

        app->render.update();
    }
}

int main() {
    scope_guard<[]{ SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); }, SDL_Quit> sdl_guard;
    scope_guard<[]{ app.construct(); }, []{ app.destruct(); }> app_guard;

    app->run();
}
