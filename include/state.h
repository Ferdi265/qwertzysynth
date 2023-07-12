#pragma once

#include <cstdint>
#include <span>
#include <fmt/format.h>
#include <SDL.h>
#include "note.h"

#define CASE(value) case value:
#define DEFAULT() default:

struct State {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_AudioDeviceID audio;
};

inline State state;

void render_init();
void render_fini();
void render_update();

void audio_init();
void audio_fini();

void keyboard_init();
void keyboard_fini();
void keyboard_update(SDL_Event e);

void synth_init();
void synth_fini();
void synth_note(note n);
void synth_release(note n);
void synth_update(std::span<int16_t> buffer);
