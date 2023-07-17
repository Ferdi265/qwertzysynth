#pragma once

enum struct KeyboardLayout {
    Piano,
    CGriff,
    BGriff,
    Qwertuoso = BGriff,
};

struct CLIArgs {
    KeyboardLayout kb_layout = KeyboardLayout::Piano;
};

CLIArgs parse_args(int argc, char ** argv);
