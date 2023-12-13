#include <SDL.h>
#include "scope_guard.hpp"
#include "cli.hpp"
#include "app.hpp"

int main(int argc, char ** argv) {
    CLIArgs args = parse_args(argc, argv);

    SCOPE_GUARD(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER), SDL_Quit());
    SCOPE_GUARD(app.construct(args), app.destruct());

    app->run();
}
