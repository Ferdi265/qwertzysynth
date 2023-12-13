#pragma once

#include <cstdint>
#include <SDL.h>
#include "non_copyable.hpp"

constexpr uint32_t SAMPLE_RATE = 48000;
constexpr uint32_t BUF_SIZE = 1024;

struct Audio : non_copyable {
    Audio();
    ~Audio();

    SDL_AudioDeviceID device;

    static void update(void * userdata, uint8_t * raw_buffer, int raw_len);
};
