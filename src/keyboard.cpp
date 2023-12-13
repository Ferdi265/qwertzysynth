#include "app.hpp"
#include "cli.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include "if_guard.hpp"

void Keyboard::hit_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        hit(*n, app->args.octave, t_sdl);
    } else if (keysym == SDLK_KP_PLUS) {
        app->args.octave++;
    } else if (keysym == SDLK_KP_MINUS) {
        app->args.octave--;
    } else {
        fmt::print("hit: {:x}\n", keysym);
    }
}

void Keyboard::release_key(int keysym, uint32_t t_sdl) {
    std::optional<Note> n = map_key(keysym);
    if (n) {
        release(*n, app->args.octave, t_sdl);
    } else {
        fmt::print("release: {:x}\n", keysym);
    }
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

        ImGui::SetWindowSize(ImVec2(400, 120));
    }

    app->piano.render();
    app->accordeon.render();
}

std::optional<Note> Keyboard::map_key(int keysym) {
    std::optional<Note> n;
    switch (app->args.kb_layout) {
        case KeyboardLayout::Piano:
            n = app->piano.map_key(keysym);
            break;
        case KeyboardLayout::Qwertuoso:
            n = app->accordeon.map_key(keysym);
            break;
        default:
            fmt::print("error: invalid keyboard layout\n");
            break;
    }

    return n;
}

void Keyboard::hit(Note n, int octave, uint32_t t_sdl) {
    app->synth.hit(n >> octave, t_sdl);
    cur_note = n;
}

void Keyboard::release(Note n, int octave, uint32_t t_sdl) {
    app->synth.release(n >> octave, t_sdl);
    if (cur_note && *cur_note == n) {
        cur_note = std::nullopt;
    }
}

