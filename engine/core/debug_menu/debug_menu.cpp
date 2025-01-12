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
    watermark();
    console::instance().render();

    if (!variables::menu_open)
        return;

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
        break;
    case 1:
        ImGui::Checkbox("Enable movement", &variables::enable_movement);
        //ImGui::SliderFloat("Movements speed", &c_camera->m_movement_speed, 0.0f, 10.0f, "%.2f");
        //ImGui::SliderFloat("Mouse sensitivity", &c_camera->m_mouse_sensitivity, 0.0f, 1.0f, "%.2f");
        break;
    }

    ImGui::End();
}
// just gonna do styles.h later on for cooler debug menus (habit from game hacking)
void setup_styles() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 0.f;
}

void debug_menu::watermark() {
    setup_styles();

    ImGui::SetNextWindowPos(ImVec2{ 10.f, 10.f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{ 100.f, 20.f }, ImGuiCond_Once);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, .00f));
    
    ImGui::Begin("debug_watermark", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::End();
}