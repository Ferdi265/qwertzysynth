#include <fmt/format.h>
#include "app.hpp"
#include "util.hpp"

constinit std::array<std::optional<note>, CHAR_MAX + 1> Keyboard::note_mapping = []{
    std::array<std::optional<note>, CHAR_MAX + 1> note_mapping = {};

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

    return note_mapping;
}();

void Keyboard::update(SDL_Event e) {
    switch (e.type) {
        CASE(SDL_KEYDOWN) {
            int keysym = e.key.keysym.sym;

            std::optional<note> keynote = (size_t)keysym < note_mapping.size() ? note_mapping[(size_t)keysym] : std::nullopt;
            if (keynote) {
                app->synth.hit(*keynote >> octave, e.key.timestamp);
            } else {
                switch (keysym) {
                    CASE('+') {
                        int new_octave = ++octave;
                        fmt::print("octave: {}\n", new_octave);
                        break;
                    }
                    CASE('-') {
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
                    CASE('+') {
                        break;
                    }
                    CASE('-') {
                        break;
                    }
                    DEFAULT() {
                        fmt::print("key up: 0x{:x}\n", keysym);
                    }
                }
            }
            break;
        }
    }
}
