#include "app.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

void Piano::render() {
    bool show = true;
    ImGui::Begin("piano", &show, ImGuiWindowFlags_NoResize);

    ImDrawList * draw = ImGui::GetWindowDrawList();
    ImVec2 top_left = ImGui::GetCursorScreenPos();

    constexpr int MIN_KEY = Keyboard::MIN_KEY;
    constexpr int NUM_KEYS = Keyboard::NUM_KEYS;

    auto key_on = [&](int key) { return app->keyboard.cur_note && app->keyboard.cur_note->n == key; };
    auto has_halfstep = [](int key) { key -= MIN_KEY; return (key % 12) == 4 || (key % 12) == 11; };
    auto draw_key = [&](ImVec2 a, ImVec2 b, ImU32 color) {
        draw->AddRectFilled(a, b, color, 0, ImDrawCornerFlags_All);
        draw->AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), IM_COL32(128, 128, 128, 255), 0, ImDrawCornerFlags_All);
    };

    int x, key;

    // white keys
    for (x = 0, key = MIN_KEY; key < MIN_KEY + NUM_KEYS; x++) {
        draw_key(
            top_left + ImVec2(x * KEY_WIDTH, 0),
            top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT),
            key_on(key) ? IM_COL32(255, 0, 0, 255) : IM_COL32_WHITE
        );
        key += has_halfstep(key) ? 1 : 2;
    }

    // black keys
    for (x = 0, key = MIN_KEY; key < MIN_KEY + NUM_KEYS; x++) {
        if (!has_halfstep(key) && key + 1 < NUM_KEYS) {
            draw_key(
                top_left + ImVec2(x * KEY_WIDTH, 0) + ImVec2(KEY_WIDTH * 2 / 3., 0),
                top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT) + ImVec2(KEY_WIDTH * 1 / 3., KEY_HEIGHT * 1 / -4.),
                key_on(key + 1) ? IM_COL32(255, 0, 0, 255) : IM_COL32_BLACK
            );
        }
        key += has_halfstep(key) ? 1 : 2;
    }

    ImGui::SetWindowSize(ImVec2(x * KEY_WIDTH + 16, KEY_HEIGHT + 36));
    ImGui::End();
}
