#pragma once

#include <cstddef>

enum struct KeyboardLayout {
    Piano,
    BGriff,
    Qwertuoso = BGriff,
    Padme,
};

constexpr const char * KEYBOARD_LAYOUTS[] = {
    "Piano",
    "B Griff (Qwertuoso)",
    "Padme"
};

struct CLIArgs {
    KeyboardLayout kb_layout = KeyboardLayout::Qwertuoso;
    int transpose = 0;
    int octave = 0;
    size_t polyphony = 2;

    void set_transpose(int new_transpose) {
        while (new_transpose < 0) {
            octave--;
            new_transpose += 12;
        }

        while (new_transpose >= 12) {
            octave++;
            new_transpose -= 12;
        }

        transpose = new_transpose;
    }
};

CLIArgs parse_args(int argc, char ** argv);
