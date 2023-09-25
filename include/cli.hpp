#pragma once

enum struct KeyboardLayout {
    Piano,
    CGriff,
    BGriff,
    Qwertuoso = BGriff,
};

struct CLIArgs {
    KeyboardLayout kb_layout = KeyboardLayout::Qwertuoso;
    int transpose = 0;
};

CLIArgs parse_args(int argc, char ** argv);
