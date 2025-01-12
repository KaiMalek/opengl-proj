#ifndef CONSOLE_H
#define CONSOLE_H

#include "debug_menu.h"

#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <functional>

enum class log_type { INFO, WARNING, ERROR };

struct log_message {
    std::string message;
    log_type type;
};

class console {
public:
    static console& instance();
    void render();
    void log(const std::string& message, log_type type = log_type::INFO);
    void execute_command(const std::string& command);
    void add_command(const std::string& name, std::function<void()> func);
    void add_alias(const std::string& alias, const std::string& command);
    void set_variable(const std::string& name, const std::string& value);
    void clear();

private:
    console() = default;
    void autocomplete(const std::string& input);
    void navigate_history(int direction);

    char input_buffer[256] = "";
    std::vector<log_message> log_buffer;
    std::deque<std::string> command_history;
    int history_index = -1;
    std::unordered_map<std::string, std::function<void()>> command_map;
    std::unordered_map<std::string, std::string> aliases;
    std::unordered_map<std::string, std::string> variables;
    bool auto_scroll = true;
};

#endif
