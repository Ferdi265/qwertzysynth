#include "app.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

void Accordeon::hit(Note n) {
}

void Accordeon::release(Note n) {
}

void Accordeon::render() {
    bool show = true;
    ImGui::Begin("accordeon", &show, ImGuiWindowFlags_NoResize);

    ImDrawList * draw = ImGui::GetWindowDrawList();
    ImVec2 top_left = ImGui::GetCursorScreenPos();

    auto has_halfstep = [](size_t key) { return (key % 12) == 4 || (key % 12) == 11; };
    auto draw_key = [&](ImVec2 a, ImVec2 b, ImU32 color) {
        draw->AddRectFilled(a, b, color, 0, ImDrawCornerFlags_All);
        draw->AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), IM_COL32(128, 128, 128, 255), 0, ImDrawCornerFlags_All);
    };

    size_t x, key;

    for (x = 0, key = 0; key < NUM_KEYS;) {
        draw_key(
            top_left + ImVec2(x * KEY_WIDTH / 3., (x % 3) * KEY_HEIGHT),
            top_left + ImVec2(x * KEY_WIDTH / 3. + KEY_WIDTH, (x % 3) * KEY_HEIGHT + KEY_HEIGHT),
            IM_COL32_WHITE
        );
        if (!has_halfstep(key) && key + 1 < NUM_KEYS) {
            draw_key(
                top_left + ImVec2((x + 1) * KEY_WIDTH / 3., ((x + 1) % 3) * KEY_HEIGHT),
                top_left + ImVec2((x + 1) * KEY_WIDTH / 3. + KEY_WIDTH, ((x + 1) % 3) * KEY_HEIGHT + KEY_HEIGHT),
                IM_COL32_BLACK
            );
        }
        x += has_halfstep(key) ? 1 : 2;
        key += has_halfstep(key) ? 1 : 2;
    }

    ImGui::SetWindowSize(ImVec2((x + 2) * KEY_WIDTH / 3. + 16, KEY_HEIGHT * 3 + 36));
    ImGui::End();
}
