#include <SDL_keycode.h>
#include <fmt/format.h>
#include "app.hpp"
#include "util.hpp"

constexpr bool QWERTUOSO = true;
constinit std::array<std::optional<note>, UCHAR_MAX + 1> Keyboard::note_mapping = []{
    std::array<std::optional<note>, UCHAR_MAX + 1> note_mapping = {};

    if (QWERTUOSO) {
        // Qwertuoso
        note_mapping['1'] = C*2;
        note_mapping['2'] = Dis*2;
        note_mapping['3'] = Fis*2;
        note_mapping['4'] = A*2;
        note_mapping['5'] = C*3;
        note_mapping['6'] = Dis*3;
        note_mapping['7'] = Fis*3;
        note_mapping['8'] = A*3;
        note_mapping['9'] = C*4;
        note_mapping['0'] = Dis*4;
        note_mapping[0xdf /* ß */] = Fis*4;

        note_mapping['q'] = Cis*2;
        note_mapping['w'] = E*2;
        note_mapping['e'] = G*2;
        note_mapping['r'] = Ais*2;
        note_mapping['t'] = Cis*3;
        note_mapping['z'] = E*3;
        note_mapping['u'] = G*3;
        note_mapping['i'] = Ais*3;
        note_mapping['o'] = Cis*4;
        note_mapping['p'] = E*4;
        note_mapping[0xfc /* 'ü' */] = G*4;
        note_mapping['+'] = Ais*4;

        note_mapping['a'] = D*2;
        note_mapping['s'] = F*2;
        note_mapping['d'] = Gis*2;
        note_mapping['f'] = B*2;
        note_mapping['g'] = D*3;
        note_mapping['h'] = F*3;
        note_mapping['j'] = Gis*3;
        note_mapping['k'] = B*3;
        note_mapping['l'] = D*4;
        note_mapping[0xf6 /* 'ö' */] = F*4;
        note_mapping[0xe4 /* 'ä' */] = Gis*4;
        note_mapping['#'] = B*4;

        note_mapping['y'] = Dis*2;
        note_mapping['x'] = Fis*2;
        note_mapping['c'] = A*2;
        note_mapping['v'] = C*3;
        note_mapping['b'] = Dis*3;
        note_mapping['n'] = Fis*3;
        note_mapping['m'] = A*3;
        note_mapping[','] = C*4;
        note_mapping['.'] = Dis*4;
        note_mapping['-'] = Fis*4;
    } else {
        note_mapping['q'] = C*4;
        note_mapping['2'] = Cis*4;
        note_mapping['w'] = D*4;
        note_mapping['3'] = Dis*4;
        note_mapping['e'] = E*4;
        note_mapping['r'] = F*4;
        note_mapping['5'] = Fis*4;
        note_mapping['t'] = G*4;
        note_mapping['6'] = Gis*4;
        note_mapping['z'] = A*4;
        note_mapping['7'] = Ais*4;
        note_mapping['u'] = B*4;
        note_mapping['i'] = C*5;
        note_mapping['9'] = Cis*5;
        note_mapping['o'] = D*5;
        note_mapping['0'] = Dis*5;
        note_mapping['p'] = E*5;

        note_mapping['y'] = C*3;
        note_mapping['s'] = Cis*3;
        note_mapping['x'] = D*3;
        note_mapping['d'] = Dis*3;
        note_mapping['c'] = E*3;
        note_mapping['v'] = F*3;
        note_mapping['g'] = Fis*3;
        note_mapping['b'] = G*3;
        note_mapping['h'] = Gis*3;
        note_mapping['n'] = A*3;
        note_mapping['j'] = Ais*3;
        note_mapping['m'] = B*3;
        note_mapping[','] = C*4;
        note_mapping['l'] = Cis*4;
        note_mapping['.'] = D*4;
        note_mapping[0xf6 /* ö */] = Dis*4;
        note_mapping['-'] = E*4;
    }

    return note_mapping;
}();

void Keyboard::update(SDL_Event e) {
    switch (e.type) {
        CASE(SDL_KEYDOWN) {
            int keysym = e.key.keysym.sym;
            if (e.key.repeat) {
                // ignore key repeats
                return;
            }

            std::optional<note> keynote = (size_t)keysym < note_mapping.size() ? note_mapping[(size_t)keysym] : std::nullopt;
            if (keynote) {
                app->synth.hit(*keynote >> octave, e.key.timestamp);
            } else {
                switch (keysym) {
                    CASE(SDLK_KP_PLUS) {
                        int new_octave = ++octave;
                        fmt::print("octave: {}\n", new_octave);
                        break;
                    }
                    CASE(SDLK_KP_MINUS) {
                        int new_octave = --octave;
                        fmt::print("octave: {}\n", new_octave);
                        break;
                    }
                    DEFAULT() {
                        fmt::print("key down: 0x{:x}\n", keysym);
                    }
                }
            }
            break;
        }
        CASE(SDL_KEYUP) {
            int keysym = e.key.keysym.sym;

            std::optional<note> keynote = (size_t)keysym < note_mapping.size() ? note_mapping[(size_t)keysym] : std::nullopt;
            if (keynote) {
                app->synth.release(*keynote >> octave, e.key.timestamp);
            } else {
                switch (keysym) {
                    DEFAULT() {
                        //fmt::print("key up: 0x{:x}\n", keysym);
                    }
                }
            }
            break;
        }
    }
}
