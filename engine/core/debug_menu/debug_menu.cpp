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

    int angle_hours = variables::cube_angle / 15;
    int hours = 1, days = 4, months = 1, years = 2025;
    hours += angle_hours;

    days = hours / 24;
    months = days / 31;
    years = months / 12;

    if (days == 31)
        days == 0;

    if (months == 12)
        months == 0;

    static int tab = 0;

    ImGui::SetNextWindowPos(ImVec2{ 20.f, 500.f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{ 600.f, 200.f }, ImGuiCond_Once);
    ImGui::Begin("debug_menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    if (ImGui::Button("Engine"))
        tab = 0;
    if (ImGui::Button("Settings"))
        tab = 1;

    switch (tab) {
    case 0:
        ImGui::SliderFloat("Worlds angle", &variables::cube_angle, 0.0f, 360.0f, "%.2f");
        ImGui::SliderFloat("Worlds rotation speed", &variables::cube_rotate_speed, 0.0f, 10.0f, "%.2f");
        ImGui::Text("Time on earth -", hours);
        ImGui::Text("Year: %i", years);
        ImGui::SameLine();
        ImGui::Text("Month: %i", months);
        ImGui::Text("Day: %i", days);
        ImGui::SameLine();
        ImGui::Text("Hour: %i", hours);
        break;
    case 1:
        ImGui::Checkbox("Enable movement", &variables::enable_movement);
        //ImGui::SliderFloat("Movements speed", &c_camera->m_movement_speed, 0.0f, 10.0f, "%.2f");
        //ImGui::SliderFloat("Mouse sensitivity", &c_camera->m_mouse_sensitivity, 0.0f, 1.0f, "%.2f");
        break;

    case 2: // shit loaded

        //ImGui::Text("%c", c_engine->shader_vertex);
        //ImGui::Text("%c", c_engine->shader_fragment);
        //ImGui::Text("%c", c_engine->text_vertex);
        //ImGui::Text("%c", c_engine->text_fragment);

        break;
    }

    ImGui::End();
}