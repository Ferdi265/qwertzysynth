#include <SDL.h>
#include "state.h"
#include "scope_guard.h"

void run() {
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                CASE(SDL_QUIT) {
                    return;
                }

                CASE(SDL_KEYDOWN) {
                    keyboard_update(e);
                    break;
                }

                CASE(SDL_KEYUP) {
                    keyboard_update(e);
                    break;
                }
            }
        }

        render_update();
    }
}

int main() {
    scope_guard<[]{ SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); }, SDL_Quit> sdl;
    scope_guard<render_init, render_fini> render;
    scope_guard<audio_init, audio_fini> audio;
    scope_guard<keyboard_init, keyboard_fini> keyboard;
    scope_guard<synth_init, synth_fini> synth;

    run();
}
