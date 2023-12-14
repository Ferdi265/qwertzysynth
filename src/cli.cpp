#include <string_view>
#include <charconv>
#include <fmt/format.h>
#include "cli.hpp"
#include "log.hpp"
#include "accordeon.hpp"
#include "piano.hpp"

void usage() {
    fmt::print(
        "usage: qwertzysynth [OPTIONS]\n"
        "\n"
        "OPTIONS:\n"
        "  -h, --help ............ show this help\n"
        "  -l L, --layout L ...... set initial layout (default qwertuoso)\n"
        "    b, b-griff .......... chromatic button accordion B-Griff (default)\n"
        "    q, qwertuoso ........ alias for b-griff\n"
        "    p, piano ............ piano key layout\n"
        "  -t T, --transpose T ... transpose by T half steps\n"
        "  -o O, --octave O ...... transpose by O octaves\n"
        "\n"
        "LAYOUTS:\n"
        "  All QwertzySynth layouts are designed for QWERTZ keyboard layouts.\n"
        "  Support for QWERTY might be provided in a future version.\n"
        "\n"
    );

    Accordeon::print_layout_table();
    Piano::print_layout_table();
}

CLIArgs parse_args(int argc, char ** argv) {
    CLIArgs args;
    bool fail = false;
    auto skip_arg = [&]{ argc--, argv++; };
    auto error = [&]<typename... Args>(fmt::format_string<Args...> fmt, Args&&... args) {
        fail = true;
        ::error(fmt, std::forward<Args&&>(args)...);
    };

    if (argc > 0) {
        skip_arg();
    }

    while (argv[0] != nullptr && argv[0][0] == '-') {
        std::string_view opt = argv[0];
        bool has_arg = argv[1] != nullptr;
        std::string_view arg = has_arg ? argv[1] : "";
        skip_arg();

        auto expect_arg = [&](bool allow_dash = false) {
            if (!has_arg || (!allow_dash && arg[0] == '-')) {
                error("option {} expects an argument\n", opt);
                return false;
            }

            return true;
        };

        if (opt == "-h" || opt == "--help") {
            usage();
            fail = true;
        } else if (opt == "-l" || opt == "--layout") {
            if (!expect_arg()) continue;
            skip_arg();

            if (arg == "piano" || arg == "p") {
                args.kb_layout = KeyboardLayout::Piano;
            } else if (arg == "b-griff" || arg == "bgriff" || arg == "b" || arg == "qwertuoso" || arg == "q") {
                args.kb_layout = KeyboardLayout::BGriff;
            } else {
                error("invalid keyboard layout '{}'\n", arg);
            }
        } else if (opt == "-t" || opt == "--transpose") {
            if (!expect_arg(true)) continue;
            skip_arg();

            int new_transpose = 0;
            auto [ptr, ec] = std::from_chars(arg.begin(), arg.end(), new_transpose);
            if (ec != std::errc()) {
                error("invalid transposition '{}'\n", arg);
                continue;
            }

            args.set_transpose(new_transpose);

        } else if (opt == "-o" || opt == "--octave") {
            if (!expect_arg(true)) continue;
            skip_arg();

            auto [ptr, ec] = std::from_chars(arg.begin(), arg.end(), args.octave);
            if (ec != std::errc()) {
                error("invalid octave '{}'\n", arg);
                continue;
            }
        } else if (opt == "--") {
            break;
        } else {
            error("invalid option '{}'\n", opt);
        }
    }

    if (argc > 0) {
        error("unexpected positional arguments (expected 0, found {})\n", argc);
    }

    if (fail) {
        exit(1);
    }

    return args;
}
