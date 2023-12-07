#pragma once

enum struct KeyboardLayout {
    Piano,
    BGriff,
    Qwertuoso = BGriff,
};
constexpr const char * KEYBOARD_LAYOUTS[] = {
    "Piano",
    "B Griff (Qwertuoso)"
};

struct CLIArgs {
    KeyboardLayout kb_layout = KeyboardLayout::Qwertuoso;
    int transpose = 0;
};

CLIArgs parse_args(int argc, char ** argv);
