#include "debug_menu.h"

debug_menu::~debug_menu() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

debug_menu::debug_menu(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void debug_menu::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    debug_menu::frame_render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
// NOTE: menu_open logic is done in camera::process_input (camera.cpp) (for anyone wondering)
void debug_menu::frame_render() {
    if (!variables::menu_open)
        return;

    ImGui::SetNextWindowPos(ImVec2{ 20.f, 500.f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{ 600.f, 200.f }, ImGuiCond_Once);
    ImGui::Begin("debug_menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Checkbox("Enable movement", &variables::enable_movement);
    ImGui::SliderFloat("Cube's angle", &variables::cube_angle, 0.0f, 360.0f, "%.2f");
    ImGui::End();
}