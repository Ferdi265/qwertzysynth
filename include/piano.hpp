#pragma once

#include <cstddef>
#include <optional>
#include <unordered_map>
#include "non_copyable.hpp"
#include "note.hpp"

struct Piano : non_copyable {
    Piano() = default;
    ~Piano() = default;

    std::optional<Note> map_key(int keysym);
    void render();

    static void print_layout_table();

private:
    static constexpr size_t KEY_WIDTH = 20;
    static constexpr size_t KEY_HEIGHT = 100;

    static const std::unordered_map<int, Note> KEY_MAP;
};
