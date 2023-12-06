#pragma once

#include "non_copyable.hpp"
#include "lazy_constructed.hpp"

#include "render.hpp"
#include "imgui.hpp"
#include "input.hpp"
#include "keyboard.hpp"
#include "piano.hpp"
#include "accordeon.hpp"
#include "audio.hpp"
#include "synth.hpp"

struct App : non_copyable {
    App(CLIArgs args);
    ~App() = default;

    void run();

    // render
    Render render;
    Imgui imgui;
    Input input;

    // routing
    Keyboard keyboard;

    // visualization
    Piano piano;
    Accordeon accordeon;

    // music
    Audio audio;
    Synth synth;
};

inline lazy_constructed<App> app;
