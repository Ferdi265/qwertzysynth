#pragma once

#include <cstddef>
#include "non_copyable.hpp"

struct Accordeon : non_copyable {
    Accordeon() = default;
    ~Accordeon() = default;

    void render();

private:
    static constexpr size_t KEY_WIDTH = 30;
    static constexpr size_t KEY_HEIGHT = 30;
};
