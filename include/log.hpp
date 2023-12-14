#pragma once

#include <cstdlib>
#include <utility>
#include <fmt/format.h>
#include "app.hpp"

template <typename... Args>
void log(const char * tag, fmt::format_string<Args...> fmt, Args&&... args) {
    fmt::print("{}: ", tag);
    fmt::print(fmt, std::forward<Args&&>(args)...);
}

template <typename... Args>
void debug(fmt::format_string<Args...> fmt, Args&&... args) {
    log("debug", fmt, std::forward<Args&&>(args)...);
}

template <typename... Args>
void info(fmt::format_string<Args...> fmt, Args&&... args) {
    log("info", fmt, std::forward<Args&&>(args)...);
}

template <typename... Args>
void warn(fmt::format_string<Args...> fmt, Args&&... args) {
    log("warn", fmt, std::forward<Args&&>(args)...);
}

template <typename... Args>
void error(fmt::format_string<Args...> fmt, Args&&... args) {
    log("error", fmt, std::forward<Args&&>(args)...);
}

template <typename... Args>
void fatal_error(fmt::format_string<Args...> fmt, Args&&... args) {
    error(fmt, std::forward<Args&&>(args)...);
    exit(1);
}
