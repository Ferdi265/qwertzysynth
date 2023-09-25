#include <SDL.h>
#include "util.hpp"
#include "app.hpp"
#include "scope_guard.hpp"
#include "cli.hpp"

App::App(CLIArgs args) :
    render(),
    imgui(),
    audio(),
    keyboard(args),
    synth(args)
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
                    app->keyboard.update(e);
                    break;
                }

                CASE(SDL_KEYUP) {
                    app->keyboard.update(e);
                    break;
                }
            }
        }

        app->render.render();
    }
}

int main(int argc, char ** argv) {
    CLIArgs args = parse_args(argc, argv);

    scope_guard sdl_guard{ []{ SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); }, SDL_Quit };
    scope_guard app_guard{ [&]{ app.construct(args); }, []{ app.destruct(); } };

    app->run();
}
