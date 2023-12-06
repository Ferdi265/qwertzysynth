#include "app.hpp"

void Keyboard::hit(Note n, int octave, uint32_t t_sdl) {
    app->synth.hit(n >> octave, t_sdl);
    app->piano.hit(n);
    app->accordeon.hit(n);
}

void Keyboard::release(Note n, int octave, uint32_t t_sdl) {
    app->synth.release(n >> octave, t_sdl);
    app->piano.release(n);
    app->accordeon.release(n);
}

void Keyboard::render() {
    app->piano.render();
    app->accordeon.render();
}
