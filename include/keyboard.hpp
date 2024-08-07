#pragma once

#include <cstdint>
#include <optional>
#include "non_copyable.hpp"
#include "note.hpp"

struct Keyboard : non_copyable {
    Keyboard() = default;
    ~Keyboard() = default;

    void hit_key(int keysym, uint32_t t_sdl);
    void release_key(int keysym, uint32_t t_sdl);

    void hit_relative_note(Note n, HitType type, uint32_t t_sdl);
    void release_relative_note(Note n, HitType type, uint32_t t_sdl);
    void release_relative_note(uint32_t t_sdl);

    void hit_note(Note n, HitType type, uint32_t t_sdl);
    void release_note(Note n, HitType type, uint32_t t_sdl);

    void render();

private:
    std::optional<std::pair<Note, HitType>> map_hit_type(std::optional<Note> n);
    std::optional<std::pair<Note, HitType>> map_key(int keysym);

public:
    static constexpr int MIN_KEY = (C*3).n;
    static constexpr int NUM_KEYS = 12 * 3;

    std::optional<std::pair<Note, HitType>> cur_note;
    HitType default_hit_type = HitType::HIT_NORMAL;
};
