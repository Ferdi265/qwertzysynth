#pragma once

#include <cstddef>
#include <optional>
#include <unordered_map>
#include "non_copyable.hpp"
#include "note.hpp"

struct Accordeon : non_copyable {
    Accordeon() = default;
    ~Accordeon() = default;

    std::optional<Note> map_key(int keysym);
    void render();

    static void print_layout_table();

private:
    static constexpr size_t KEY_WIDTH = 30;
    static constexpr size_t KEY_HEIGHT = 30;

    static const std::unordered_map<int, Note> KEY_MAP;
};
