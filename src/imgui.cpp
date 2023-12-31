#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "imgui.hpp"
#include "app.hpp"

Imgui::Imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(app->render.window, app->render.renderer);
    ImGui_ImplSDLRenderer2_Init(app->render.renderer);

    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
}

Imgui::~Imgui() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Imgui::frame() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Imgui::update(SDL_Event e) {
    ImGui_ImplSDL2_ProcessEvent(&e);
}

void Imgui::render() {
    app->keyboard.render();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

bool Imgui::keyboard_captured() {
    return ImGui::GetIO().WantCaptureKeyboard;
}
