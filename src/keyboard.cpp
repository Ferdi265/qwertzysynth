#include "app.hpp"

void Keyboard::hit(Note n, int octave, uint32_t t_sdl) {
    app->synth.hit(n >> octave, t_sdl);
    cur_note = n;
}

void Keyboard::release(Note n, int octave, uint32_t t_sdl) {
    app->synth.release(n >> octave, t_sdl);
    if (cur_note && *cur_note == n) {
        cur_note = std::nullopt;
    }
}

void Keyboard::render() {
    app->piano.render();
    app->accordeon.render();
}
