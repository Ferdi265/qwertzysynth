#pragma once

#include <optional>
#include "non_copyable.hpp"
#include "note.hpp"
#include "cli.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void hit_key(int keysym, uint32_t t_sdl);
    void release_key(int keysym, uint32_t t_sdl);
    void render();

private:
    std::optional<Note> map_key(int keysym);
    void hit(Note n, int octave, uint32_t t_sdl);
    void release(Note n, int octave, uint32_t t_sdl);

public:
    static constexpr int MIN_KEY = (C*3).n;
    static constexpr int NUM_KEYS = 12 * 3;

    std::optional<Note> cur_note;

private:
    int octave = 0;
};
