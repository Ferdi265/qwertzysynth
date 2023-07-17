#pragma once

#include "non_copyable.hpp"
#include "lazy_constructed.hpp"

#include "render.hpp"
#include "audio.hpp"
#include "keyboard.hpp"
#include "synth.hpp"

struct App : non_copyable {
    App();
    ~App() = default;

    void run();

    Render render;
    Audio audio;
    Keyboard keyboard;
    Synth synth;
};

inline lazy_constructed<App> app;
