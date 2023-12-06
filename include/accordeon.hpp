#pragma once

#include <optional>
#include "non_copyable.hpp"
#include "note.hpp"

struct Accordeon : non_copyable {
    Accordeon() = default;
    ~Accordeon() = default;

    void hit(Note n);
    void release(Note n);
    void render();

private:
    static constexpr size_t KEY_WIDTH = 30;
    static constexpr size_t KEY_HEIGHT = 30;
    static constexpr int MIN_KEY = (C*3).n;
    static constexpr int NUM_KEYS = 12 * 3;

    std::optional<Note> cur_note;
};
