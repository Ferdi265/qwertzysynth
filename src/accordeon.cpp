#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <fmt/format.h>
#include "if_guard.hpp"
#include "accordeon.hpp"
#include "app.hpp"

const std::unordered_map<int, Note> Accordeon::KEY_MAP = [](){
    std::unordered_map<int, Note> key_map;

    key_map.emplace('1', C*3);
    key_map.emplace('2', Dis*3);
    key_map.emplace('3', Fis*3);
    key_map.emplace('4', A*3);
    key_map.emplace('5', C*4);
    key_map.emplace('6', Dis*4);
    key_map.emplace('7', Fis*4);
    key_map.emplace('8', A*4);
    key_map.emplace('9', C*5);
    key_map.emplace('0', Dis*5);
    key_map.emplace(0xdf /* ß */, Fis*5);

    key_map.emplace('q', Cis*3);
    key_map.emplace('w', E*3);
    key_map.emplace('e', G*3);
    key_map.emplace('r', Ais*3);
    key_map.emplace('t', Cis*4);
    key_map.emplace('z', E*4);
    key_map.emplace('u', G*4);
    key_map.emplace('i', Ais*4);
    key_map.emplace('o', Cis*5);
    key_map.emplace('p', E*5);
    key_map.emplace(0xfc /* 'ü' */, G*5);
    key_map.emplace('+', Ais*5);

    key_map.emplace('a', D*3);
    key_map.emplace('s', F*3);
    key_map.emplace('d', Gis*3);
    key_map.emplace('f', B*3);
    key_map.emplace('g', D*4);
    key_map.emplace('h', F*4);
    key_map.emplace('j', Gis*4);
    key_map.emplace('k', B*4);
    key_map.emplace('l', D*5);
    key_map.emplace(0xf6 /* 'ö' */, F*5);
    key_map.emplace(0xe4 /* 'ä' */, Gis*5);
    key_map.emplace('#', B*5);

    key_map.emplace('<', C*3);
    key_map.emplace('y', Dis*3);
    key_map.emplace('x', Fis*3);
    key_map.emplace('c', A*3);
    key_map.emplace('v', C*4);
    key_map.emplace('b', Dis*4);
    key_map.emplace('n', Fis*4);
    key_map.emplace('m', A*4);
    key_map.emplace(',', C*5);
    key_map.emplace('.', Dis*5);
    key_map.emplace('-', Fis*5);

    return key_map;
}();

void Accordeon::print_layout_table() {
    fmt::print(
        "B-GRIFF LAYOUT:\n"
        "\n"
        "   KEY | NOTE || KEY | NOTE || KEY | NOTE || KEY | NOTE\n"
        "  ------------------------------------------------------\n"
        "       |      ||     |      ||     |      ||  <  | C-3\n"
        "    1  | C-3  ||  Q  | C#3  ||  A  | D-3  ||  Y  | D#3\n"
        "    2  | D#3  ||  W  | E-3  ||  S  | F-3  ||  X  | F#3\n"
        "    3  | F#3  ||  E  | G-3  ||  D  | G#3  ||  C  | A-3\n"
        "    4  | A-3  ||  R  | A#3  ||  F  | B-3  ||  V  | C-4\n"
        "    5  | C-4  ||  T  | C#4  ||  G  | D-4  ||  B  | D#4\n"
        "    6  | D#4  ||  Z  | E-4  ||  H  | F-4  ||  N  | F#4\n"
        "    7  | F#4  ||  U  | G-4  ||  J  | G#4  ||  M  | A-4\n"
        "    8  | A-4  ||  I  | A#4  ||  K  | B-4  ||  ,  | C-5\n"
        "    9  | C-5  ||  O  | C#5  ||  L  | D-5  ||  .  | D#5\n"
        "    0  | D#5  ||  P  | E-5  ||  Ö  | F-5  ||  -  | F#5\n"
        "    ß  | F#5  ||  Ü  | G-5  ||  Ä  | G#5  ||     |\n"
        "    ´  |      ||  +  | A#5  ||  #  | B-5  ||     |\n"
        "\n"
    );
}

std::optional<Note> Accordeon::map_key(int keysym) {
    auto it = KEY_MAP.find(keysym);
    if (it ==  KEY_MAP.end()) {
        return std::nullopt;
    } else {
        return it->second;
    }
}

void Accordeon::render() {
    IF_GUARD(ImGui::Begin("accordeon", nullptr, ImGuiWindowFlags_NoResize), ImGui::End()) {
        ImDrawList * draw = ImGui::GetWindowDrawList();
        ImVec2 top_left = ImGui::GetCursorScreenPos();

        constexpr int MIN_KEY = Keyboard::MIN_KEY;
        constexpr int NUM_KEYS = Keyboard::NUM_KEYS;

        int x, key;
        std::optional<Note> clicked_note;

        auto key_on = [&](int key) { return app->keyboard.cur_note && app->keyboard.cur_note->n == key; };
        auto has_halfstep = [](int key) { key -= MIN_KEY; return (key % 12) == 4 || (key % 12) == 11; };
        auto draw_key = [&](ImVec2 a, ImVec2 b, ImU32 color) {
            draw->AddRectFilled(a, b, color);
            draw->AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), IM_COL32(128, 128, 128, 255));
            if (ImGui::IsMouseHoveringRect(a, b)) clicked_note = Note(key);
        };

        for (x = 0, key = MIN_KEY; key < MIN_KEY + NUM_KEYS; x++, key++) {
            draw_key(
                top_left + ImVec2(x * KEY_WIDTH / 3., (x % 3) * KEY_HEIGHT),
                top_left + ImVec2(x * KEY_WIDTH / 3. + KEY_WIDTH, (x % 3) * KEY_HEIGHT + KEY_HEIGHT),
                key_on(key) ? IM_COL32(255, 0, 0, 255) : IM_COL32_WHITE
            );
            if (!has_halfstep(key) && key + 1 < NUM_KEYS) {
                x++, key++;
                draw_key(
                    top_left + ImVec2(x * KEY_WIDTH / 3., (x % 3) * KEY_HEIGHT),
                    top_left + ImVec2(x * KEY_WIDTH / 3. + KEY_WIDTH, (x % 3) * KEY_HEIGHT + KEY_HEIGHT),
                    key_on(key) ? IM_COL32(255, 0, 0, 255) : IM_COL32_BLACK
                );
            }
        }

        if (clicked_note && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            app->keyboard.hit_relative_note(*clicked_note, SDL_GetTicks());
        } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            app->keyboard.release_relative_note(SDL_GetTicks());
        }

        ImVec2 size = ImVec2((x + 2) * KEY_WIDTH / 3. + 16, KEY_HEIGHT * 3 + 36);
        ImGui::SetWindowSize(size);
        ImGui::SetWindowPos(ImVec2(WIDTH * (1 / 2.), HEIGHT * (2.5 / 3.)) - (size / 2), ImGuiCond_Once);
    }
}
