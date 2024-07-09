#pragma once

#include <cstddef>
#include <optional>
#include <unordered_map>
#include "non_copyable.hpp"
#include "note.hpp"

struct Padme : non_copyable {
    Padme() = default;
    ~Padme() = default;

    std::optional<std::pair<Note, HitType>> map_key(int keysym);
    void render();

    static void print_layout_table();

private:
    static constexpr size_t KEY_WIDTH = 30;
    static constexpr size_t KEY_HEIGHT = 30;

    static const std::unordered_map<int, Note> KEY_MAP;
};
