#include <SDL.h>
#include "util.hpp"
#include "app.hpp"
#include "cli.hpp"

App::App(CLIArgs args) :
    args(args)
{}

void App::run() {
    while (true) {
        app->imgui.frame();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            app->imgui.update(e);

            switch (e.type) {
                CASE(SDL_QUIT) {
                    return;
                }

                CASE(SDL_KEYDOWN) {
                    if (!app->imgui.keyboard_captured()) {
                        app->input.update(e);
                    }
                    break;
                }

                CASE(SDL_KEYUP) {
                    if (!app->imgui.keyboard_captured()) {
                        app->input.update(e);
                    }
                    break;
                }
            }
        }

        app->render.render();
    }
}
