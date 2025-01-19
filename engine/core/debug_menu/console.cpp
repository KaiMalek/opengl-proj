#define _CRT_SECURE_NO_WARNINGS

#include "console.h"
#include <iostream>
#include <algorithm>

console& console::instance() {
    static console instance;
    return instance;
}

void console::log(const std::string& message, log_type type) {
    log_buffer.push_back({ message, type });
    if (auto_scroll) {
        auto_scroll = true;
    }
}

void console::add_command(const std::string& name, std::function<void()> func) {
    command_map[name] = func;
}

void console::add_alias(const std::string& alias, const std::string& command) {
    aliases[alias] = command;
}

void console::set_variable(const std::string& name, const std::string& value) {
    variables[name] = value;
}

void console::execute_command(const std::string& command) {
    std::string resolved_command = command;

    if (aliases.find(command) != aliases.end()) {
        resolved_command = aliases[command];
    }

    auto it = command_map.find(resolved_command);
    if (it != command_map.end()) {
        it->second();
    }
    else {
        log("Unknown command: " + resolved_command, log_type::ERROR);
    }

    command_history.push_back(command);
    history_index = -1;
}

void console::autocomplete(const std::string& input) {
    std::vector<std::string> suggestions;
    for (const auto& [command, _] : command_map) {
        if (command.find(input) == 0) {
            suggestions.push_back(command);
        }
    }

    if (!suggestions.empty()) {
        log("Suggestions:");
        for (const auto& suggestion : suggestions) {
            log("  " + suggestion);
        }
    }
}

void console::navigate_history(int direction) {
    if (direction < 0 && history_index > 0) {
        history_index--;
    }
    else if (direction > 0 && history_index < static_cast<int>(command_history.size()) - 1) {
        history_index++;
    }

    if (history_index >= 0 && history_index < static_cast<int>(command_history.size())) {
        strncpy(input_buffer, command_history[history_index].c_str(), sizeof(input_buffer));
    }
}

void console::clear() {
    log_buffer.clear();
    auto_scroll = true;
}

void console::render() {
    if (!variables::console_visible) 
        return;

    ImGui::SetNextWindowPos(ImVec2{ 50.f, 50.f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{ 500.f, 700.f }, ImGuiCond_Once);
    ImGui::Begin("console", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
    if (auto_scroll) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::BeginChild("console_region", ImVec2(0, -ImGui::GetTextLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto& log : log_buffer) {
        ImVec4 color;
        switch (log.type) {
        case log_type::INFO: color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); break;
        case log_type::WARNING: color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); break;
        case log_type::ERROR: color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); break;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(log.message.c_str());
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();
    ImGui::Separator();
    std::string command;
    ImGui::InputText("Command", input_buffer, sizeof(input_buffer));
    ImGui::SameLine();
    if (ImGui::Button("Send")) {
        command = input_buffer;
        execute_command(command);
        memset(input_buffer, 0, sizeof(input_buffer));
    }

    ImGui::End();
}
