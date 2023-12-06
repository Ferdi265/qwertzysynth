#include "app.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

void Piano::hit(Note n) {
}

void Piano::release(Note n) {
}

void Piano::render() {
    bool show = true;
    ImGui::Begin("piano", &show, ImGuiWindowFlags_NoResize);

    ImDrawList * draw = ImGui::GetWindowDrawList();
    ImVec2 top_left = ImGui::GetCursorScreenPos();

    auto has_halfstep = [](size_t key) { return (key % 12) == 4 || (key % 12) == 11; };
    auto draw_key = [&](ImVec2 a, ImVec2 b, ImU32 color) {
        draw->AddRectFilled(a, b, color, 0, ImDrawCornerFlags_All);
        draw->AddRect(a, b + ImVec2(1, 1), IM_COL32_BLACK, 0, ImDrawCornerFlags_All);
    };

    size_t width = 0;
    size_t x, key;

    // white keys
    for (x = 0, key = 0; key < NUM_KEYS; x++) {
        draw_key(
            top_left + ImVec2(x * KEY_WIDTH, 0),
            top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT),
            IM_COL32_WHITE
        );
        key += has_halfstep(key) ? 1 : 2;
    }
    width = std::max(width, x);

    // black keys
    for (x = 0, key = 0; key < NUM_KEYS; x++) {
        if (!has_halfstep(key) && key + 1 < NUM_KEYS) {
            draw_key(
                top_left + ImVec2(x * KEY_WIDTH, 0) + ImVec2(KEY_WIDTH * 2 / 3., 0),
                top_left + ImVec2((x + 1) * KEY_WIDTH, KEY_HEIGHT) + ImVec2(KEY_WIDTH * 1 / 3., KEY_HEIGHT * 1 / -4.),
                IM_COL32_BLACK
            );
        }
        key += has_halfstep(key) ? 1 : 2;
    }
    width = std::max(width, x);

    ImGui::SetWindowSize(ImVec2(width * KEY_WIDTH + 16, KEY_HEIGHT + 36));
    ImGui::End();
}
