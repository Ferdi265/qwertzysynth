#pragma once

template <auto construct, auto destruct>
struct scope_guard {
    scope_guard() { construct(); }
    ~scope_guard() { destruct(); }

    scope_guard(const scope_guard&) = delete;
    scope_guard& operator=(const scope_guard&) = delete;
};
