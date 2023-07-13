#pragma once

#include "non_copyable.hpp"
#include "singleton_wrapper.hpp"

#include "render.hpp"
#include "audio.hpp"
#include "keyboard.hpp"
#include "synth.hpp"

struct App : non_copyable {
    App() = default;
    ~App() = default;

    static App& instance() {
        static App app;
        return app;
    }

    Render render;
    Audio audio;
    Keyboard keyboard;
    Synth synth;
};

inline singleton_wrapper<App> app;
