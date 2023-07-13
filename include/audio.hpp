#pragma once

#include <SDL.h>
#include "non_copyable.hpp"

struct Audio : non_copyable {
    Audio();
    ~Audio();

    SDL_AudioDeviceID device;

    static void update(void * userdata, uint8_t * raw_buffer, int raw_len);
};
