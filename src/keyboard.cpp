#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include "log.hpp"
#include "if_guard.hpp"
#include "keyboard.hpp"
#include "app.hpp"

void Keyboard::hit_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        hit_relative_note(*n, t_sdl);
    } else if (keysym == SDLK_KP_PLUS || keysym == SDLK_F2) {
        app->args.octave++;
    } else if (keysym == SDLK_KP_MINUS || keysym == SDLK_F1) {
        app->args.octave--;
    }
}

void Keyboard::release_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        release_relative_note(*n, t_sdl);
    }
}

void Keyboard::hit_relative_note(Note n, uint32_t t_sdl) {
    hit_note(n >> app->args.octave, t_sdl);
    cur_note = n;
}

void Keyboard::release_relative_note(Note n, uint32_t t_sdl) {
    release_note(n >> app->args.octave, t_sdl);
    if (cur_note && *cur_note == n) {
        cur_note = std::nullopt;
    }
}

void Keyboard::release_relative_note(uint32_t t_sdl) {
    if (cur_note) {
        release_note(*cur_note >> app->args.octave, t_sdl);
        cur_note = std::nullopt;
    }
}

void Keyboard::hit_note(Note n, uint32_t t_sdl) {
    app->synth.hit(n, t_sdl);
}

void Keyboard::release_note(Note n, uint32_t t_sdl) {
    app->synth.release(n, t_sdl);
}

void Keyboard::render() {
    IF_GUARD(ImGui::Begin("settings", nullptr, ImGuiWindowFlags_NoResize), ImGui::End()) {
        ImGui::Text("Current Note:");
        ImGui::SameLine(130);
        ImGui::Text("%s", cur_note ? fmt::format("{}", *cur_note).c_str() : "none");

        size_t cur_layout = (size_t)app->args.kb_layout;
        ImGui::Text("Keyboard Layout:");
        ImGui::SameLine(130);
        IF_GUARD(ImGui::BeginCombo("##layout", KEYBOARD_LAYOUTS[cur_layout]), ImGui::EndCombo()) {
            for (size_t i = 0; i < std::size(KEYBOARD_LAYOUTS); i++) {
                bool is_selected = cur_layout == i;

                if (ImGui::Selectable(KEYBOARD_LAYOUTS[i], is_selected)) {
                    app->args.kb_layout = (KeyboardLayout)i;
                }

                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
        }

        int new_transpose = app->args.transpose;
        ImGui::Text("Transpose:");
        ImGui::SameLine(130);
        ImGui::InputInt("##transpose", &new_transpose);
        app->args.set_transpose(new_transpose);

        ImGui::Text("Octave:");
        ImGui::SameLine(130);
        ImGui::InputInt("##octave", &app->args.octave);

        ImVec2 size = ImVec2(400, 120);
        ImGui::SetWindowSize(size);
        ImGui::SetWindowPos(ImVec2(WIDTH * (1 / 2.), HEIGHT * (0.5 / 3.)) - (size / 2), ImGuiCond_Once);
    }

    app->piano.render();
    app->accordeon.render();
}

std::optional<Note> Keyboard::map_key(int keysym) {
    std::optional<Note> n;
    switch (app->args.kb_layout) {
        CASE(KeyboardLayout::Piano) {
            n = app->piano.map_key(keysym);
            break;
        }

        CASE(KeyboardLayout::Qwertuoso) {
            n = app->accordeon.map_key(keysym);
            break;
        }

        DEFAULT() {
            error("invalid keyboard layout\n");
            break;
        }
    }

    return n;
}

