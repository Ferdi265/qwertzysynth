#include <string_view>
#include <fmt/format.h>
#include "cli.hpp"

using namespace std::string_view_literals;

CLIArgs parse_args(int argc, char ** argv) {
    CLIArgs args;
    bool fail = false;
    auto skip_arg = [&]{ argc--, argv++; };
    auto error = [&]<typename... Args>(fmt::format_string<Args...> fmt, Args... args){
        fmt::print(fmt, std::forward<Args&&>(args)...);
        fail = true;
    };

    if (argc > 0) {
        skip_arg();
    }

    while (argv[0] != nullptr && argv[0][0] == '-') {
        char * opt = argv[0];
        char * arg = argv[1];
        skip_arg();

        if (opt == "--layout"sv) {
            if (arg == nullptr || arg[0] == '-') {
                error("error: option --layout expects an argument\n");
                continue;
            }
            skip_arg();

            if (arg == "piano"sv || arg == "p"sv) {
                args.kb_layout = KeyboardLayout::Piano;
            } else if (arg == "c-griff"sv || arg == "cgriff"sv || arg == "c"sv) {
                args.kb_layout = KeyboardLayout::CGriff;
            } else if (arg == "b-griff"sv || arg == "bgriff"sv || arg == "b"sv || arg == "qwertuoso"sv || arg == "q"sv) {
                args.kb_layout = KeyboardLayout::BGriff;
            } else {
                error("error: invalid keyboard layout '{}'\n", arg);
            }
        } else if (opt == "--"sv) {
            break;
        } else {
            error("error: invalid option '{}'\n", opt);
        }
    }

    if (argc > 0) {
        error("error: unexpected positional arguments (expected 0, found {})\n", argc);
    }

    if (fail) {
        exit(1);
    }

    return args;
}
