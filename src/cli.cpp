#include <string_view>
#include <charconv>
#include <fmt/format.h>
#include "cli.hpp"
#include "log.hpp"

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

        if (opt == "-l" || opt == "--layout") {
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
