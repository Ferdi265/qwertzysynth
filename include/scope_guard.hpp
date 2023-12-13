#pragma once

#include "non_copyable.hpp"
#include "util.hpp"

template <typename Construct, typename Destruct>
struct scope_guard : non_copyable {
    scope_guard(Construct c, Destruct d) : d(d) { c(); }
    ~scope_guard() { d(); }

    Destruct d;
};

template <typename Construct, typename Destruct>
scope_guard(Construct, Destruct) -> scope_guard<Construct, Destruct>;

#define SCOPE_GUARD(a, b) scope_guard UNIQUE_IDENT(__guard_) {[&]{ a; }, [&]{ b; }}
