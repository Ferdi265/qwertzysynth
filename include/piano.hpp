#pragma once

#include <cstddef>
#include "non_copyable.hpp"

struct Piano : non_copyable {
    Piano() = default;
    ~Piano() = default;

    void render();

private:
    static constexpr size_t KEY_WIDTH = 20;
    static constexpr size_t KEY_HEIGHT = 100;
};
