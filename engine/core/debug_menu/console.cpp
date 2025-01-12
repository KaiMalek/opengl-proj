#include "console.h"

console& console::instance() {
    static console instance;
    return instance;
}

void console::log(const std::string& message) {
    log_buffer.push_back(message);
    auto_scroll = true;
}

void console::clear() {
    log_buffer.clear();
    auto_scroll = true;
}

void console::execute_command(const std::string& command) {
    log("> " + command);
    auto it = command_map.find(command);
    if (it != command_map.end()) {
        it->second();
    }
    else {
        log("Unknown command: " + command);
    }
}

void console::register_command(const std::string& name, const std::function<void()>& func) {
    command_map[name] = func;
}

void console::render() {
    if (!variables::console_visible) return;

    ImGui::Begin("Console");

    if (ImGui::Button("Clear")) {
        clear();
    }

    ImGui::Separator();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetTextLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& message : log_buffer) {
        ImGui::TextUnformatted(message.c_str());
    }

    if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
        auto_scroll = false;
    }

    ImGui::EndChild();
    ImGui::Separator();

    if (ImGui::InputText("Command", input_buffer, sizeof(input_buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string command = input_buffer;
        execute_command(command);
        memset(input_buffer, 0, sizeof(input_buffer));
    }

    ImGui::End();
}

bool console::is_visible() const {
    return variables::console_visible;
}