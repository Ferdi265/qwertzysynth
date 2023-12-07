#include "app.hpp"

void Keyboard::hit_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        hit(*n, octave, t_sdl);
    } else if (keysym == SDLK_KP_PLUS) {
        octave++;
        fmt::print("octave: {}\n", octave);
    } else if (keysym == SDLK_KP_MINUS) {
        octave--;
        fmt::print("octave: {}\n", octave);
    } else {
        fmt::print("hit: {:x}\n", keysym);
    }
}

void Keyboard::release_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        release(*n, octave, t_sdl);
    } else {
        fmt::print("release: {:x}\n", keysym);
    }
}

void Keyboard::render() {
    app->piano.render();
    app->accordeon.render();
}

std::optional<Note> Keyboard::map_key(int keysym) {
    std::optional<Note> n;
    switch (app->args.kb_layout) {
        case KeyboardLayout::Piano:
            n = app->piano.map_key(keysym);
            break;
        case KeyboardLayout::Qwertuoso:
            n = app->accordeon.map_key(keysym);
            break;
        case KeyboardLayout::CGriff:
            fmt::print("error: CGriff not supported\n");
            break;
        default:
            fmt::print("error: invalid keyboard layout\n");
            break;
    }

    return n;
}

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

