#pragma once

#include "non_copyable.hpp"
#include "note.hpp"

struct Piano : non_copyable {
    Piano() = default;
    ~Piano() = default;

    void hit(Note n);
    void release(Note n);
    void render();
};
