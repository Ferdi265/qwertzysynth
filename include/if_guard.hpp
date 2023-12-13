#pragma once

#include "non_copyable.hpp"
#include "util.hpp"

template <typename Construct, typename Destruct>
struct if_guard {
    if_guard(Construct c, Destruct d) : d(d), b(c()) {}
    ~if_guard() { if (b) d(); }
    explicit operator bool() const { return b; }

    Destruct d;
    bool b;
};

template <typename Construct, typename Destruct>
if_guard(Construct, Destruct) -> if_guard<Construct, Destruct>;

#define IF_GUARD(a, b) if (if_guard UNIQUE_IDENT(__guard_) {[&]{ return a; }, [&]{ b; }})
