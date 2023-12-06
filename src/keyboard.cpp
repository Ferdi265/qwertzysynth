#include "app.hpp"

void Keyboard::hit(Note n, uint32_t t_sdl) {
    app->synth.hit(n, t_sdl);
    app->piano.hit(n);
    app->accordeon.hit(n);
}

void Keyboard::release(Note n, uint32_t t_sdl) {
    app->synth.release(n, t_sdl);
    app->piano.release(n);
    app->accordeon.release(n);
}

void Keyboard::render() {
    app->piano.render();
    app->accordeon.render();
}
