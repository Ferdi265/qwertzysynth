#pragma once

#include "non_copyable.hpp"
#include "note.hpp"

struct Accordeon : non_copyable {
    Accordeon() = default;
    ~Accordeon() = default;

    void hit(Note n);
    void release(Note n);
    void render();
};
