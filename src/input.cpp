#include <SDL_keycode.h>
#include <fmt/format.h>
#include "app.hpp"
#include "cli.hpp"
#include "util.hpp"

Input::Input(CLIArgs args) {
    if (args.kb_layout == KeyboardLayout::Piano) {
        note_mapping['2'] = Cis*4;
        note_mapping['3'] = Dis*4;
        note_mapping['5'] = Fis*4;
        note_mapping['6'] = Gis*4;
        note_mapping['7'] = Ais*4;
        note_mapping['9'] = Cis*5;
        note_mapping['0'] = Dis*5;

        note_mapping['q'] = C*4;
        note_mapping['w'] = D*4;
        note_mapping['e'] = E*4;
        note_mapping['r'] = F*4;
        note_mapping['t'] = G*4;
        note_mapping['z'] = A*4;
        note_mapping['u'] = B*4;
        note_mapping['i'] = C*5;
        note_mapping['o'] = D*5;
        note_mapping['p'] = E*5;
        note_mapping[0xfc /* 'ü' */] = F*5;
        note_mapping['+'] = G*5;

        note_mapping['s'] = Cis*3;
        note_mapping['d'] = Dis*3;
        note_mapping['g'] = Fis*3;
        note_mapping['h'] = Gis*3;
        note_mapping['j'] = Ais*3;
        note_mapping['l'] = Cis*4;
        note_mapping[0xf6 /* ö */] = Dis*4;
        note_mapping['#'] = Fis*4;

        note_mapping['<'] = B*2;
        note_mapping['y'] = C*3;
        note_mapping['x'] = D*3;
        note_mapping['c'] = E*3;
        note_mapping['v'] = F*3;
        note_mapping['b'] = G*3;
        note_mapping['n'] = A*3;
        note_mapping['m'] = B*3;
        note_mapping[','] = C*4;
        note_mapping['.'] = D*4;
        note_mapping['-'] = E*4;
    } else if (args.kb_layout == KeyboardLayout::CGriff) {
        fmt::print("TODO: implement CGriff\n");
    } else if (args.kb_layout == KeyboardLayout::BGriff) {
        // Qwertuoso
        note_mapping['1'] = C*3;
        note_mapping['2'] = Dis*3;
        note_mapping['3'] = Fis*3;
        note_mapping['4'] = A*3;
        note_mapping['5'] = C*4;
        note_mapping['6'] = Dis*4;
        note_mapping['7'] = Fis*4;
        note_mapping['8'] = A*4;
        note_mapping['9'] = C*5;
        note_mapping['0'] = Dis*5;
        note_mapping[0xdf /* ß */] = Fis*5;

        note_mapping['q'] = Cis*3;
        note_mapping['w'] = E*3;
        note_mapping['e'] = G*3;
        note_mapping['r'] = Ais*3;
        note_mapping['t'] = Cis*4;
        note_mapping['z'] = E*4;
        note_mapping['u'] = G*4;
        note_mapping['i'] = Ais*4;
        note_mapping['o'] = Cis*5;
        note_mapping['p'] = E*5;
        note_mapping[0xfc /* 'ü' */] = G*5;
        note_mapping['+'] = Ais*5;

        note_mapping['a'] = D*3;
        note_mapping['s'] = F*3;
        note_mapping['d'] = Gis*3;
        note_mapping['f'] = B*3;
        note_mapping['g'] = D*4;
        note_mapping['h'] = F*4;
        note_mapping['j'] = Gis*4;
        note_mapping['k'] = B*4;
        note_mapping['l'] = D*5;
        note_mapping[0xf6 /* 'ö' */] = F*5;
        note_mapping[0xe4 /* 'ä' */] = Gis*5;
        note_mapping['#'] = B*5;

        note_mapping['<'] = C*3;
        note_mapping['y'] = Dis*3;
        note_mapping['x'] = Fis*3;
        note_mapping['c'] = A*3;
        note_mapping['v'] = C*4;
        note_mapping['b'] = Dis*4;
        note_mapping['n'] = Fis*4;
        note_mapping['m'] = A*4;
        note_mapping[','] = C*5;
        note_mapping['.'] = Dis*5;
        note_mapping['-'] = Fis*5;
    } else {
        fmt::print("error: invalid keyboard layout: {}\n", (int)args.kb_layout);
    }
}

void Input::update(SDL_Event e) {
    switch (e.type) {
        CASE(SDL_KEYDOWN) {
            int keysym = e.key.keysym.sym;
            if (e.key.repeat) {
                // ignore key repeats
                return;
            }

            std::optional<Note> keynote = (size_t)keysym < note_mapping.size() ? note_mapping[(size_t)keysym] : std::nullopt;
            if (keynote) {
                app->keyboard.hit(*keynote, octave, e.key.timestamp);
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

            std::optional<Note> keynote = (size_t)keysym < note_mapping.size() ? note_mapping[(size_t)keysym] : std::nullopt;
            if (keynote) {
                app->keyboard.release(*keynote, octave, e.key.timestamp);
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
