#ifndef CONSOLE_H
#define CONSOLE_H

#include "debug_menu.h"

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

class console {
public:
    static console& instance();

    void log(const std::string& message);
    void clear();
    void execute_command(const std::string& command);
    void register_command(const std::string& name, const std::function<void()>& func);
    void render();
    bool is_visible() const;

private:
    console() = default;
    ~console() = default;
    console(const console&) = delete;
    console& operator=(const console&) = delete;

    std::vector<std::string> log_buffer;
    std::unordered_map<std::string, std::function<void()>> command_map;
    char input_buffer[256] = { 0 };
    bool auto_scroll = true;
};

#endif
