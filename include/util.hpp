#pragma once

#include <array>
#include <algorithm>
#include <fmt/format.h>

#define CASE(value) case value:
#define DEFAULT() default:

template <typename... Args>
void warn_on(bool cond, fmt::format_string<Args...> fmt, Args&&... args) {
    if (cond) {
        fmt::print("warn: ");
        fmt::print(fmt, std::forward<Args&&>(args)...);
    }
}
