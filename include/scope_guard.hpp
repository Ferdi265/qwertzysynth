#pragma once

template <typename Construct, typename Destruct>
struct scope_guard {
    scope_guard(Construct c, Destruct d) : c(c), d(d) { c(); }
    ~scope_guard() { d(); }

    scope_guard(const scope_guard&) = delete;
    scope_guard& operator=(const scope_guard&) = delete;

    Construct c;
    Destruct d;
};

template <typename Construct, typename Destruct>
scope_guard(Construct, Destruct) -> scope_guard<Construct, Destruct>;
