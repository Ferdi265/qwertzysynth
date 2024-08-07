#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <fmt/format.h>
#include "if_guard.hpp"
#include "piano.hpp"
#include "app.hpp"

const std::unordered_map<int, Note> Piano::KEY_MAP = [](){
    std::unordered_map<int, Note> key_map;

    key_map.emplace('2', Cis*4);
    key_map.emplace('3', Dis*4);
    key_map.emplace('5', Fis*4);
    key_map.emplace('6', Gis*4);
    key_map.emplace('7', Ais*4);
    key_map.emplace('9', Cis*5);
    key_map.emplace('0', Dis*5);

    key_map.emplace('q', C*4);
    key_map.emplace('w', D*4);
    key_map.emplace('e', E*4);
    key_map.emplace('r', F*4);
    key_map.emplace('t', G*4);
    key_map.emplace('z', A*4);
    key_map.emplace('u', B*4);
    key_map.emplace('i', C*5);
    key_map.emplace('o', D*5);
    key_map.emplace('p', E*5);
    key_map.emplace(0xfc /* 'ü' */, F*5);
    key_map.emplace('+', G*5);

    key_map.emplace('s', Cis*3);
    key_map.emplace('d', Dis*3);
    key_map.emplace('g', Fis*3);
    key_map.emplace('h', Gis*3);
    key_map.emplace('j', Ais*3);
    key_map.emplace('l', Cis*4);
    key_map.emplace(0xf6 /* ö */, Dis*4);
    key_map.emplace('#', Fis*4);

    key_map.emplace('<', B*2);
    key_map.emplace('y', C*3);
    key_map.emplace('x', D*3);
    key_map.emplace('c', E*3);
    key_map.emplace('v', F*3);
    key_map.emplace('b', G*3);
    key_map.emplace('n', A*3);
    key_map.emplace('m', B*3);
    key_map.emplace(',', C*4);
    key_map.emplace('.', D*4);
    key_map.emplace('-', E*4);

    return key_map;
}();

void Piano::print_layout_table() {
    fmt::print(
        "PIANO LAYOUT:\n"
        "\n"
        "   KEY | NOTE || KEY | NOTE || KEY | NOTE || KEY | NOTE\n"
        "  ------------------------------------------------------\n"
        "       |      ||     |      ||     |      ||  <  | D#3\n"
        "    1  |      ||  Q  | C-4  ||  A  |      ||  Y  | C-3\n"
        "    2  | C#4  ||  W  | D-4  ||  S  | C#3  ||  X  | D-3\n"
        "    3  | D#4  ||  E  | E-4  ||  D  | D#3  ||  C  | E-3\n"
        "    4  |      ||  R  | F-4  ||  F  |      ||  V  | F-3\n"
        "    5  | F#4  ||  T  | G-4  ||  G  | F#3  ||  B  | G-3\n"
        "    6  | G#4  ||  Z  | A-4  ||  H  | G#3  ||  N  | A-3\n"
        "    7  | A#4  ||  U  | B-4  ||  J  | A#3  ||  M  | B-3\n"
        "    8  |      ||  I  | C-5  ||  K  |      ||  ,  | C-4\n"
        "    9  | C#5  ||  O  | D-5  ||  L  | C#4  ||  .  | D-4\n"
        "    0  | D#5  ||  P  | E-5  ||  Ö  | D#4  ||  -  | E-4\n"
        "    ß  |      ||  Ü  | F-5  ||  Ä  |      ||     |\n"
        "    ´  |      ||  +  | G-5  ||  #  | F#4  ||     |\n"
        "\n"
    );
}

std::optional<Note> Piano::map_key(int keysym) {
    auto it = KEY_MAP.find(keysym);
    if (it ==  KEY_MAP.end()) {
        return std::nullopt;
    } else {
        return it->second;
    }
}

void Piano::render() {
    IF_GUARD(ImGui::Begin("piano", nullptr, ImGuiWindowFlags_NoResize), ImGui::End()) {
        ImDrawList * draw = ImGui::GetWindowDrawList();
        ImVec2 top_left = ImGui::GetCursorScreenPos();

        constexpr int MIN_KEY = Keyboard::MIN_KEY;
        constexpr int NUM_KEYS = Keyboard::NUM_KEYS;

        int x, key;
        std::optional<Note> clicked_note;

        auto key_on = [&](int key) { return app->keyboard.cur_note && app->keyboard.cur_note->first.n == key; };
        auto has_halfstep = [](int key) { key -= MIN_KEY; return (key % 12) == 4 || (key % 12) == 11; };
        auto draw_key = [&](ImVec2 a, ImVec2 b, ImU32 color) {
            draw->AddRectFilled(a, b, color);
            draw->AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), IM_COL32(128, 128, 128, 255));
            if (ImGui::IsMouseHoveringRect(a, b)) clicked_note = Note(key);
        };

        // white keys
        for (x = 0, key = MIN_KEY; key < MIN_KEY + NUM_KEYS; x++, key += has_halfstep(key) ? 1 : 2) {
            draw_key(
                top_left + ImVec2(x * KEY_WIDTH, 0),
                top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT),
                key_on(key) ? IM_COL32(255, 0, 0, 255) : IM_COL32_WHITE
            );
        }

        // black keys
        for (x = 0, key = MIN_KEY; key < MIN_KEY + NUM_KEYS; x++, key++) {
            if (!has_halfstep(key) && key + 1 < NUM_KEYS) {
                key++;
                draw_key(
                    top_left + ImVec2(x * KEY_WIDTH, 0) + ImVec2(KEY_WIDTH * 2 / 3., 0),
                    top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT) + ImVec2(KEY_WIDTH * 1 / 3., KEY_HEIGHT * 1 / -4.),
                    key_on(key) ? IM_COL32(255, 0, 0, 255) : IM_COL32_BLACK
                );
            }
        }

        if (clicked_note && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            app->keyboard.hit_relative_note(*clicked_note, app->keyboard.default_hit_type, SDL_GetTicks());
        } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            app->keyboard.release_relative_note(SDL_GetTicks());
        }

        ImVec2 size = ImVec2(x * KEY_WIDTH + 16, KEY_HEIGHT + 36);
        ImGui::SetWindowSize(size);
        ImGui::SetWindowPos(ImVec2(WIDTH * (1 / 2.), HEIGHT * (1.5 / 3.)) - (size / 2), ImGuiCond_Once);
    }
}
